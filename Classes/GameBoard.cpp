#include <vector>
#include "make_unique.hpp"
#include "GameBoard.hpp"
#include "GameBoardSquare.hpp"
#include "Utility.hpp"

using namespace std;
using namespace cocos2d;

struct GameBoard::Impl
{
public:
	static const int BOARD_COLUMNS;
	static const int BOARD_ROWS;
	static const int BOARD_TOTAL_SQUARES;
	static const float BOARD_SQUARE_WIDTH;
	static const float BOARD_SQUARE_HEIGHT;
	static const float BOARD_SQUARE_BOARDER_THICKNESS;
	static const Color4F BOARD_SQUARE_FILL_COLOR_FIRST;
	static const Color4F BOARD_SQUARE_FILL_COLOR_SECOND;
	static const Color4F BOARD_SQUARE_BOARDER_COLOR;

public:
	vector<GameBoardSquare*> squares;

private:
	GameBoard* m_parent;

public:
	explicit Impl(GameBoard* parent);
	~Impl();

public:
	void setupEvents();
};

const int GameBoard::Impl::BOARD_COLUMNS = 6;
const int GameBoard::Impl::BOARD_ROWS = 8;
const int GameBoard::Impl::BOARD_TOTAL_SQUARES = GameBoard::Impl::BOARD_COLUMNS * GameBoard::Impl::BOARD_ROWS;
const float GameBoard::Impl::BOARD_SQUARE_WIDTH = 50.0f;
const float GameBoard::Impl::BOARD_SQUARE_HEIGHT = 50.0f;
const float GameBoard::Impl::BOARD_SQUARE_BOARDER_THICKNESS = 1.0f;
const Color4F GameBoard::Impl::BOARD_SQUARE_FILL_COLOR_FIRST = Color4F::GRAY;
const Color4F GameBoard::Impl::BOARD_SQUARE_FILL_COLOR_SECOND = Color4F::WHITE;
const Color4F GameBoard::Impl::BOARD_SQUARE_BOARDER_COLOR = Color4F::BLACK;

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
	this->removeAllChildrenWithCleanup(true);

	if (!Node::init()) {
		return false;
	}

	const float BOARD_WIDTH = m_pimpl->BOARD_SQUARE_WIDTH * m_pimpl->BOARD_COLUMNS;
	const float BOARD_HEIGHT = m_pimpl->BOARD_SQUARE_HEIGHT * m_pimpl->BOARD_ROWS;
	const Vec2 SQUARE_ANCHOR_POINT(0.5f, 0.5f);

	int col = 0;
	int row = 0;
	Color4F color;
	Vec2 position;
	for (int i = 0; i < m_pimpl->BOARD_TOTAL_SQUARES; ++i) {
		if (col >= m_pimpl->BOARD_COLUMNS) {
			col = 0;
			++row;
		}

		if (row >= m_pimpl->BOARD_ROWS) {
			break;
		}

		if (row % 2) {
			if (col % 2) {
				color = m_pimpl->BOARD_SQUARE_FILL_COLOR_FIRST;
			}
			else {
				color = m_pimpl->BOARD_SQUARE_FILL_COLOR_SECOND;
			}
		}
		else {
			if (col % 2) {
				color = m_pimpl->BOARD_SQUARE_FILL_COLOR_SECOND;
			}
			else {
				color = m_pimpl->BOARD_SQUARE_FILL_COLOR_FIRST;
			}
		}

		position.x = col * m_pimpl->BOARD_SQUARE_WIDTH;
		position.y = row * m_pimpl->BOARD_SQUARE_HEIGHT;

		auto square = GameBoardSquare::create(m_pimpl->BOARD_SQUARE_WIDTH, m_pimpl->BOARD_SQUARE_HEIGHT,
			m_pimpl->BOARD_SQUARE_BOARDER_THICKNESS,
			color, m_pimpl->BOARD_SQUARE_BOARDER_COLOR);
		square->ignoreAnchorPointForPosition(true);
		square->setAnchorPoint(SQUARE_ANCHOR_POINT);
		square->setPosition(position);

		this->setContentSize(Size((col + 1) * m_pimpl->BOARD_SQUARE_WIDTH,
			(row + 1) * m_pimpl->BOARD_SQUARE_HEIGHT));
		this->addChild(square);
		m_pimpl->squares.push_back(square);

		++col;
	}

	m_pimpl->setupEvents();

	return true;
}

GameBoardSquare* GameBoard::getSquare(const int index) const
{
	if (index < m_pimpl->squares.size()) {
		return m_pimpl->squares[index];
	}
	else {
		return nullptr;
	}
}

GameBoard::Impl::Impl(GameBoard* parent)
	: m_parent(parent)
{

}

GameBoard::Impl::~Impl() = default;

void GameBoard::Impl::setupEvents()
{

}
