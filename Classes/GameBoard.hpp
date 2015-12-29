#ifndef GAME_BOARD_HPP
#define GAME_BOARD_HPP

#include <memory>
#include "cocos2d.h"

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
	virtual const cocos2d::Size& getContentSize() const override;
};

#endif // GAME_BOARD_HPP
