#include "MainMenuScene.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct MainMenuScene::Impl
{
private:
	MainMenuScene *m_parent;

public:
	explicit Impl(MainMenuScene *parent);
	~Impl();

	void createTitle();
	void createMenu();
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
	: m_pimpl(make_unique<MainMenuScene::Impl>(this))
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

	m_pimpl->createTitle();
	m_pimpl->createMenu();

	return true;
}

MainMenuScene::Impl::Impl(MainMenuScene *parent)
	: m_parent(parent)
{

}

MainMenuScene::Impl::~Impl()
{

}

void MainMenuScene::Impl::createTitle()
{
	auto vgap = VisibleRect::height() * 0.25;

	auto titleLabel = Label::createWithTTF("A Bus to Serendipity", "fonts/Marker Felt.ttf", 24);
	titleLabel->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y + vgap));
	m_parent->addChild(titleLabel);
}

void MainMenuScene::Impl::createMenu()
{

}
