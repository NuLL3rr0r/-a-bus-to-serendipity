#include <mutex>
#include "make_unique.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Android.hpp"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Screen.hpp"

using namespace std;
using namespace cocos2d;

struct Screen::Impl
{
public:
	static mutex mutex_;
	static Screen* instance_;

private:
	Screen *m_parent;

public:
	explicit Impl(Screen* parent);
	~Impl();

public:
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	void onAndroidScreenOrientationChanged(const Android::ScreenOrientation& orientation);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

public:
	void setupEvents();
};

mutex Screen::Impl::mutex_;
Screen* Screen::Impl::instance_ = nullptr;

Screen* Screen::getInstance()
{
	lock_guard<mutex> lock(Impl::mutex_);
	(void)lock;

	if (!Impl::instance_) {
		Impl::instance_ = new (std::nothrow) Screen();
		CCASSERT(Impl::instance_, "FATAL: Not enough memory!");
		Impl::instance_->init();
		Impl::instance_->autorelease();
	}

	return Impl::instance_;
}

Screen::Screen()
	: m_pimpl(make_unique<Screen::Impl>(this))
{

}

Screen::~Screen()
{
	Impl::instance_ = nullptr;
}

bool Screen::init()
{
	if (!Impl::instance_) {
		return false;
	}

	m_pimpl->setupEvents();

	return true;
}

const Screen::Orientation Screen::getOrientation() const
{
	auto orientation = Screen::Orientation::Undefined;
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (glview) {
		Size frameSize = glview->getFrameSize();
		auto ratio = frameSize.width / frameSize.height;

		if (ratio == 1.0f) {
			orientation = Screen::Orientation::Square;
		}
		else {
			if (ratio < 1.0f) {
				orientation = Screen::Orientation::Portrait;
			}
			else {
				orientation = Screen::Orientation::Landscape;
			}
		}
	}

	return orientation;
}

Screen::Impl::Impl(Screen *parent)
	: m_parent(parent)
{

}

Screen::Impl::~Impl()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->screenOrientationChangedSignal.disconnect(this, &Impl::onAndroidScreenOrientationChanged);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void Screen::Impl::onAndroidScreenOrientationChanged(const Android::ScreenOrientation& orientation)
{
	m_parent->orientationChangedSignal.emit(static_cast<const Screen::Orientation>(static_cast<const unsigned char>(orientation)));
}
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

void Screen::Impl::setupEvents()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->screenOrientationChangedSignal.connect(this, &Impl::onAndroidScreenOrientationChanged);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
}
