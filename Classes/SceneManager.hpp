#ifndef __SCENE_MANAGER_HPP__
#define __SCENE_MANAGER_HPP__

#include <memory>
#include "cocos2d.h"

class SceneManager : public cocos2d::Ref
{
public:
	enum class Scene : const unsigned char {
		MainMenu,
		Game
	};

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static SceneManager* getInstance();

private:
	SceneManager();
	virtual ~SceneManager();

public:
	bool init();

	void run();
	void load(const Scene& scene);
};

#endif // __SCENE_MANAGER_HPP__
