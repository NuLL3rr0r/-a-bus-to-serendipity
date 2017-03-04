#include <iomanip>
#include <string>
#include <sstream>
#include "make_unique.hpp"
#include "GameBoard.hpp"
#include "GameBoardSquare.hpp"
#include "GameScene.hpp"
#include "InputManager.hpp"
#include "PostProcess.hpp"
#include "Screen.hpp"
#include "Utility.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct GameScene::Impl
{
public:
	Sprite3D* sprite;
	Camera* cam3d;
	Camera* camera;
	Layer* gameLayer;
	PostProcess* grayPostProcessLayer;
	GameBoard* gameBoard;

private:
	GameScene* m_parent;

public:
	explicit Impl(GameScene* parent);
	~Impl();

public:
	void onInputKeyPressed(const InputManager::Key& key);

public:
	void setupEvents();
};

GameScene* GameScene::create()
{
	auto p = new (std::nothrow) GameScene();
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

GameScene::GameScene()
	: m_pimpl(make_unique<GameScene::Impl>(this))
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	//////////// TEST A - BEGIN

	Layer* gameLayer = Layer::create();
	this->addChild(gameLayer, 0);

	auto s = Director::getInstance()->getWinSize();
	Camera *camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);
	camera->setPosition3D(Vec3(0, 100, 100));
	camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
	gameLayer->addChild(camera); //add camera to the scene

	/*auto billboard = BillBoard::create("cocos2d-x.png", BillBoard::Mode::VIEW_POINT_ORIENTED);
	billboard->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
	gameLayer->addChild(billboard, 100);*/

	Sprite3D* sprite = Sprite3D::create("blend_test/character_3_animations_test.c3b");
	sprite->setScale(5.0f); //sets the object scale in float
	sprite->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	//sprite->setPosition3D(Vec3(VisibleRect::center().x, VisibleRect::center().y, 0.0f)); //sets sprite position
	sprite->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
	gameLayer->addChild(sprite, 1); //adds sprite to scene, z-index: 1

	Sprite* ss = Sprite::create("cocos2d-x.png");
	ss->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
	gameLayer->addChild(ss);

	GLProgram* glProgram = GLProgram::createWithFilenames("shaders/gray.vert", "shaders/gray.frag");
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_POSITION);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_COLOR);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	glProgram->link();
	glProgram->updateUniforms();

	RenderTexture* renderTexture = RenderTexture::create(VisibleRect::width(), VisibleRect::height());
	renderTexture->retain();

	Sprite* sprite2D = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	sprite2D->setTextureRect(Rect(0, 0, sprite2D->getTexture()->getContentSize().width,
	sprite2D->getTexture()->getContentSize().height));
	sprite2D->setAnchorPoint(Point::ZERO);
	sprite2D->setPosition(Point::ZERO);
	sprite2D->setFlippedY(true);
	sprite2D->setGLProgram(glProgram);
	this->addChild(sprite2D, 100);

	renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	// We should check for visiting camera here
	// or
	// we'll get a NULL camera inside BillBoard::calculateBillbaordTransform() function
	auto c = Camera::getVisitingCamera();
	//if (c) {
		auto renderer = _director->getRenderer();
		auto& parentTransform = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
		gameLayer->visit(renderer, parentTransform, true);
		//gameLayer->visit();
	//}
	renderTexture->end();
	sprite2D->setTexture(renderTexture->getSprite()->getTexture());

	//////////// TEST A - END

	/*m_pimpl->gameLayer = Layer::create();
	m_pimpl->gameLayer->setAnchorPoint(Point::ZERO);
	m_pimpl->gameLayer->setPosition(Point::ZERO);
	this->addChild(m_pimpl->gameLayer, 0);

	m_pimpl->grayPostProcessLayer = PostProcess::create("shaders/gray.vert", "shaders/gray.frag");
	m_pimpl->grayPostProcessLayer->setAnchorPoint(Point::ZERO);
	m_pimpl->grayPostProcessLayer->setPosition(Point::ZERO);
	this->addChild(m_pimpl->grayPostProcessLayer, 1);

	//m_pimpl->gameBoard = GameBoard::create();
	//m_pimpl->gameBoard->ignoreAnchorPointForPosition(false);
	//m_pimpl->gameBoard->setAnchorPoint(Vec2(0.5f, 0.5f));
	//m_pimpl->gameBoard->setPosition(VisibleRect::center().x, VisibleRect::center().y);
	//m_pimpl->gameLayer->addChild(m_pimpl->gameBoard, -1);

	auto s = Director::getInstance()->getWinSize();
	m_pimpl->camera = Camera::createPerspective(60, (GLfloat)s.width / s.height, 1, 1000);

	// set parameters for camera
	m_pimpl->camera->setPosition3D(Vec3(0, 100, 100));
	m_pimpl->camera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));

	m_pimpl->gameLayer->addChild(m_pimpl->camera); //add camera to the scene

	auto billboard = BillBoard::create("cocos2d-x.png", BillBoard::Mode::VIEW_POINT_ORIENTED);
	//auto s = Sprite::create("cocos2d-x.png");
	billboard->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
	m_pimpl->gameLayer->addChild(billboard, 100);


	sprite2d = Sprite3D::create("blend_test/character_3_animations_test.c3b");
	sprite2d->setScale(1.0f); //sets the object scale in float
	sprite2d->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
	//sprite->setPosition3D(Vec3(0.0f, 0.0f, 0.0f)); //sets sprite position
	sprite2d->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y));
	m_pimpl->gameLayer->addChild(sprite2d, 1000); //adds sprite to scene, z-index: 1

	//s->setGlobalZOrder(-100);
	//sprite->setGlobalZOrder(200);

	auto animation = Animation3D::create("blend_test/character_3_animations_test.c3b");
	//auto animate = Animate3D::create(animation);
	//sprite->runAction(RepeatForever::create(animate));

	auto animate1 = Animate3D::createWithFrames(animation, 0, 14, 30);
	auto animate2 = Animate3D::createWithFrames(animation, 15, 119, 30);
	auto animate3 = Animate3D::createWithFrames(animation, 120, 133, 30);
	sprite2d->runAction(RepeatForever::create(animate1));
	sprite2d->runAction(RepeatForever::create(animate2));
	sprite2d->runAction(RepeatForever::create(animate3));

	//auto glProgram = GLProgram::createWithFilenames("shaders/gray.vert", "shaders/gray.frag");
	//glProgram->link();
	//glProgram->updateUniforms();
	//sprite2d->setGLProgram(glProgram);


	//auto camera2D = Camera::createOrthographic(60, (GLfloat)VisibleRect::width() / VisibleRect::height(), 1, 1000);
	//auto camera2D = Camera::create();
	//m_pimpl->gameLayer->addChild(camera2D, 5000);

	//m_pimpl->cam3d = Camera::createPerspective(60, (GLfloat)VisibleRect::width() / VisibleRect::height(), 0.1, 200);
	//m_pimpl->cam3d->setPosition3D(Vec3(0.f, 0.f, 50.f));
	//m_pimpl->cam3d->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));
	//m_pimpl->gameLayer->addChild(m_pimpl->cam3d, 10000);

	auto ambientLight = AmbientLight::create(Color3B(200, 200, 200));
	ambientLight->setEnabled(true);
	m_pimpl->gameLayer->addChild(ambientLight); */

	this->addChild(InputManager::getInstance());

	m_pimpl->setupEvents();
	this->scheduleUpdate();

	return true;
}

void GameScene::update(float delta)
{
	//m_pimpl->grayPostProcessLayer->draw(sprite2d);
	//m_pimpl->grayPostProcessLayer->draw(m_pimpl->gameLayer);
	//m_pimpl->grayPostProcessLayer->draw(m_pimpl->camera);
}

GameScene::Impl::Impl(GameScene *parent)
	: m_parent(parent)
{

}

GameScene::Impl::~Impl()
{
	InputManager::getInstance()->keyPressedSignal.disconnect(this, &Impl::onInputKeyPressed);
}

void GameScene::Impl::onInputKeyPressed(const InputManager::Key& key)
{
	switch (key) {
	case InputManager::Key::START:
		CCLOG("START");
		break;
	case InputManager::Key::PLAYER_LEFT:
		CCLOG("LEFT");
		break;
	case InputManager::Key::PLAYER_UP:
		CCLOG("UP");
		break;
	case InputManager::Key::PLAYER_RIGHT:
		CCLOG("RIGHT");
		break;
	case InputManager::Key::PLAYER_DOWN:
		CCLOG("DOWN");
		break;
	}
}

void GameScene::Impl::setupEvents()
{
	InputManager::getInstance()->keyPressedSignal.connect(this, &Impl::onInputKeyPressed);
}
