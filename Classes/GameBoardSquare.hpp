#ifndef GAME_BOARD_SQUARE_HPP
#define GAME_BOARD_SQUARE_HPP

#include <memory>
#include "cocos2d.h"

class GameBoardSquare : public cocos2d::Node
{
	friend class GameBoard;

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static GameBoardSquare* create(float width, float height, float borderWidth,
		const cocos2d::Color4F& fillColor, const cocos2d::Color4F& borderColor);
	static GameBoardSquare* create(cocos2d::Sprite* sprite);

private:
	GameBoardSquare();
public:
	virtual ~GameBoardSquare();
public:
	bool init(float width, float height, float borderWidth,
		const cocos2d::Color4F &fillColor, const cocos2d::Color4F &borderColor);
	bool init(cocos2d::Sprite* sprite);
};

#endif // GAME_BOARD_SQUARE_HPP
