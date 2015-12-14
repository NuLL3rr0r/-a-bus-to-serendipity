#include <mutex>
#include "make_unique.hpp"
#include "GameScene.hpp"
#include "MainMenuScene.hpp"
#include "SceneManager.hpp"

using namespace std;
using namespace cocos2d;

struct SceneManager::Impl
{
public:
	static const float SCENE_TRANSITION_DURATION;

	static mutex mutex_;
	static SceneManager* instance_;

private:
	SceneManager* m_parent;

public:
	explicit Impl(SceneManager* parent);
	~Impl();
};

const float SceneManager::Impl::SCENE_TRANSITION_DURATION(0.5f);

mutex SceneManager::Impl::mutex_;
SceneManager* SceneManager::Impl::instance_ = nullptr;

SceneManager* SceneManager::getInstance()
{
	lock_guard<mutex> lock(Impl::mutex_);
	(void)lock;

	if (!Impl::instance_) {
		Impl::instance_ = new (std::nothrow) SceneManager();
		CCASSERT(Impl::instance_, "FATAL: Not enough memory!");
		Impl::instance_->init();
		Impl::instance_->autorelease();
	}

	return Impl::instance_;
}

SceneManager::SceneManager()
	: m_pimpl(make_unique<SceneManager::Impl>(this))
{

}

SceneManager::~SceneManager()
{
	Impl::instance_ = nullptr;
}

bool SceneManager::init()
{
	return true;
}

void SceneManager::run()
{
	Director::getInstance()->runWithScene(MainMenuScene::create());
}

void SceneManager::load(const Scene& scene)
{
	auto director = Director::getInstance();
	cocos2d::Scene *s;

	switch (scene) {
	case Scene::MainMenu:
		s = MainMenuScene::create();
		break;
	case Scene::Game:
		s = GameScene::create();
		break;
	default:
		CCASSERT(false, "FATAL: Invalid scene!");
		break;
	}

	director->replaceScene(TransitionFade::create(Impl::SCENE_TRANSITION_DURATION, s));
}

SceneManager::Impl::Impl(SceneManager *parent)
	: m_parent(parent)
{

}

SceneManager::Impl::~Impl() = default;
