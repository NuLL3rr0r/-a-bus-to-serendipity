#include <iomanip>
#include <string>
#include <sstream>
#include "make_unique.hpp"
#include "GameBoard.hpp"
#include "GameBoardSquare.hpp"
#include "GameScene.hpp"
#include "InputManager.hpp"
#include "PostProcess.hpp"
#include "Screen.hpp"
#include "Utility.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct GameScene::Impl
{
public:
	Layer* gameLayer;
	PostProcess* grayPostProcessLayer;
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

	m_pimpl->gameLayer = Layer::create();
	m_pimpl->gameLayer->setAnchorPoint(Point::ZERO);
	m_pimpl->gameLayer->setPosition(Point::ZERO);
	this->addChild(m_pimpl->gameLayer, 0);

	m_pimpl->grayPostProcessLayer = PostProcess::create("shaders/gray.vert", "shaders/gray.frag");
	m_pimpl->grayPostProcessLayer->setAnchorPoint(Point::ZERO);
	m_pimpl->grayPostProcessLayer->setPosition(Point::ZERO);
	this->addChild(m_pimpl->grayPostProcessLayer, 1);

	auto camera = Camera::createPerspective(60, (GLfloat)VisibleRect::width() / VisibleRect::height(), 1, 1000);
	camera->setPosition3D(Vec3(0, 100, 100));
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
	this->addChild(camera);

	auto ambientLight = AmbientLight::create(Color3B(200, 200, 200));
	ambientLight->setEnabled(true);
	m_pimpl->gameLayer->addChild(ambientLight);

	m_pimpl->gameBoard = GameBoard::create();
	m_pimpl->gameBoard->ignoreAnchorPointForPosition(false);
	m_pimpl->gameBoard->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_pimpl->gameBoard->setPosition(VisibleRect::center().x, VisibleRect::center().y);
	m_pimpl->gameLayer->addChild(m_pimpl->gameBoard);

	this->addChild(InputManager::getInstance());

	m_pimpl->setupEvents();
	this->scheduleUpdate();

	return true;
}

void GameScene::update(float delta)
{
	m_pimpl->grayPostProcessLayer->draw(m_pimpl->gameLayer);
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
