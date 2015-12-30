#ifndef PUPPET_HPP
#define PUPPET_HPP

#include <memory>
#include "cocos2d.h"
#include "IGamePiece.hpp"

class Puppet : public cocos2d::Node, public IGamePiece
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
