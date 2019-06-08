#ifndef _LAYER_MODEL_H_
#define _LAYER_MODEL_H_

#include "Util.h"
#include "Role.h"
#include "RoleMario.h"
#define util Util::getInstance()

// 存放各种数据的层
class LayerModel : public Layer
{
public:
	CREATE_FUNC(LayerModel);

	virtual bool init()override;

	// 碰撞检测 处理函数
	void collision(float dt);

	/* for mario */
	void jump();
	void moveLeft();
	void moveRight();
	void stop();

	// 获取当前地图
	TMXTiledMap* getCurTiledMap()const;

private:
	// 初始化地图
	void initMap();

	// 初始化角色们
	void initRoles();

	// boss 发射子弹事件
	void initBossFireEvent();

	// 切断桥事件
	void initBreakBridgeEvent();

	// Mario 顶动 砖头 事件
	void initHitBlockEvent();

	// BOSS发射子弹 处理函数
	void bossFire(EventCustom* ev);

	// 切断桥 处理函数
	void breakBridge(EventCustom*);

	// Mario 顶动砖头 处理函数
	void hitBlock(EventCustom* ev);

	// 切断桥
	void breakBridge1(Vec2 pos, int idx);
	
	// 滚动地图
	void scrollMap();

	// 判断游戏是否结束
	void isGameOver();

	// 吃金币
	void eatCoin();

public:
	Vector<Role*>	_roles;               // 存放各种角色，以便和英雄做碰撞检测

private:
	TMXTiledMap*	_map	= nullptr;    // 地图
	RoleMario*		_mario  = nullptr;    // 英雄
	Role*			_bridge = nullptr;    // 桥
};

#endif

