#ifndef  MAKE_UNIQUE_HPP
#define  MAKE_UNIQUE_HPP

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

#endif // MAKE_UNIQUE_HPP
