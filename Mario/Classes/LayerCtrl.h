#ifndef __LayerCtrl_H__
#define __LayerCtrl_H__

#include "Util.h"
#include "LayerModel.h"

class LayerCtrl : public Layer
{
public:
	//CREATE_FUNC(LayerCtrl);

	static LayerCtrl* create(LayerModel* model)
	{
		LayerCtrl* ret = new LayerCtrl;
		ret->_model = model;
		ret->init();
		ret->autorelease();
		return ret;
	}

	bool init();

	LayerModel* _model;
	void onExit();

	Sprite* _ctrlDir;

	//std::function<void(Ref*, Widget::TouchEventType)>

	void menuCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);
	void jumpCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);
	void fireCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	bool TouchBegan(Touch*, Event*);
	void TouchEnded(Touch*, Event*);
	void TouchMoved(Touch*, Event*);

	bool isTouchOnDirLeft(Touch*);
	bool isTouchOnDirRight(Touch*);

	void moveRight();
	void moveLeft();
	void stop();

#ifdef WIN32
	void checkKey(float);
#endif
};

#endif

