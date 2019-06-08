#ifndef __LayerAI_H__
#define __LayerAI_H__

#include "Util.h"
#include "LayerModel.h"

class LayerAI : public Layer
{
public:
	static LayerAI* create(LayerModel* model);

	virtual bool init()override;

	void onExit();
	
	// 定时器 处理函数（判断角色们是否运动）
	void checkRunning(float);

	// 源model 中存放角色们的数据 （加载并排序）
	void loadModelDataAndSort();

private:
	LayerModel*		_model = nullptr;
	Vector<Role*>	_stopRoles;
};

#endif

