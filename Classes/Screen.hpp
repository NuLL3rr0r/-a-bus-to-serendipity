#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include "wink/slot.hpp"
#include "wink/signal.hpp"
#include "cocos2d.h"

class Screen : public cocos2d::Ref
{
public:
	enum class Orientation : const unsigned char {
		Undefined = 0,
		Portrait = 1,
		Landscape = 2,
		Square = 3
	};

	typedef wink::slot<void(const Orientation&)> OrientationChangedSlot;
	typedef wink::signal<OrientationChangedSlot> OrientationChangedSignal;

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	OrientationChangedSignal orientationChangedSignal;

public:
	static Screen* getInstance();

private:
	Screen();
	virtual ~Screen();
public:
	virtual bool init();

public:
	const Orientation getOrientation() const;
};

#endif // SCREEN_HPP
