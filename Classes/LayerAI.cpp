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

	// 引用计数加1，防止使用 已释放的对象
	_model->retain();

	// 启动定时器， 检测角色是否运动
	schedule(schedule_selector(LayerAI::checkRunning));

	// 复制一份 role集合 数据（并排好序）， 防止使用源数据操作，损坏
	this->loadModelDataAndSort();

	return true;
}

// 获取 源model 中存放角色们的数据（加载并排序）
void LayerAI::loadModelDataAndSort()
{
	for (auto it = _model->_roles.begin(); it != _model->_roles.end(); ++it)
	{
		Role* role = *it;
		/* 插入时，顺便排序 */
		// 最好离Mario远的怪物，在数组前头
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
	
	// 判断role是不是在窗口右边
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