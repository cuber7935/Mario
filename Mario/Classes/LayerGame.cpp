#include "LayerGame.h"

bool LayerGame::init()
{
	Layer::init();

	/* 027. �����Ӳ㣬���ͼ����
	3.LayerGame����Ⱦ���ͼ̳й�ϵͼ*/
	_model = LayerModel::create();
	addChild(_model);

	_ai = LayerAI::create(_model);
	addChild(_ai);

	_ctrl = LayerCtrl::create(_model);
	addChild(_ctrl);

	return true;
}