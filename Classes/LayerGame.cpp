#include "LayerGame.h"

bool LayerGame::init()
{
	if (!Layer::init())
		return false;

	// �����Ӳ㣬���ͼ����
	// LayerGame����Ⱦ���ͼ̳й�ϵͼ
	_model = LayerModel::create();
	this->addChild(_model);

	_ai = LayerAI::create(_model);
	this->addChild(_ai);

	_ctrl = LayerCtrl::create(_model);
	this->addChild(_ctrl);

	return true;
}