#include <mutex>
#include "make_unique.hpp"
#include "InputManager.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct InputManager::Impl
{
public:
	static mutex mutex_;
	static InputManager* instance_;

public:
	bool isTouchDown;
	float initialTouchPos[2];
	float currentTouchPos[2];

private:
	InputManager* m_parent;

public:
	explicit Impl(InputManager* parent);
	~Impl();

public:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event *event);

public:
	void createKeyboardListener();
	void createTouchListener();
	void setupEvents();
};

mutex InputManager::Impl::mutex_;
InputManager* InputManager::Impl::instance_ = nullptr;

InputManager* InputManager::getInstance()
{
	lock_guard<mutex> lock(Impl::mutex_);
	(void)lock;

	if (!Impl::instance_) {
		Impl::instance_ = new (std::nothrow) InputManager();
		CCASSERT(Impl::instance_, "FATAL: Not enough memory!");
		Impl::instance_->init();
		Impl::instance_->autorelease();
	}

	return Impl::instance_;
}

InputManager::InputManager()
	: m_pimpl(make_unique<InputManager::Impl>(this))
{

}

InputManager::~InputManager()
{
	Impl::instance_ = nullptr;
}

bool InputManager::init()
{
	if (!Impl::instance_) {
		return false;
	}

	if (!Node::init()) {
		return false;
	}

	m_pimpl->setupEvents();

	this->scheduleUpdate();

	return true;
}

void InputManager::update(float delta)
{
	if (m_pimpl->isTouchDown) {
		if (m_pimpl->initialTouchPos[0] - m_pimpl->currentTouchPos[0] > VisibleRect::width() * 0.05) {
			keyPressedSignal.emit(Key::PLAYER_LEFT);
			m_pimpl->isTouchDown = false;
		}
		else if (m_pimpl->initialTouchPos[1] - m_pimpl->currentTouchPos[1] < -VisibleRect::width() * 0.05) {
			keyPressedSignal.emit(Key::PLAYER_UP);
			m_pimpl->isTouchDown = false;
		}
		else if (m_pimpl->initialTouchPos[0] - m_pimpl->currentTouchPos[0] < -VisibleRect::width() * 0.05) {
			keyPressedSignal.emit(Key::PLAYER_RIGHT);
			m_pimpl->isTouchDown = false;
		}
		else if (m_pimpl->initialTouchPos[1] - m_pimpl->currentTouchPos[1] > VisibleRect::width() * 0.05) {
			keyPressedSignal.emit(Key::PLAYER_DOWN);
			m_pimpl->isTouchDown = false;
		}
	}
}

InputManager::Impl::Impl(InputManager *parent)
	: m_parent(parent)
{

}

InputManager::Impl::~Impl() = default;

bool InputManager::Impl::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event)
{
	initialTouchPos[0] = touch->getLocation().x;
	initialTouchPos[1] = touch->getLocation().y;
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;
	isTouchDown = true;

	return true;
}

void InputManager::Impl::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;
}

void InputManager::Impl::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{
	isTouchDown = false;
}

void InputManager::Impl::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event *event)
{
	onTouchEnded(touch, event);
}

void InputManager::Impl::createKeyboardListener()
{
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			InputManager::getInstance()->keyPressedSignal.emit(InputManager::Key::ESC);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			InputManager::getInstance()->keyPressedSignal.emit(InputManager::Key::PLAYER_LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			InputManager::getInstance()->keyPressedSignal.emit(InputManager::Key::PLAYER_UP);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			InputManager::getInstance()->keyPressedSignal.emit(InputManager::Key::PLAYER_RIGHT);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			InputManager::getInstance()->keyPressedSignal.emit(InputManager::Key::PLAYER_DOWN);
			break;
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, m_parent);
}

void InputManager::Impl::createTouchListener()
{
	isTouchDown = false;

	initialTouchPos[0] = 0;
	initialTouchPos[1] = 0;
	currentTouchPos[0] = 0;
	currentTouchPos[1] = 0;

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->setSwallowTouches(true);

	eventListener->onTouchBegan = CC_CALLBACK_2(Impl::onTouchBegan, this);
	eventListener->onTouchMoved = CC_CALLBACK_2(Impl::onTouchMoved, this);
	eventListener->onTouchEnded = CC_CALLBACK_2(Impl::onTouchEnded, this);
	eventListener->onTouchCancelled = CC_CALLBACK_2(Impl::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, m_parent);
}

void InputManager::Impl::setupEvents()
{
	createKeyboardListener();
	createTouchListener();
}
