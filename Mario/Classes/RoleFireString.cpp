#include "RoleFireString.h"

bool RoleFireString::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	_begAngle = objProperty["begAngle"].asInt();
	_time = objProperty["time"].asInt();

	this->setRotation(_begAngle);

	RotateBy* r = RotateBy::create(_time, 360);
	RepeatForever* rep = RepeatForever::create(r);
	this->runAction(rep);

	this->setTexture("fireRight.png");
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	this->setScale(.5f, 0.7f);

	return true;
}

Role::CollisionResult RoleFireString::collsion(Role* role, const Rect& rcMario)
{
	int angle = this->getRotation();
	angle %= 360;

	Vec2 ptFire1;
	Vec2 ptFire2;

	Rect rc = getBoundingBox();

	if (angle < 90)
	{
		ptFire1 = Vec2(rc.getMinX(), rc.getMaxY());
		ptFire2 = Vec2(rc.getMaxX(), rc.getMinY());
	}
	else if (angle < 180)
	{
		ptFire1 = Vec2(rc.getMinX(), rc.getMinY());
		ptFire2 = Vec2(rc.getMaxX(), rc.getMaxY());
	}
	else if (angle < 270)
	{
		ptFire1 = Vec2(rc.getMinX(), rc.getMaxY());
		ptFire2 = Vec2(rc.getMaxX(), rc.getMinY());
	}
	else
	{
		ptFire1 = Vec2(rc.getMinX(), rc.getMinY());
		ptFire2 = Vec2(rc.getMaxX(), rc.getMaxY());
	}

	Vec2 ptMario1 = Vec2(rcMario.getMinX(), rcMario.getMinY());
	Vec2 ptMario2 = Vec2(rcMario.getMaxX(), rcMario.getMaxY());
	Vec2 ptMario3 = Vec2(rcMario.getMinX(), rcMario.getMaxY());
	Vec2 ptMario4 = Vec2(rcMario.getMaxX(), rcMario.getMinY());

	if (ccpSegmentIntersect(ptFire1, ptFire2, ptMario1, ptMario2))
	{
		return CollisionResult::MarioDie;
	}
	else if (ccpSegmentIntersect(ptFire1, ptFire2, ptMario3, ptMario4))
	{
		return CollisionResult::MarioDie;
	}

	return Role::CollisionResult::Nothing;
}