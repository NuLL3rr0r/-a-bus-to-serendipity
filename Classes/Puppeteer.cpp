#include "make_unique.hpp"
#include "Puppeteer.hpp"

using namespace std;
using namespace cocos2d;

struct Puppeteer::Impl
{
private:
	Puppeteer* m_parent;

public:
	explicit Impl(Puppeteer* parent);
	~Impl();

public:
	void setupEvents();
};

Puppeteer* Puppeteer::create()
{
	auto p = new (std::nothrow) Puppeteer();
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

Puppeteer::Puppeteer()
	: m_pimpl(make_unique<Puppeteer::Impl>(this))
{

}

Puppeteer::~Puppeteer() = default;

bool Puppeteer::init()
{
	if (!Node::init()) {
		return false;
	}

	m_pimpl->setupEvents();

	return true;
}

Puppeteer::Impl::Impl(Puppeteer* parent)
	: m_parent(parent)
{

}

Puppeteer::Impl::~Impl() = default;

void Puppeteer::Impl::setupEvents()
{

}
