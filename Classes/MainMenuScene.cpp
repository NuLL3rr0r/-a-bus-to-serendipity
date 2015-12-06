#include "make_unique.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Android.hpp"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "MainMenuScene.hpp"
#include "SceneManager.hpp"
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

MainMenuScene::~MainMenuScene() = default;

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

MainMenuScene::Impl::~Impl() = default;

void MainMenuScene::Impl::createTitle()
{
	auto vGap = VisibleRect::height() * 0.25f;

	auto titleLabel = Label::createWithTTF("A Bus to Serendipity", "fonts/Marker Felt.ttf", 24);
	titleLabel->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y + vGap));
	m_parent->addChild(titleLabel);
}

void MainMenuScene::Impl::createMenu()
{
	auto vGap = VisibleRect::height() * 0.10f;
	float vOffset = 40.0f;

	MenuItemFont::setFontName("fonts/Marker Felt.ttf");
	MenuItemFont::setFontSize(20);

	auto newGameItem = MenuItemFont::create("New Game", [&](Ref *sender) {
		SceneManager::getInstance()->load(SceneManager::Scene::Game);
	});

	auto creditsItem = MenuItemFont::create("Credits", [&](Ref *sender) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		Android::getInstance()->debug("ToDo...");
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	});

	auto exitItem = MenuItemFont::create("Exit", [&](Ref *sender) {
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(EXIT_SUCCESS);
#endif
	});

	auto menu = Menu::create(newGameItem, creditsItem, exitItem, nullptr);
	menu->setPosition(Point::ZERO);

	float nextItemOffset = 0.0f;
	int i = 0;
	for (const auto& child : menu->getChildren()) {
		child->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y + vGap - nextItemOffset));
		nextItemOffset += vOffset;

		auto dstPoint = child->getPosition();
		auto offset = VisibleRect::center().x + 50.0f;
		if (i % 2 == 0)
			offset = -offset;

		child->setPosition(Vec2(dstPoint.x + offset, dstPoint.y));
		child->runAction(
			EaseElasticOut::create(MoveTo::create(2.0f, Vec2(dstPoint.x, dstPoint.y)), 0.35f)
			);
		i++;
	}

	m_parent->addChild(menu);
}
