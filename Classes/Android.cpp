#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <android/log.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "Android.hpp"
#include "make_unique.hpp"

#define  LOG_TAG    "Android.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;
using namespace cocos2d;

static void screenOrientationChanged(JNIEnv*, jobject, int state)
{

}

static JNINativeMethod s_jniNativeMethods[] = {
	{ "screenOrientationChanged", "(I)V", (void*)screenOrientationChanged }
};

struct Android::Impl
{
public:
	static mutex androidMutex;
	static Android* androidInstance;

public:
	jclass appActivityClass;
	jobject appActivityObject;
	jmethodID appActivityGetObjectMethod;
	jmethodID appActivityDebugMethod;

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

}

Android::~Android()
{
	Impl::androidInstance = nullptr;
}

bool Android::init()
{
	JavaVM* javaVM = JniHelper::getJavaVM();
	JNIEnv* env = JniHelper::getEnv();

	m_pimpl->appActivityClass = env->FindClass("serendipity/AppActivity");
	if (!m_pimpl->appActivityClass) {
		LOGD("FATAL: Failed to find class `AppActivity`!");
		return false;
	}

	m_pimpl->appActivityGetObjectMethod = env->GetStaticMethodID(m_pimpl->appActivityClass, "getObject", "()Ljava/lang/Object;");
	if (!m_pimpl->appActivityGetObjectMethod) {
		LOGD("FATAL: Failed to find static method `AppActivity.getObject()`!");
		return false;
	}

	m_pimpl->appActivityObject = env->CallStaticObjectMethod(m_pimpl->appActivityClass, m_pimpl->appActivityGetObjectMethod);
	if (!m_pimpl->appActivityObject) {
		LOGD("FATAL: Failed to get the current instance of the running activity!");
		return false;
	}

	m_pimpl->appActivityDebugMethod = env->GetMethodID(m_pimpl->appActivityClass, "debug", "(Ljava/lang/CharSequence)V");
	if (!m_pimpl->appActivityDebugMethod) {
		LOGD("FATAL: Failed to find method `AppActivity.debug()`!");
		return false;
	}

	LOGD("INFO: Android interface initialized successfully!");

	return true;
}

void Android::debug(const std::string &log)
{
	if (!m_pimpl->appActivityObject)
		return;

	if (!m_pimpl->appActivityDebugMethod)
		return;

	JNIEnv* env = JniHelper::getEnv();
	jstring logJstr = env->NewString(reinterpret_cast<const jchar*>(log.c_str()), log.length());

	env->CallVoidMethod(m_pimpl->appActivityObject, m_pimpl->appActivityDebugMethod, logJstr);
	env->DeleteLocalRef(logJstr);
}

Android::Impl::Impl(Android *parent)
	: m_parent(parent)
{
	appActivityObject = nullptr;
}

Android::Impl::~Impl()
{

}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
