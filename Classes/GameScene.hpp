#ifndef __GAME_SCENE_HPP__
#define __GAME_SCENE_HPP__

#include <memory>
#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static GameScene* create();

public:
	GameScene();
	virtual ~GameScene();

public:
	virtual bool init() override;
};

#endif // __GAME_SCENE_HPP__
