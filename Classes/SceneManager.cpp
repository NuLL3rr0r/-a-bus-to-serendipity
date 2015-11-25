#include <mutex>
#include "GameScene.hpp"
#include "MainMenuScene.hpp"
#include "SceneManager.hpp"

using namespace std;
using namespace cocos2d;

struct SceneManager::Impl
{
	static const float SCENE_TRANSITION_DURATION;

	static mutex sceneManagerMutex;
	static SceneManager* sceneManagerInstance;

	Impl();
	~Impl();
};

const float SceneManager::Impl::SCENE_TRANSITION_DURATION(0.5f);

mutex SceneManager::Impl::sceneManagerMutex;
SceneManager* SceneManager::Impl::sceneManagerInstance = nullptr;

SceneManager* SceneManager::getInstance()
{
	lock_guard<mutex> lock(Impl::sceneManagerMutex);
	(void)lock;

	if (!Impl::sceneManagerInstance)
	{
		Impl::sceneManagerInstance = new (std::nothrow) SceneManager();
		CCASSERT(Impl::sceneManagerInstance, "FATAL: Not enough memory!");
		Impl::sceneManagerInstance->init();
		Impl::sceneManagerInstance->autorelease();
	}

	return Impl::sceneManagerInstance;
}

SceneManager::SceneManager()
	: m_pimpl(make_unique<SceneManager::Impl>())
{

}

SceneManager::~SceneManager()
{
	Impl::sceneManagerInstance = nullptr;
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

SceneManager::Impl::Impl()
{

}

SceneManager::Impl::~Impl()
{

}
