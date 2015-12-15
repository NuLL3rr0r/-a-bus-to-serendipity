#include <iomanip>
#include <string>
#include <sstream>
#include "make_unique.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Android.hpp"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "GameScene.hpp"
#include "InputManager.hpp"
#include "Screen.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct GameScene::Impl
{
public:
	static const string ASSET_BACKGROUND;

private:
	GameScene* m_parent;

public:
	explicit Impl(GameScene* parent);
	~Impl();

public:
	void onInputKeyPressed(const InputManager::Key& key);

public:
	void setupEvents();
};

const string GameScene::Impl::ASSET_BACKGROUND = "bg_land.png";

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

}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	this->addChild(InputManager::getInstance());

	m_pimpl->setupEvents();

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float delta)
{

}

GameScene::Impl::Impl(GameScene *parent)
	: m_parent(parent)
{

}

GameScene::Impl::~Impl()
{
	InputManager::getInstance()->keyPressedSignal.disconnect(this, &Impl::onInputKeyPressed);
}

void GameScene::Impl::onInputKeyPressed(const InputManager::Key& key)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	Android::getInstance()->init();
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	switch (key) {
	case InputManager::Key::ESC:
		CCLOG("ESC");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		Android::getInstance()->debug("ESC");
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		break;
	case InputManager::Key::PLAYER_LEFT:
		CCLOG("LEFT");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		Android::getInstance()->debug("LEFT");
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		break;
	case InputManager::Key::PLAYER_UP:
		CCLOG("UP");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		Android::getInstance()->debug("UP");
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		break;
	case InputManager::Key::PLAYER_RIGHT:
		CCLOG("RIGHT");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		Android::getInstance()->debug("RIGHT");
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		break;
	case InputManager::Key::PLAYER_DOWN:
		CCLOG("DOWN");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		Android::getInstance()->debug("DOWN");
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		break;
	}
}

void GameScene::Impl::setupEvents()
{
	InputManager::getInstance()->keyPressedSignal.connect(this, &Impl::onInputKeyPressed);
}
