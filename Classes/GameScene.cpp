#include "make_unique.hpp"
#include "GameScene.hpp"
#include "Screen.hpp"
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

GameScene::Impl::~Impl() = default;

void GameScene::Impl::setupEvents()
{

}
