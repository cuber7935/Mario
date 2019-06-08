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

	enum class Status{NONE, NORMAL};

	CC_PROPERTY(std::string, _type, Type);
	CC_PROPERTY(Status, _status, Status);

	
	void runAnimation(const char* name);
	void stopAnimation();

	void setSpriteFrameByAnimation(const char* name);
	void setSpriteFrame(const char* name);

	// 上帝模式的设置
	void setGodMode(float duration);

	void unsetGodMode();

	virtual void setRunning(bool run);
	virtual void setRight(bool right);
	virtual void setDead(bool deadByHit);
	virtual void updateStatus(){}

	// 微调
	void moveDownAjust();

public:
	int _gravity	= 10;
	int _speedDown	= _gravity;
	int _speed		= 120;
	int _speedUp	= 0;

	bool _right		= true;  // 朝向 
	bool _running	= false; // 是否行走, 如果是怪物，表示该怪物已经参与游戏 
	bool _dead		= false;
	bool _deadByHit = false; // deadBy...;

	bool _godMode	= false; // 无敌模式

	Action* _animate = nullptr;
	static TMXTiledMap* _map;

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

public:
	/* move */
	virtual void move(float);

	virtual void moveLeft(float dt){}
	virtual void moveRight(float dt){}
	virtual void moveUp(float dt) {}
	virtual void moveDown(float dt) {}

	enum class CollisionResult { Nothing, MarioDie, RoleDie, EAT_MUSHROOM_REWARD, EAT_MUSHROOM_ADDLIFE, FINAL};
	virtual CollisionResult collsion(Role*, const Rect&){ return CollisionResult::Nothing; }
};

#endif

