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

	typedef wink::slot<void(const Orientation&)> OrientationChangedSlot_t;
	typedef wink::signal<OrientationChangedSlot_t> OrientationChangedSignal_t;

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	OrientationChangedSignal_t orientationChangedSignal;

public:
	static Screen* getInstance();

private:
	Screen();
	virtual ~Screen();

public:
	bool init();

	const Orientation getOrientation() const;
};

#endif // SCREEN_HPP
