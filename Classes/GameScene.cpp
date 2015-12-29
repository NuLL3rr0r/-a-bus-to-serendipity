#include <iomanip>
#include <string>
#include <sstream>
#include "make_unique.hpp"
#include "GameBoard.hpp"
#include "GameScene.hpp"
#include "InputManager.hpp"
#include "Screen.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct GameScene::Impl
{
public:
	GameBoard* gameBoard;

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

	m_pimpl->gameBoard = GameBoard::create();
	m_pimpl->gameBoard->ignoreAnchorPointForPosition(false);
	m_pimpl->gameBoard->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_pimpl->gameBoard->setPosition(VisibleRect::center().x, VisibleRect::center().y);
	this->addChild(m_pimpl->gameBoard);

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
	switch (key) {
	case InputManager::Key::START:
		CCLOG("START");
		break;
	case InputManager::Key::PLAYER_LEFT:
		CCLOG("LEFT");
		break;
	case InputManager::Key::PLAYER_UP:
		CCLOG("UP");
		break;
	case InputManager::Key::PLAYER_RIGHT:
		CCLOG("RIGHT");
		break;
	case InputManager::Key::PLAYER_DOWN:
		CCLOG("DOWN");
		break;
	}
}

void GameScene::Impl::setupEvents()
{
	InputManager::getInstance()->keyPressedSignal.connect(this, &Impl::onInputKeyPressed);
}
