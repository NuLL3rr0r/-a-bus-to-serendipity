#ifndef  APP_DELEGATE_HPP
#define  APP_DELEGATE_HPP

#include <memory>
#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	AppDelegate();
	virtual ~AppDelegate();

public:
	virtual bool applicationDidFinishLaunching() override;
	virtual void applicationDidEnterBackground() override;
	virtual void applicationWillEnterForeground() override;

	virtual void initGLContextAttrs() override;
};

#endif // APP_DELEGATE_HPP
