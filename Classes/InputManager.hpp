#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <memory>
#include "wink/slot.hpp"
#include "wink/signal.hpp"
#include "cocos2d.h"

class InputManager : public cocos2d::Node
{
public:
	enum class Key : const unsigned char {
		ESC,
		PLAYER_LEFT,
		PLAYER_UP,
		PLAYER_RIGHT,
		PLAYER_DOWN
	};

	typedef wink::slot<void(const Key&)> KeyPressedSlot;
	typedef wink::signal<KeyPressedSlot> KeyPressedSignal;

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	KeyPressedSignal keyPressedSignal;

public:
	static InputManager* getInstance();

private:
	InputManager();
	virtual ~InputManager();
public:
	virtual bool init() override;

public:
	virtual void update(float delta) override;
};

#endif // INPUT_MANAGER_HPP
