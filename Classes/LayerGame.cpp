#include "LayerGame.h"

bool LayerGame::init()
{
	if (!Layer::init())
		return false;

	// 三个子层，层次图见：
	// LayerGame的渲染树和继承关系图
	_model = LayerModel::create();
	this->addChild(_model);

	_ai = LayerAI::create(_model);
	this->addChild(_ai);

	_ctrl = LayerCtrl::create(_model);
	this->addChild(_ctrl);

	return true;
}