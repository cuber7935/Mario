#include "RoleFinalPoint.h"

bool RoleFinalPoint::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	/* ����Ģ����ͼƬ */
	//SpriteFrame* frame = SpriteFrame::create("Mushroom0.png", Rect(0, 0, 16, 16));
	//Sprite::setSpriteFrame(frame);

	this->setVisible(false);

	return true;
}

Role::CollisionResult RoleFinalPoint::collsion(Role* role, const Rect& rcMario)
{
	/* �յ��x���� */
	float finalX = this->getPositionX();

	if (rcMario.getMidX() > finalX)
	{
		return Role::CollisionResult::FINAL;
	}

	return Role::CollisionResult::Nothing;
}