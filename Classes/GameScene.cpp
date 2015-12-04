#include "make_unique.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Android.hpp"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "GameScene.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct GameScene::Impl
{
private:
	GameScene *m_parent;

public:
	explicit Impl(GameScene *parent);
	~Impl();

public:
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	void onScreenOrientationChanged(const Android::ScreenOrientation&);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
};

GameScene* GameScene::create()
{
	auto p = new (std::nothrow) GameScene();
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

GameScene::GameScene()
	: m_pimpl(make_unique<GameScene::Impl>(this))
{

}

GameScene::~GameScene()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->ScreenOrientationChangedSignal.disconnect(m_pimpl.get(), &Impl::onScreenOrientationChanged);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto background = Sprite::create("bg_game.png");
	background->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y));
	this->addChild(background, - 1);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->ScreenOrientationChangedSignal.connect(m_pimpl.get(), &Impl::onScreenOrientationChanged);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	return true;
}

GameScene::Impl::Impl(GameScene *parent)
	: m_parent(parent)
{

}

GameScene::Impl::~Impl()
{

}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void GameScene::Impl::onScreenOrientationChanged(const Android::ScreenOrientation&)
{
	Android::getInstance()->debug("Screen rotated!");
}
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

