#ifndef _ROLE_TORTOISE_H_
#define _ROLE_TORTOISE_H_

#include "Role.h"

// ÎÚ¹ê
class RoleTortoise : public Role
{
public:
	virtual bool init(ValueMap& objProperty);
	void updateStatus();

	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	CollisionResult collsion(Role*, const Rect&);

	void setScared(bool scared);
	void setCrazy(bool crazy);

public:
	bool _bScared = false;      // ÊÜ¾ªÏÅ
	bool _bCrazy = false;       // ·è¿ñµÄ
};


#endif
