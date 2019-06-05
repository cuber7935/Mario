#ifndef __LayerSelectMap_H__
#define __LayerSelectMap_H__

#include "Util.h"

/* 013. Ñ¡Ôñ¹Ø¿¨³¡¾° */
class LayerSelectMap : public Layer
{
public:
	CREATE_FUNC(LayerSelectMap);

	bool init();
	void initBG();
	void initScrollView();
	void initTouch();
	void initBackMenu();

	bool TouchBegan(Touch*, Event*);
	void TouchEnded(Touch*, Event*);
//	void TouchMoved(Touch*, Event*);

	void detectScrollViewMoving(float);
	float _lastScrollViewPosition;
	ScrollView* _view;
	void adjustView();
};

#endif

