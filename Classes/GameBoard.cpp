#include "make_unique.hpp"
#include "GameBoard.hpp"

using namespace std;
using namespace cocos2d;

struct GameBoard::Impl
{
public:
	static const string ASSET_BOARD;

private:
	GameBoard* m_parent;

public:
	explicit Impl(GameBoard* parent);
	~Impl();

public:
	void setupEvents();
};

const string GameBoard::Impl::ASSET_BOARD = "game_board.png";

GameBoard* GameBoard::create()
{
	auto p = new (std::nothrow) GameBoard();
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

GameBoard::GameBoard()
	: m_pimpl(make_unique<GameBoard::Impl>(this))
{

}

GameBoard::~GameBoard() = default;

bool GameBoard::init()
{
	if (!Node::init()) {
		return false;
	}

	auto background = Sprite::create(m_pimpl->ASSET_BOARD);
	this->addChild(background, -1);

	m_pimpl->setupEvents();

	return true;
}

GameBoard::Impl::Impl(GameBoard* parent)
	: m_parent(parent)
{

}

GameBoard::Impl::~Impl() = default;

void GameBoard::Impl::setupEvents()
{

}
