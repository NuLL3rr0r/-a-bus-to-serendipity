#ifndef  __MAKE_UNIQUE_HPP__
#define  __MAKE_UNIQUE_HPP__

#ifdef __ANDROID__

#include <memory>
#include <utility>

namespace std {
	template<typename T, typename ...Args>
	std::unique_ptr<T> make_unique(Args&& ...args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}

#endif // __ANDROID__

#endif // __MAKE_UNIQUE_HPP__
