#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TouchLayer :public Layer {
public:
	virtual bool init();
	CREATE_FUNC(TouchLayer);
	static TouchLayer* createTouchLayer();
	EventListenerTouchOneByOne* touchlistener;
	void initEvent();
	void addWrongPlace(Point location);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
};