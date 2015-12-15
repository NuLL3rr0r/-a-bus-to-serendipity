#ifndef MAIN_MENU_SCENE_HPP
#define MAIN_MENU_SCENE_HPP

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

#endif // MAIN_MENU_SCENE_HPP
