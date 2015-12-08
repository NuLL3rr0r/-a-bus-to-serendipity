#ifndef  ANDROID_HPP
#define  ANDROID_HPP

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <functional>
#include <memory>
#include <string>
#include "cocos2d.h"

class Android : public cocos2d::Ref
{
public:
	enum class ScreenOrientation : const unsigned char {
		Undefined = 0,
		Portrait = 1,
		Landscape = 2,
		Square = 3	// This constant was deprecated in API level 16. Not currently supported or used.
	};

	typedef std::function<void(const ScreenOrientation&)> ScreenOrientationChangedHandler_t;

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

#endif // ANDROID_HPP
