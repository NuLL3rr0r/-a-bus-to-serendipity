#ifndef PUPPET_HPP
#define PUPPET_HPP

#include <memory>
#include "cocos2d.h"

class Puppet : public cocos2d::Node
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static Puppet* create();

private:
	Puppet();
	virtual ~Puppet();
public:
	virtual bool init() override;
};

#endif // PUPPET_HPP
