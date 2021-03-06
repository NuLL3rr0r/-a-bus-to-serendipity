#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <cstddef>
#include <memory>
#include "cocos2d.h"

class GameBoardSquare;
class IGamePiece;

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
	GameBoardSquare* getSquare(const std::size_t index) const;

	void addPiece(IGamePiece* piece);
};

#endif // GAME_BOARD_HPP
