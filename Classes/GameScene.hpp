#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

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

#endif // GAME_SCENE_HPP
