#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>
#include "cocos2d.h"

class InputManager : public cocos2d::Ref
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
	static InputManager* getInstance();

private:
	InputManager();
	virtual ~InputManager();

public:
	bool init();
};

#endif // INPUT_MANAGER_HPP
