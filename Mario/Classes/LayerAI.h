#ifndef __LayerAI_H__
#define __LayerAI_H__

#include "Util.h"
#include "LayerModel.h"

class LayerAI : public Layer
{
public:
	//CREATE_FUNC(LayerAI);
	static LayerAI* create(LayerModel* model)
	{
		LayerAI* ret = new LayerAI;
		ret->_model = model;
		ret->init();
		ret->autorelease();
		return ret;
	}

	bool init();

	LayerModel* _model;
	void checkRunning(float);

	Vector<Role*> _stopRoles;

	void onExit();
};

#endif

