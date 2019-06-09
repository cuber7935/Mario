#ifndef _ROLE_FLY_FISH_H_
#define _ROLE_FLY_FISH_H_

#include "Role.h"

// ����
class RoleFlyFish : public Role
{
public:
	virtual bool init(ValueMap& objProperty);
	void updateStatus();
	virtual CollisionResult collsion(Role*, const Rect&);

private:
	//�ص����� ���л� ���ҷ���
	void callback();

	int _duration;    // ����ʱ��
	int _offsetH;     // ˮƽƫ��
	int _offsetV;     // ��ֱƫ��

	Vec2 _ori;        // ��ǰ��
	Vec2 _dst;        // Ŀ���
};

#endif
