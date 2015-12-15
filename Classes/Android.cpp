#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <functional>
#include <vector>
#include <android/log.h>
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "Android.hpp"
#include "make_unique.hpp"

#define  LOG_TAG    "[Android.cpp]"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

using namespace std;
using namespace cocos2d;

static std::function<void(const Android::ScreenOrientation&)> screenOrientationChangedHandler = nullptr;

static void screenOrientationChanged(JNIEnv*, jobject, const int orientation)
{
	if (screenOrientationChangedHandler) {
		// To avoid evil "JNI ERROR (app bug): attempt to use stale local reference 0xHHHHHHHH".
		Android::getInstance()->init();

		screenOrientationChangedHandler(static_cast<const Android::ScreenOrientation>(orientation));
	}
}

struct Android::Impl
{
public:
	static mutex mutex_;
	static Android* instance_;

	static JNINativeMethod jniNativeMethods[];

public:
	jclass appActivityClass;
	jobject appActivityObject;
	jmethodID appActivityGetObjectMethod;
	jmethodID appActivityDebugMethod;

private:
	Android* m_parent;

public:
	explicit Impl(Android* parent);
	~Impl();
};

JNINativeMethod Android::Impl::jniNativeMethods[] = {
	{ "screenOrientationChanged", "(I)V", (void*)screenOrientationChanged }
};

mutex Android::Impl::mutex_;
Android* Android::Impl::instance_ = nullptr;

Android* Android::getInstance()
{
	lock_guard<mutex> lock(Impl::mutex_);
	(void)lock;

	if (!Impl::instance_) {
		Impl::instance_ = new (std::nothrow) Android();
		CCASSERT(Impl::instance_, "FATAL: Not enough memory!");
		Impl::instance_->init();
		Impl::instance_->autorelease();
	}

	return Impl::instance_;
}

Android::Android()
	: m_pimpl(make_unique<Android::Impl>(this))
{

}

Android::~Android()
{
	Impl::instance_ = nullptr;
}

bool Android::init()
{
	if (!Impl::instance_) {
		return false;
	}

	JavaVM* javaVM = JniHelper::getJavaVM();
	JNIEnv* env = JniHelper::getEnv();
	
	// Keep a global reference to it, or, you may crash!
	// Since Android ICS, class references are not global so we need to peg a
	// global reference to the jclass returned by FindClass(), otherwise we get
	// following error in the log:
	// "JNI ERROR (app bug): attempt to use stale local reference 0xHHHHHHHH".
	jclass clazz = env->FindClass("serendipity/AppActivity");
	if (!clazz) {
		LOGD("FATAL: Failed to find class `AppActivity`!");
		return false;
	}
	m_pimpl->appActivityClass = static_cast<jclass>(env->NewGlobalRef(clazz));

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

	m_pimpl->appActivityDebugMethod = env->GetMethodID(m_pimpl->appActivityClass, "debug", "(Ljava/lang/CharSequence;)V");
	if (!m_pimpl->appActivityDebugMethod) {
		LOGD("FATAL: Failed to find method `AppActivity.debug()`!");
		return false;
	}

	if (env->RegisterNatives(m_pimpl->appActivityClass,	m_pimpl->jniNativeMethods,
		sizeof(m_pimpl->jniNativeMethods) / sizeof(m_pimpl->jniNativeMethods[0])) < 0) {
		LOGD("FATAL: Failed to register native methods!");
		return false;
	}

	screenOrientationChangedHandler = [](const Android::ScreenOrientation& orientation) {
		Android::getInstance()->screenOrientationChangedSignal.emit(orientation);
	};

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
	jstring logJstr = env->NewStringUTF(log.c_str());

	env->CallVoidMethod(m_pimpl->appActivityObject, m_pimpl->appActivityDebugMethod, logJstr);
	env->DeleteLocalRef(logJstr);

	LOGD("%s", log.c_str());
}

Android::Impl::Impl(Android *parent)
	: m_parent(parent)
{
	appActivityObject = nullptr;
}

Android::Impl::~Impl() = default;

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
