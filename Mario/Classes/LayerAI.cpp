#include "LayerAI.h"

bool LayerAI::init()
{
	Layer::init();

	_model->retain();

	schedule(schedule_selector(LayerAI::checkRunning));

//	_stopRoles = _model->_roles;
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

	return true;
}

void LayerAI::checkRunning(float)
{
	if (_stopRoles.size() == 0)
	{
		return;
	}
	//for (auto it = _stopRoles.begin(); it != _stopRoles.end(); )
	//{
		Role* role = *_stopRoles.begin();
		// 判断role是不是在窗口右边
		//Vec2 ptInMap = role->getPosition();
		Rect rcRole = role->getBoundingBox();
		Vec2 ptInMap = Vec2(rcRole.getMinX(), rcRole.getMinY());

		Vec2 ptInWorld = _model->_map->convertToWorldSpace(ptInMap);
		if (ptInWorld.x <= winSize.width)
		{
			role->setRunning(true);
			_stopRoles.erase(0);
		}
	//	else
	//	{
	//		break;
	//	}
	//}
#if 0
	Vector<Role*>& roles = _model->_roles;
	for (auto it = roles.begin(); it != roles.end(); ++it)
	{
		Role* role = *it;
		// 判断role是不是在窗口右边
		Vec2 ptInMap = role->getPosition();
		Vec2 ptInWorld = _model->_map->convertToWorldSpace(ptInMap);
		if (ptInWorld.x <= winSize.width)
		{
			role->setRunning(true);
			break;
		}
	}
#endif
}

void LayerAI::onExit()
{
	Layer::onExit();

	_model->release();
}