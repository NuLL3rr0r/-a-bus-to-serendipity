#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <memory>
#include "cocos2d.h"

class GameBoardSquare;

class GameBoard : public cocos2d::Node
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static GameBoard* create();

private:
	GameBoard();
	virtual ~GameBoard();
public:
	virtual bool init() override;

public:
	GameBoardSquare* getSquare(const int index) const;
};

#endif // GAME_BOARD_HPP
