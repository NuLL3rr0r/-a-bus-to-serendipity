#include "make_unique.hpp"
#include "GameBoardSquare.hpp"
#include "Utility.hpp"

using namespace std;
using namespace cocos2d;

struct GameBoardSquare::Impl
{
private:
	GameBoardSquare* m_parent;

public:
	explicit Impl(GameBoardSquare* parent);
	~Impl();

public:
	void setupEvents();
};

GameBoardSquare* GameBoardSquare::create(float width, float height, float borderWidth,
	const cocos2d::Color4F& fillColor, const cocos2d::Color4F& borderColor)
{
	auto p = new (std::nothrow) GameBoardSquare();
	if (p && p->init(width, height, borderWidth, fillColor, borderColor)) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

GameBoardSquare* GameBoardSquare::create(cocos2d::Sprite* sprite)
{
	auto p = new (std::nothrow) GameBoardSquare();
	if (p && p->init(sprite)) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

GameBoardSquare::GameBoardSquare()
	: m_pimpl(make_unique<GameBoardSquare::Impl>(this))
{

}

GameBoardSquare::~GameBoardSquare() = default;

bool GameBoardSquare::init(float width, float height, float borderWidth,
	const cocos2d::Color4F &fillColor, const cocos2d::Color4F &borderColor)
{
	this->removeAllChildrenWithCleanup(true);

	if (!Node::init()) {
		return false;
	}

	const float PX = width;
	const float NX = 0.0f;
	const float PY = height;
	const float NY = 0.0f;

	auto rect = DrawNode::create();
	Vec2 vertices[]	{
		Vec2(PX, PY),
		Vec2(NX, PY),
		Vec2(NX, NY),
		Vec2(PX, NY)
	};
	rect->drawPolygon(vertices, 4, fillColor, borderWidth, borderColor);
	rect->setContentSize(Size(width, height));
	rect->ignoreAnchorPointForPosition(true);
	rect->setAnchorPoint(Vec2(0.5f, 0.5f));
	rect->setPosition(Vec2(0.0f, 0.0f));

	this->setContentSize(Size(width, height));
	this->addChild(rect);

	m_pimpl->setupEvents();

	return true;
}

bool GameBoardSquare::init(cocos2d::Sprite* sprite)
{
	this->removeAllChildrenWithCleanup(true);

	if (!Node::init()) {
		return false;
	}

	this->addChild(sprite, -1);

	m_pimpl->setupEvents();

	return true;
}

GameBoardSquare::Impl::Impl(GameBoardSquare* parent)
	: m_parent(parent)
{

}

GameBoardSquare::Impl::~Impl() = default;

void GameBoardSquare::Impl::setupEvents()
{

}
