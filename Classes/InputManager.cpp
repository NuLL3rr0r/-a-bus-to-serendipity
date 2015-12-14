#include <mutex>
#include "make_unique.hpp"
#include "InputManager.hpp"

using namespace std;
using namespace cocos2d;

struct InputManager::Impl
{
public:
	static mutex mutex_;
	static InputManager* instance_;

private:
	InputManager* m_parent;

public:
	explicit Impl(InputManager* parent);
	~Impl();
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
	return true;
}

InputManager::Impl::Impl(InputManager *parent)
	: m_parent(parent)
{

}

InputManager::Impl::~Impl() = default;
