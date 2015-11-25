#include "MainMenuScene.hpp"

using namespace std;
using namespace cocos2d;

struct MainMenuScene::Impl
{
	Impl();
	~Impl();
};

MainMenuScene* MainMenuScene::create()
{
	auto p = new (std::nothrow) MainMenuScene();
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

MainMenuScene::MainMenuScene()
	: m_pimpl(make_unique<MainMenuScene::Impl>())
{

}

MainMenuScene::~MainMenuScene()
{

}

bool MainMenuScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	return true;
}

MainMenuScene::Impl::Impl()
{

}

MainMenuScene::Impl::~Impl()
{

}
