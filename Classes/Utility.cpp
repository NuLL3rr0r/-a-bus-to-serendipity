#include "Utility.hpp"

using namespace std;
using namespace cocos2d;

void Utility::drawAnchorPoint(cocos2d::Node* node, float radius, cocos2d::Color4F color)
{
#ifndef NDEBUG
	auto anchorPoint = DrawNode::create();
	anchorPoint->drawDot(Point(
		node->getContentSize().width * node->getAnchorPoint().x,
		node->getContentSize().height * node->getAnchorPoint().y),
		radius, color);
	node->addChild(anchorPoint);
#endif // NDEBUG
}
