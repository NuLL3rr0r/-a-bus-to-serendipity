#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    /*auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);*/
	
	map = TMXTiledMap::create("maps/my_desert.tmx");
	this->addChild(map, 0, 99); // with a tag of '99'
	for (const auto& child : map->getChildren())
	{
		//static_cast<SpriteBatchNode*>(child)->getTexture()->setAliasTexParameters();
		//static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event){
		float step = 10.0f;

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode){
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			direction = "LEFT";
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			direction = "RIGHT";
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			direction = "UP";
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			direction = "DOWN";
			break;
		}
	};

	eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		direction = "";
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, map);
	this->scheduleUpdate();

    return true;
}


void HelloWorld::update(float delta) {
	float step = 100.0f * delta;

	Vec2 loc = map->getPosition();
	if (direction == "LEFT") {
		map->setPosition(loc.x - step, loc.y);
	}
	else if (direction == "RIGHT") {
		map->setPosition(loc.x + step, loc.y);
	}
	else if (direction == "UP") {
		map->setPosition(loc.x, loc.y + step);
	}
	else if (direction == "DOWN") {
		map->setPosition(loc.x, loc.y - step);
	}
	else {
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
