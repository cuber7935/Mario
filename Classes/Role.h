#ifndef _ROLE_H_
#define _ROLE_H_

#include "Util.h"
#define util Util::getInstance()

class Role : public Sprite
{
public:
	/* 工厂创建函数 */
	static Role* create(ValueMap& objProperty);
	virtual bool init(ValueMap& objProperty);

	void update(float);

	// 动画操作
public: 
	void runAnimation(const char* name);
	void stopAnimation();

	// 通过帧名 设置精灵帧
	void setSpriteFrame(const char* name);

	// 设置角色的状态（运动，朝向，更新状态）
public:
	virtual void setRunning(bool run);
	virtual void setRight(bool right);
	virtual void setDead(bool deadByHit);
	virtual void updateStatus(){}
	
	// 移动操作
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
	int _gravity = 10;
	int _speedDown = _gravity;
	int _speed = 120;
	int _speedUp = 0;

	bool _right = true;  // 朝向 
	bool _running = false; // 是否行走, 如果是怪物，表示该怪物已经参与游戏 
	bool _dead = false;
	bool _deadByHit = false; // deadBy...;

	bool _godMode = false; // 无敌模式

	Action* _animate = nullptr;
	static TMXTiledMap* _map;

	CC_PROPERTY(std::string, _type, Type);
#if 0
	// 获取首帧
	void setSpriteFrameByAnimation(const char* name);

	// 装载上帝模式
	void setGodMode(float duration);

	// 卸载上帝模式
	void unsetGodMode();
#endif
};

#endif

