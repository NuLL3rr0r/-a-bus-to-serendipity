#include <mutex>
#include "make_unique.hpp"
#include "Screen.hpp"

using namespace std;
using namespace cocos2d;

struct Screen::Impl
{
public:
	static mutex screenMutex;
	static Screen* screenInstance;

private:
	Screen *m_parent;

public:
	explicit Impl(Screen* parent);
	~Impl();
};

mutex Screen::Impl::screenMutex;
Screen* Screen::Impl::screenInstance = nullptr;

Screen* Screen::getInstance()
{
	lock_guard<mutex> lock(Impl::screenMutex);
	(void)lock;

	if (!Impl::screenInstance)
	{
		Impl::screenInstance = new (std::nothrow) Screen();
		CCASSERT(Impl::screenInstance, "FATAL: Not enough memory!");
		Impl::screenInstance->init();
		Impl::screenInstance->autorelease();
	}

	return Impl::screenInstance;
}

Screen::Screen()
	: m_pimpl(make_unique<Screen::Impl>(this))
{

}

Screen::~Screen()
{
	Impl::screenInstance = nullptr;
}

bool Screen::init()
{
	return true;
}

Screen::Impl::Impl(Screen *parent)
	: m_parent(parent)
{

}

Screen::Impl::~Impl() = default;
