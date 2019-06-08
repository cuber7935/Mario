#include "LayerAI.h"

LayerAI * LayerAI::create(LayerModel * model)
{
	LayerAI* ret = new LayerAI;
	ret->_model = model;
	ret->init();
	ret->autorelease();
	return ret;
}

bool LayerAI::init()
{
	if (!Layer::init())
		return false;

	// ���ü�����1����ֹʹ�� ���ͷŵĶ���
	_model->retain();

	// ������ʱ���� ����ɫ�Ƿ��˶�
	schedule(schedule_selector(LayerAI::checkRunning));

	// ����һ�� role���� ���ݣ����ź��򣩣� ��ֹʹ��Դ���ݲ�������
	this->loadModelDataAndSort();

	return true;
}

// ��ȡ Դmodel �д�Ž�ɫ�ǵ����ݣ����ز�����
void LayerAI::loadModelDataAndSort()
{
	for (auto it = _model->_roles.begin(); it != _model->_roles.end(); ++it)
	{
		Role* role = *it;
		/* ����ʱ��˳������ */
		// �����MarioԶ�Ĺ��������ǰͷ
		int stopSize = _stopRoles.size();
		for (int idx = 0; idx < stopSize; ++idx)
		{
			Role* roleInStop = _stopRoles.at(idx);
			if (role->getPositionX() < roleInStop->getPositionX())
			{
				_stopRoles.insert(idx, role);
				break;
			}
		}
		if (stopSize == _stopRoles.size())
		{
			_stopRoles.pushBack(role);
		}
	}
}

void LayerAI::checkRunning(float)
{
	if (_stopRoles.size() == 0)
	{
		return;
	}

	Role* role = *_stopRoles.begin();
	
	// �ж�role�ǲ����ڴ����ұ�
	Rect rcRole = role->getBoundingBox();
	Vec2 ptInMap = Vec2(rcRole.getMinX(), rcRole.getMinY());

	Vec2 ptInWorld = _model->getCurTiledMap()->convertToWorldSpace(ptInMap);
	if (ptInWorld.x <= winSize.width)
	{
		role->setRunning(true);
		_stopRoles.erase(0);
	}
}

void LayerAI::onExit()
{
	Layer::onExit();

	_model->release();
}