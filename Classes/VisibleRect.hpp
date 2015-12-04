#ifndef VISIBLE_RECT_HPP
#define VISIBLE_RECT_HPP

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

#endif // VISIBLE_RECT_HPP
