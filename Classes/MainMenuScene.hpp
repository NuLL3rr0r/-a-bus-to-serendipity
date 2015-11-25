#ifndef __MAIN_MENU_SCENE_HPP__
#define __MAIN_MENU_SCENE_HPP__

#include <memory>
#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static MainMenuScene* create();

public:
	MainMenuScene();
	virtual ~MainMenuScene();

public:
	virtual bool init() override;
};

#endif // __MAIN_MENU_SCENE_HPP__
