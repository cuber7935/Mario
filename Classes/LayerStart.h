#ifndef _LAYER_START_H_
#define _LAYER_START_H_

#include "Util.h"

/* 开场第一个场景 */
class LayerStart : public Layer
{
public:
	CREATE_FUNC(LayerStart);
	virtual bool init()override;

private:
	//菜单项类型
	enum class ItemType { Start, Setting, Quit, About };

	//创建背景
	void createBG();

	//按钮选项
	void createItems();

	//开始游戏
	//void startGame();

	//菜单项回调函数
	void itemsCallback(Ref* ref);
};

#endif

