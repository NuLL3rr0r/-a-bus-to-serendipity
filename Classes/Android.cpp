#ifdef __ANDROID__

#include <jni.h>
#include "Android.hpp"
#include "make_unique.hpp"

using namespace std;
using namespace cocos2d;

static JavaVM* s_javaVM = NULL;
static jclass s_appActivityClassID = NULL;
static jmethodID s_appActivityConstructorMethodID = NULL;
static jmethodID s_appActivityReleaseMethodID = NULL;
static jmethodID s_appActivityDebugMethodID = NULL;

static void screenOrientationChanged(JNIEnv*, jobject, int state)
{

}

static JNINativeMethod s_jniNativeMethods[] = {
	{ "screenOrientationChanged", "(I)V", (void*)screenOrientationChanged }
};

// This method is called immediately after the module is loaded.
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void*)
{
	JNIEnv* env;
	if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		CCLOG("FATAL: Could not get the JNI enviroument!");
		return -1;
	}

	s_javaVM = vm;

	// Search for AppActivity class.
	jclass clazz = env->FindClass("serendipity/AppActivity");
	if (!clazz) {
		CCLOG("FATAL: Could not find the Android class!");
		return -1;
	}

	// Keep a global reference to it.
	s_appActivityClassID = (jclass)env->NewGlobalRef(clazz);

	// Search for its contructor.
	s_appActivityConstructorMethodID = env->GetMethodID(s_appActivityClassID, "<init>", "()V");
	if (!s_appActivityConstructorMethodID) {
		CCLOG("FATAL: Could not find the Android class contructor!");
		return -1;
	}

	// Search for release method.
	s_appActivityReleaseMethodID = env->GetMethodID(s_appActivityClassID, "release", "()Z");
	if (!s_appActivityReleaseMethodID) {
		CCLOG("FATAL: Could not find Release method!");
		return -1;
	}

	// Search for debug method.
	s_appActivityDebugMethodID = env->GetMethodID(s_appActivityClassID, "debug", "(Ljava/lang/CharSequence)V");
	if (!s_appActivityDebugMethodID) {
		CCLOG("FATAL: Could not find debug method!");
		return -1;
	}

	CCLOG("INFO: JNI_OnLoad was executed successfully!");

	return JNI_VERSION_1_6;
}

struct Android::Impl
{
public:
	static mutex androidMutex;
	static Android* androidInstance;

public:
	jobject appActivityObject;

private:
	Android *m_parent;

public:
	explicit Impl(Android *parent);
	~Impl();
};

mutex Android::Impl::androidMutex;
Android* Android::Impl::androidInstance = nullptr;

Android* Android::getInstance()
{
	lock_guard<mutex> lock(Impl::androidMutex);
	(void)lock;

	if (!Impl::androidInstance)
	{
		Impl::androidInstance = new (std::nothrow) Android();
		CCASSERT(Impl::androidInstance, "FATAL: Not enough memory!");
		Impl::androidInstance->init();
		Impl::androidInstance->autorelease();
	}

	return Impl::androidInstance;
}

Android::Android()
	: m_pimpl(make_unique<Android::Impl>(this))
{
	JNIEnv* env;

	// Cocos2d-x is running in a different thread than Java UI.
	// So, Java VM *MUST* always stay attached to the current thread.
	if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
		CCLOG("FATAL: AttachCurrentThread failed!");
		return;
	}

	// Create a new instance of appActivity.
	m_pimpl->appActivityObject = env->NewGlobalRef(env->NewObject(s_appActivityClassID,	s_appActivityConstructorMethodID));
	if (!m_pimpl->appActivityObject) {
		CCLOG("FATAL: Could not create the appActivity class instance!");
		return;
	}

	// Don't forget to detach from current thread.
	s_javaVM->DetachCurrentThread();
}

Android::~Android()
{
	if (m_pimpl->appActivityObject) {
		JNIEnv* env;

		if (s_javaVM->AttachCurrentThread(&env, NULL) < 0 ) {
			CCLOG("FATAL: AttachCurrentThread failed!");
			return;
		}

		if (!env->CallBooleanMethod(m_pimpl->appActivityObject,	s_appActivityReleaseMethodID)) {
			CCLOG("FATAL: Releasing appActivity object failed!");
		}

		s_javaVM->DetachCurrentThread();
	}

	Impl::androidInstance = nullptr;
}

bool Android::init()
{
	return true;
}

void Android::debug(const std::string &log)
{
	if (m_pimpl->appActivityObject)
		return;

	JNIEnv* env;

	if (s_javaVM->AttachCurrentThread(&env, NULL) < 0) {
		CCLOG("FATAL: AttachCurrentThread failed!");
		return;
	}

	jstring str = env->NewString(reinterpret_cast<const jchar*>(log.c_str()), log.length());

	env->CallVoidMethod(m_pimpl->appActivityObject, s_appActivityDebugMethodID, str);
	env->DeleteLocalRef(str);
	s_javaVM->DetachCurrentThread();
}

Android::Impl::Impl(Android *parent)
	: m_parent(parent)
{
	appActivityObject = nullptr;
}

Android::Impl::~Impl()
{

}

#endif // __ANDROID__
