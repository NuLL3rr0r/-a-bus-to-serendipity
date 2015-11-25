#include "SimpleAudioEngine.h"
#include "AppDelegate.hpp"
#include "SceneManager.hpp"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

static int register_all_packages()
{
	return 0;
}

struct AppDelegate::Impl
{
private:
	AppDelegate *m_parent;

public:
	explicit Impl(AppDelegate *parent);
	~Impl();

	void setupSounds();
};

AppDelegate::AppDelegate()
	: m_pimpl(make_unique<AppDelegate::Impl>(this))
{

}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#ifndef NDEBUG
		glview = GLViewImpl::createWithRect("A Bus to Serendipity", Rect(0, 0, mediumResolutionSize.width, mediumResolutionSize.height));
#else
		glview = GLViewImpl::createWithFullScreen("A Bus to Serendipity");
#endif // NDEBUG
#else
		glview = GLViewImpl::create("A Bus to Serendipity");
#endif // (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		director->setOpenGLView(glview);
	}

	director->setAnimationInterval(1.0f / 60.0f);
#ifndef NDEBUG
	director->setDisplayStats(true);
#endif // NDEBUG

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	Size frameSize = glview->getFrameSize();
	if (frameSize.height > mediumResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	}
	else if (frameSize.height > smallResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}
	else
	{
		director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	}

	register_all_packages();

	auto sceneManager = SceneManager::getInstance();
	sceneManager->run();

	auto audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->setBackgroundMusicVolume(0.5f);
	audioEngine->setEffectsVolume(0.5f);

	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs{ 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

AppDelegate::Impl::Impl(AppDelegate *parent)
	: m_parent(parent)
{

}

AppDelegate::Impl::~Impl()
{

}

void AppDelegate::Impl::setupSounds()
{

}
