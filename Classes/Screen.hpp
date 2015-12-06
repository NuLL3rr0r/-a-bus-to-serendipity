#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>
#include "cocos2d.h"

class Screen : public cocos2d::Ref
{
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
};

#endif // SCREEN_HPP
