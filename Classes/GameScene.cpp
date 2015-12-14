#include <iomanip>
#include <string>
#include <sstream>
#include "make_unique.hpp"
#include "GameScene.hpp"
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

GameScene::~GameScene() = default;

void GameScene::update(float delta)
{

}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

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
