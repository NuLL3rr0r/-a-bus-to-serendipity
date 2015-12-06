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
	GameScene* m_parent;

public:
	explicit Impl(GameScene* parent);
	~Impl();

public:
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	void onScreenOrientationChanged(const Android::ScreenOrientation& orientation);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

public:
	void setupEvents();
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

GameScene::~GameScene() = default;

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto background = Sprite::create("bg_game.png");
	background->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y));
	this->addChild(background, - 1);

	m_pimpl->setupEvents();

	return true;
}

GameScene::Impl::Impl(GameScene *parent)
	: m_parent(parent)
{

}

GameScene::Impl::~Impl()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->screenOrientationChangedSignal.disconnect(this, &Impl::onScreenOrientationChanged);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
}

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
void GameScene::Impl::onScreenOrientationChanged(const Android::ScreenOrientation& orientation)
{
	Android::getInstance()->debug("Screen rotated!");
}
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

void GameScene::Impl::setupEvents()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->screenOrientationChangedSignal.connect(this, &Impl::onScreenOrientationChanged);
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
}
