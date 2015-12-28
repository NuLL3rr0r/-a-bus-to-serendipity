#include "make_unique.hpp"
#include "Puppet.hpp"

using namespace std;
using namespace cocos2d;

struct Puppet::Impl
{
private:
	Puppet* m_parent;

public:
	explicit Impl(Puppet* parent);
	~Impl();

public:
	void setupEvents();
};

Puppet::Puppet()
	: m_pimpl(make_unique<Puppet::Impl>(this))
{

}

Puppet::~Puppet() = default;

bool Puppet::init()
{
	if (!Node::init()) {
		return false;
	}

	m_pimpl->setupEvents();

	return true;
}

Puppet::Impl::Impl(Puppet* parent)
	: m_parent(parent)
{

}

Puppet::Impl::~Impl() = default;

void Puppet::Impl::setupEvents()
{

}
