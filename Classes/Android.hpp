#ifdef __ANDROID__

#ifndef  __ANDROID_HPP__
#define  __ANDROID_HPP__

#include <memory>
#include <string>
#include "cocos2d.h"

class Android : public cocos2d::Ref
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static Android* getInstance();

private:
	Android();
	virtual ~Android();

public:
	bool init();

	void debug(const std::string &log);
};

#endif // __ANDROID_HPP__

#endif // __ANDROID__
