#ifndef  __MAKE_UNIQUE_HPP__
#define  __MAKE_UNIQUE_HPP__

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <memory>
#include <utility>

namespace std {
	template<typename T, typename ...Args>
	std::unique_ptr<T> make_unique(Args&& ...args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#endif // __MAKE_UNIQUE_HPP__
