#ifndef  __ANDROID_HPP__
#define  __ANDROID_HPP__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <functional>
#include <memory>
#include <string>
#include "cocos2d.h"

class Android : public cocos2d::Ref
{
public:
	typedef std::function<void(int)> ScreenOrientationChangedHandler_t;

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static Android* getInstance();

private:
	Android();
	virtual ~Android();

public:
	void onScreenOrientationChanged(ScreenOrientationChangedHandler_t handler);

public:
	bool init();

	void debug(const std::string &log);
};

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif // __ANDROID_HPP__
