#include "LayerGame.h"

bool LayerGame::init()
{
	Layer::init();

	/* 027. 三个子层，层次图见：
	3.LayerGame的渲染树和继承关系图*/
	_model = LayerModel::create();
	addChild(_model);

	_ai = LayerAI::create(_model);
	addChild(_ai);

	_ctrl = LayerCtrl::create(_model);
	addChild(_ctrl);

	return true;
}