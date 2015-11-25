#ifndef __VISIBLE_RECT_HPP__
#define __VISIBLE_RECT_HPP__

#include <memory>
#include "cocos2d.h"

class VisibleRect : public cocos2d::Scene
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static const cocos2d::Size& size();

	static const float width();
	static const float height();

	static const cocos2d::Point left();
	static const cocos2d::Point right();
	static const cocos2d::Point top();
	static const cocos2d::Point bottom();
	static const cocos2d::Point center();
	static const cocos2d::Point leftTop();
	static const cocos2d::Point rightTop();
	static const cocos2d::Point leftBottom();
	static const cocos2d::Point rightBottom();

private:
	VisibleRect();
	virtual ~VisibleRect();
};

#endif // __VISIBLE_RECT_HPP__
