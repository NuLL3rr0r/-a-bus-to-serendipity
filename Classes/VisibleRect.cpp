#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct VisibleRect::Impl
{
public:
	static Rect visibleRect;

	static void lazyInit();

private:
	VisibleRect *m_parent;

public:
	explicit Impl(VisibleRect *parent);
	~Impl();
};

Rect VisibleRect::Impl::visibleRect;

const cocos2d::Size& VisibleRect::size()
{
	Impl::lazyInit();
	return Impl::visibleRect.size;
}

const float VisibleRect::width()
{
	Impl::lazyInit();
	return Impl::visibleRect.size.width;
}

const float VisibleRect::height()
{
	Impl::lazyInit();
	return Impl::visibleRect.size.height;
}

const cocos2d::Point VisibleRect::left()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x, Impl::visibleRect.origin.y + Impl::visibleRect.size.height / 2);
}

const cocos2d::Point VisibleRect::right()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x + Impl::visibleRect.size.width, Impl::visibleRect.origin.y + Impl::visibleRect.size.height / 2);
}

const cocos2d::Point VisibleRect::top()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x + Impl::visibleRect.size.width / 2, Impl::visibleRect.origin.y + Impl::visibleRect.size.height);
}

const cocos2d::Point VisibleRect::bottom()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x + Impl::visibleRect.size.width / 2, Impl::visibleRect.origin.y);
}

const cocos2d::Point VisibleRect::center()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x + Impl::visibleRect.size.width / 2, Impl::visibleRect.origin.y + Impl::visibleRect.size.height / 2);
}

const cocos2d::Point VisibleRect::leftTop()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x, Impl::visibleRect.origin.y + Impl::visibleRect.size.height);
}

const cocos2d::Point VisibleRect::rightTop()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x + Impl::visibleRect.size.width, Impl::visibleRect.origin.y + Impl::visibleRect.size.height);
}

const cocos2d::Point VisibleRect::leftBottom()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x, Impl::visibleRect.origin.y);
}

const cocos2d::Point VisibleRect::rightBottom()
{
	Impl::lazyInit();
	return Point(Impl::visibleRect.origin.x + Impl::visibleRect.size.width, Impl::visibleRect.origin.y);
}

VisibleRect::VisibleRect()
	: m_pimpl(make_unique<VisibleRect::Impl>(this))
{

}

VisibleRect::~VisibleRect()
{

}

void VisibleRect::Impl::lazyInit()
{
	if (visibleRect.size.width == 0.0f && visibleRect.size.height == 0.0f) {
		auto director = Director::getInstance();
		visibleRect.origin = director->getVisibleOrigin();
		visibleRect.size = director->getVisibleSize();
	}
}

VisibleRect::Impl::Impl(VisibleRect *parent)
	: m_parent(parent)
{

}

VisibleRect::Impl::~Impl()
{

}
