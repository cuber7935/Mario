#ifndef __RoleTortoiseFly_H__
#define __RoleTortoiseFly_H__

#include "RoleTortoiseRound.h"

class RoleTortoiseFly : public RoleTortoiseRound
{
public:
	virtual bool init(ValueMap& objProperty);

	// �Ƿ��ڷ��к����ڽ��������
	bool _flying = true;    // false
	bool _dropping = false; // false

	// ����״̬
	void updateStatus();

	// �ƶ�����
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	CollisionResult collsion(Role*, const Rect&);
};

#endif

