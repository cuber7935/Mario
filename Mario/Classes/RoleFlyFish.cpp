#include "RoleFlyFish.h"

bool RoleFlyFish::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	_duration = objProperty["duration"].asInt();
	_offsetH = objProperty["offsetH"].asInt();
	_offsetV = objProperty["offsetV"].asInt();

	_ori = getPosition();
	_dst = _ori + Vec2(_offsetH, _offsetV);


//	runAnimation(ANI_FLYFISH_LEFT);

	updateStatus();

	return true;
}

void RoleFlyFish::updateStatus()
{
	//stopAllActions();
	stopAnimation();

	Vec2 dst;

	if (_right)
	{
		runAnimation(ANI_FLYFISH_RIGHT);
		dst = _dst;
	}
	else
	{
		runAnimation(ANI_FLYFISH_RIGHT);
		dst = _ori;
	}

	// Ö´ÐÐ±´Èû¶ûÇúÏß
	ccBezierConfig cfg;
	cfg.endPosition = dst;
	cfg.controlPoint_1 = Vec2(CCRANDOM_0_1()*_offsetH, CCRANDOM_0_1()*_offsetV) + _ori;
	cfg.controlPoint_2 = Vec2(CCRANDOM_0_1()*_offsetH, CCRANDOM_0_1()*_offsetV) + _ori;
	BezierTo* b = BezierTo::create(_duration, cfg);

	CallFunc* c = CallFunc::create(CC_CALLBACK_0(RoleFlyFish::callback, this));
	this->runAction(Sequence::createWithTwoActions(b, c));
}

Role::CollisionResult RoleFlyFish::collsion(Role* mario, const Rect& rcMario)
{
	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
	{		
		return CollisionResult::Nothing;
	}

	return Role::CollisionResult::MarioDie;
}

