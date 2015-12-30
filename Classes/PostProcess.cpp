#include "make_unique.hpp"
#include "PostProcess.hpp"
#include "VisibleRect.hpp"

using namespace std;
using namespace cocos2d;

struct PostProcess::Impl
{
public:
	GLProgram* glProgram;
	RenderTexture* renderTexture;
	Sprite* sprite;

private:
	PostProcess* m_parent;

public:
	explicit Impl(PostProcess* parent);
	~Impl();
};

PostProcess* PostProcess::create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	auto p = new (std::nothrow) PostProcess();
	if (p && p->init(vertexShaderFile, fragmentShaderFile)) {
		p->autorelease();
		return p;
	}
	else {
		CC_SAFE_DELETE(p);
		return nullptr;
	}
}

PostProcess::PostProcess()
	: m_pimpl(make_unique<PostProcess::Impl>(this))
{

}

PostProcess::~PostProcess()
{
	m_pimpl->renderTexture->release();
}

bool PostProcess::init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	if (!Layer::init()) {
		return false;
	}

	m_pimpl->glProgram = GLProgram::createWithFilenames(vertexShaderFile, fragmentShaderFile);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_POSITION);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_COLOR);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	m_pimpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	m_pimpl->glProgram->link();
	m_pimpl->glProgram->updateUniforms();

	m_pimpl->renderTexture = RenderTexture::create(VisibleRect::width(), VisibleRect::height());
	m_pimpl->renderTexture->retain();

	m_pimpl->sprite = Sprite::createWithTexture(m_pimpl->renderTexture->getSprite()->getTexture());
	m_pimpl->sprite->setTextureRect(Rect(0, 0, m_pimpl->sprite->getTexture()->getContentSize().width,
		m_pimpl->sprite->getTexture()->getContentSize().height));
	m_pimpl->sprite->setAnchorPoint(Point::ZERO);
	m_pimpl->sprite->setPosition(Point::ZERO);
	m_pimpl->sprite->setFlippedY(true);
	m_pimpl->sprite->setGLProgram(m_pimpl->glProgram);
	this->addChild(m_pimpl->sprite);

	return true;
}

void PostProcess::draw(cocos2d::Layer* layer)
{
	m_pimpl->renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	layer->visit();
	m_pimpl->renderTexture->end();

	m_pimpl->sprite->setTexture(m_pimpl->renderTexture->getSprite()->getTexture());
}

PostProcess::Impl::Impl(PostProcess* parent)
	: m_parent(parent)
{

}

PostProcess::Impl::~Impl() = default;
