#ifndef PUPPETEER_HPP
#define PUPPETEER_HPP

#include <memory>
#include "cocos2d.h"

class Puppeteer : public cocos2d::Node
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

private:
	Puppeteer();
	virtual ~Puppeteer();
public:
	virtual bool init() override;
};

#endif // PUPPETEER_HPP
