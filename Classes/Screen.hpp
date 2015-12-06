#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
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

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

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
