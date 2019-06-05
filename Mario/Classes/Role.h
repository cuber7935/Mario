#ifndef __Role_H__
#define __Role_H__

#include "Util.h"
class Role : public Sprite
{
public:
	/* ������������ */
	static Role* create(ValueMap& objProperty);
	virtual bool init(ValueMap& objProperty);

	static TMXTiledMap* _map;
	void update(float);

	enum class Status{NONE, NORMAL};

	CC_PROPERTY(std::string, _type, Type);
	CC_PROPERTY(Status, _status, Status);

	Action* _animate = nullptr;
	void runAnimation(const char* name);
	void stopAnimation();

	void setSpriteFrameByAnimation(const char* name);
	void setSpriteFrame(const char* name);

	Sprite* getHitBlock();
	Sprite* getHitBlock(Vec2 pts[3]);

	bool isBlockUp();
	bool isBlockLeft();
	bool isBlockRight();
	bool isBlockDown();

	bool isBlockForPts(Vec2 pts[3]);
	bool isBLockForPt(const Vec2& pt);
	bool isBlockForPtInLayer(const Vec2& pt, const char* layerName);

	

	Util& util = Util::getInstance();

	int _gravity = 10;
	int _speedDown = _gravity;
	int _speed = 120;
	int _speedUp = 0;

	bool _godMode = false; // �޵�ģʽ

	// �ϵ�ģʽ������
	void setGodMode(float duration)
	{
		// �ϵ�ģʽһ��ʹ�ð�͸������
		this->setOpacity(128);

		// �����ϵ�ģʽ
		_godMode = true;

		//DelayTime* delay = DelayTime::create(duration);
		// ��durationʱ���ȥ֮��������Ϊ���޵�ģʽ
		Blink* blink = Blink::create(duration, duration*2);
		CallFunc* callf = CallFunc::create(CC_CALLBACK_0(Role::unsetGodMode, this));
		this->runAction(Sequence::create(blink, callf, NULL));
		
	}
	void unsetGodMode()
	{
		this->setOpacity(255);
		_godMode = false;
	}

	bool _right = true; /* ���� */
	bool _running = false; /* �Ƿ�����, ����ǹ����ʾ�ù����Ѿ�������Ϸ */
	
	bool _dead = false;
	bool _deadByHit = false; // deadBy...;

	virtual void setRunning(bool run);
	virtual void setRight(bool right);
	virtual void setDead(bool deadByHit);
	virtual void updateStatus(){}

	void moveDownAjust()
	{
		
		// ΢����ֵ�ǣ�������
		int y = this->getPositionY();
		y = y / 16 * 16;
		this->setPositionY(y);
	}

public:
	/* move */
	virtual void move(float);
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveUp(float dt);
	virtual void moveDown(float dt);

//	virtual bool canMove(TMXTiledMap*){ return true; }

	enum class CollisionResult { Nothing, MarioDie, RoleDie, EAT_MUSHROOM_REWARD, EAT_MUSHROOM_ADDLIFE, FINAL};
	virtual CollisionResult collsion(Role*, const Rect&){ return CollisionResult::Nothing; }
};

#endif

