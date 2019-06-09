#ifndef _ROLE_H_
#define _ROLE_H_

#include "Util.h"
#define util Util::getInstance()

class Role : public Sprite
{
public:
	/* ������������ */
	static Role* create(ValueMap& objProperty);

	//	��ʼ��
	virtual bool init(ValueMap& objProperty);

	// ��ʱ���������������ɫ�˶���
	void update(float);

	// ��������
public: 
	// ִ�ж���
	void runAnimation(const char* name);
	
	// ֹͣ����
	void stopAnimation();

	// ͨ��֡�� ���þ���֡
	void setSpriteFrame(const char* name);

	// ���ý�ɫ��״̬���˶�����������������״̬��
public:
	virtual void setRunning(bool run);
	virtual void setRight(bool right);
	virtual void setDead(bool deadByHit);
	virtual void updateStatus(){}
	
	// �ƶ��������������£�
public:
	virtual void move(float);

	virtual void moveLeft(float dt){}
	virtual void moveRight(float dt){}
	virtual void moveUp(float dt) {}
	virtual void moveDown(float dt) {}

	// ��ײ��� ��ز���
public:
	enum class CollisionResult { Nothing, MarioDie, RoleDie, EAT_MUSHROOM_REWARD, EAT_MUSHROOM_ADDLIFE, FINAL};
	virtual CollisionResult collsion(Role*, const Rect&){ return CollisionResult::Nothing; }

	// ����Ƿ�ש�� ��ز���
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

	// �������
public:
	int _gravity		= 10;			// ���ٶ�
	int _speedDown		= _gravity;		// �����ٶȣ�ģ�� ������
	int _speed			= 120;			// ˮƽ�ٶ�
	int _speedUp		= 0;			// �����ٶ�

	bool _right			= true;			// ���� 
	bool _running		= false;		// �Ƿ�����, ����ǹ����ʾ�ù����Ѿ�������Ϸ 
	bool _dead			= false;
	bool _deadByHit		= false;		// deadBy...;

	Action* _animate	= nullptr;
	static TMXTiledMap* _map;

	CC_PROPERTY(std::string, _type, Type);
};

#endif

