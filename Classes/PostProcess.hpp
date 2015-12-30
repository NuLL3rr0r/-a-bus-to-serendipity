#ifndef POST_PROCESS_HPP
#define POST_PROCESS_HPP

#include <memory>
#include <string>
#include "cocos2d.h"

class PostProcess : public cocos2d::Layer
{
private:
	struct Impl;
	std::unique_ptr<Impl> m_pimpl;

public:
	static PostProcess* create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

private:
	PostProcess();
	virtual ~PostProcess();
public:
	virtual bool init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

public:
	void draw(cocos2d::Layer* layer);
};

#endif // POST_PROCESS_HPP
