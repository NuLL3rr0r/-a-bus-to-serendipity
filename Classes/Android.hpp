#ifndef  ANDROID_HPP
#define  ANDROID_HPP

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <functional>
#include <memory>
#include <string>
#include "wink/slot.hpp"
#include "wink/signal.hpp"
#include "cocos2d.h"

class Android : public cocos2d::Ref
{
public:
	enum class ScreenOrientation : const int {
		Undefined = 0,
		Portrait = 1,
		Landscape = 2,
		Square = 3	// This constant was deprecated in API level 16. Not currently supported or used.
	};

	typedef wink::slot<void (ScreenOrientation)> ScreenOrientationChangedSlot_t;
	typedef wink::signal<ScreenOrientationChangedSlot_t> ScreenOrientationChangedSignal_t;

private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	ScreenOrientationChangedSignal_t ScreenOrientationChangedSignal;

public:
	static Android* getInstance();

private:
	Android();
	virtual ~Android();

public:
	bool init();

	void debug(const std::string &log);
};

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif // ANDROID_HPP
