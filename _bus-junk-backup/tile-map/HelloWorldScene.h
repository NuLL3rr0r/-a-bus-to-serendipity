#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <string>
#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float) override;

private:
	std::string direction;
	cocos2d::TMXTiledMap *map;
};

#endif // __HELLOWORLD_SCENE_H__
