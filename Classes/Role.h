#ifndef _ROLE_H_
#define _ROLE_H_

#include "Util.h"
#define util Util::getInstance()

class Role : public Sprite
{
public:
	/* 工厂创建函数 */
	static Role* create(ValueMap& objProperty);

	//	初始化
	virtual bool init(ValueMap& objProperty);

	// 定时器处理函数（负责角色运动）
	void update(float);

	// 动画操作
public: 
	// 执行动画
	void runAnimation(const char* name);
	
	// 停止动画
	void stopAnimation();

	// 通过帧名 设置精灵帧
	void setSpriteFrame(const char* name);

	// 设置角色的状态（运动，朝向，死亡，更新状态）
public:
	virtual void setRunning(bool run);
	virtual void setRight(bool right);
	virtual void setDead(bool deadByHit);
	virtual void updateStatus(){}
	
	// 移动操作（左右上下）
public:
	virtual void move(float);

	virtual void moveLeft(float dt){}
	virtual void moveRight(float dt){}
	virtual void moveUp(float dt) {}
	virtual void moveDown(float dt) {}

	// 碰撞检测 相关操作
public:
	enum class CollisionResult { Nothing, MarioDie, RoleDie, EAT_MUSHROOM_REWARD, EAT_MUSHROOM_ADDLIFE, FINAL};
	virtual CollisionResult collsion(Role*, const Rect&){ return CollisionResult::Nothing; }

	// 检测是否顶砖块 相关操作
public:
	Sprite* getHitBlock();
	Sprite* getHitBlock(Vec2 pts[3]);

	bool isBlockUp();
	bool isBlockLeft();
	bool isBlockRight();
	bool isBlockDown();

	bool isBlockForPts(Vec2 pts[3]);
	bool isBLockForPt(const Vec2& pt);
	bool isBlockForPtInLayer(const Vec2& pt, const char* layerName);

	// 相关属性
public:
	int _gravity		= 10;			// 加速度
	int _speedDown		= _gravity;		// 向下速度（模拟 重力）
	int _speed			= 120;			// 水平速度
	int _speedUp		= 0;			// 向上速度

	bool _right			= true;			// 朝向 
	bool _running		= false;		// 是否行走, 如果是怪物，表示该怪物已经参与游戏 
	bool _dead			= false;
	bool _deadByHit		= false;		// deadBy...;

	Action* _animate	= nullptr;
	static TMXTiledMap* _map;

	CC_PROPERTY(std::string, _type, Type);
};

#endif

