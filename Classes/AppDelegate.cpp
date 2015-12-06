#include "make_unique.hpp"
#include "SimpleAudioEngine.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Android.hpp"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AppDelegate.hpp"
#include "SceneManager.hpp"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

static int register_all_packages()
{
	return 0;
}

struct AppDelegate::Impl
{
public:
	static const cocos2d::Size DesignResolutionSize;
	static const cocos2d::Size SdResolutionSize;
	static const cocos2d::Size MdResolutionSize;
	static const cocos2d::Size HdResolutionSize;

private:
	AppDelegate *m_parent;

public:
	explicit Impl(AppDelegate *parent);
	~Impl();

	void setupSounds();
};

const cocos2d::Size AppDelegate::Impl::DesignResolutionSize = cocos2d::Size(480, 320);
const cocos2d::Size AppDelegate::Impl::SdResolutionSize = cocos2d::Size(480, 320);
const cocos2d::Size AppDelegate::Impl::MdResolutionSize = cocos2d::Size(960, 640);
const cocos2d::Size AppDelegate::Impl::HdResolutionSize = cocos2d::Size(1920, 1280);

AppDelegate::AppDelegate()
	: m_pimpl(make_unique<AppDelegate::Impl>(this))
{

}

AppDelegate::~AppDelegate() = default;

bool AppDelegate::applicationDidFinishLaunching()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	(void*)Android::getInstance();
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
#ifndef NDEBUG
		glview = GLViewImpl::createWithRect("A Bus to Serendipity", Rect(0, 0, m_pimpl->MdResolutionSize.width, m_pimpl->MdResolutionSize.height));
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

	glview->setDesignResolutionSize(m_pimpl->DesignResolutionSize.width, m_pimpl->DesignResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
	Size frameSize = glview->getFrameSize();

	std::vector<std::string> searchPaths;
	auto fileUtils = FileUtils::getInstance();

	if (frameSize.height > m_pimpl->MdResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(m_pimpl->HdResolutionSize.height / m_pimpl->DesignResolutionSize.height, m_pimpl->HdResolutionSize.width / m_pimpl->DesignResolutionSize.width));
		searchPaths.push_back("res/hd");
	}
	else if (frameSize.height > m_pimpl->SdResolutionSize.height)
	{
		director->setContentScaleFactor(MIN(m_pimpl->MdResolutionSize.height / m_pimpl->DesignResolutionSize.height, m_pimpl->MdResolutionSize.width / m_pimpl->DesignResolutionSize.width));
		searchPaths.push_back("res/md");
	}
	else
	{
		director->setContentScaleFactor(MIN(m_pimpl->SdResolutionSize.height / m_pimpl->DesignResolutionSize.height, m_pimpl->SdResolutionSize.width / m_pimpl->DesignResolutionSize.width));
		searchPaths.push_back("res/sd");
	}

	fileUtils->setSearchPaths(searchPaths);

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

AppDelegate::Impl::~Impl() = default;

void AppDelegate::Impl::setupSounds()
{

}
