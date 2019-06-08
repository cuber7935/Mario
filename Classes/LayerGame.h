#ifndef _LAYER_GAME_H_
#define _LAYER_GAME_H_

#include "Util.h"
#include "LayerModel.h"
#include "LayerAI.h"
#include "LayerCtrl.h"

// ”Œœ∑≥°æ∞ 
class LayerGame : public Layer
{
public:
	CREATE_FUNC(LayerGame);

	virtual bool init()override;

private:
	LayerModel*		_model = nullptr;
	LayerAI*		_ai    = nullptr;
	LayerCtrl*		_ctrl  = nullptr;
};

#endif

