#include <mutex>
#include "GameScene.hpp"
#include "MainMenuScene.hpp"
#include "SceneManager.hpp"

using namespace std;
using namespace cocos2d;

struct SceneManager::Impl
{
	static const float SCENE_TRANSITION_DURATION;

	static mutex SceneManagerMutex;
	static SceneManager* SceneManagerInstance;
};

const float SceneManager::Impl::SCENE_TRANSITION_DURATION(0.5f);

mutex SceneManager::Impl::SceneManagerMutex;
SceneManager* SceneManager::Impl::SceneManagerInstance = nullptr;

SceneManager* SceneManager::getInstance()
{
	lock_guard<mutex> lock(Impl::SceneManagerMutex);
	(void)lock;

	if (!Impl::SceneManagerInstance)
	{
		Impl::SceneManagerInstance = new (std::nothrow) SceneManager();
		CCASSERT(Impl::SceneManagerInstance, "FATAL: Not enough memory!");
		Impl::SceneManagerInstance->init();
		Impl::SceneManagerInstance->autorelease();
	}

	return Impl::SceneManagerInstance;
}

SceneManager::SceneManager()
	: m_pimpl(make_unique<SceneManager::Impl>())
{

}

SceneManager::~SceneManager()
{
	Impl::SceneManagerInstance = nullptr;
}

bool SceneManager::init()
{
	return true;
}

void SceneManager::run()
{
	Director::getInstance()->runWithScene(MainMenuScene::create());
}

void SceneManager::load(Scene& scene)
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
