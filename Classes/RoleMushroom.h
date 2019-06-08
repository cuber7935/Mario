
#ifndef __RoleMushroom_H__
#define __RoleMushroom_H__


#include "Role.h"

class RoleMushroom : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	virtual void updateStatus()override;

	// �ƶ������������£�
	virtual void moveLeft(float dt)override;
	virtual void moveRight(float dt)override;
	virtual void moveDown(float dt)override;

	CollisionResult collsion(Role* mario, const Rect& rcMario);
};


#endif
