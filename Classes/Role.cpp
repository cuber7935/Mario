#include "Role.h"
#include "RoleMushroom.h"
#include "RoleFinalPoint.h"
#include "RoleFlagPoint.h"
#include "RoleFlower.h"
#include "RoleMario.h"
#include "RoleMushroomAddLife.h"
#include "RoleMushroomReward.h"
#include "RoleTortoise.h"
#include "RoleFlyFish.h"
#include "RoleTortoiseRound.h"
#include "RoleLadderLR.h"
#include "RoleTortoiseFly.h"
#include "RoleFireString.h"
#include "RoleBoss.h"
#include "RoleBossBullet.h"
#include "RoleBridgeStart.h"

TMXTiledMap* Role::_map;

// ������ɫ��������Ĵ������������Ǵ�������Ķ��󣬶��Ǳ�������
Role* Role::create(ValueMap& objProperty)
{
	Role* role = nullptr;
	ZOrder order = ZOrder::RoleNormal;

	std::string type = objProperty["type"].asString();
	if (type == "mushroom")
		role = new RoleMushroom;
	if (type == "finalpoint")
		role = new RoleFinalPoint;
	if (type == "flagpoint")
		role = new RoleFlagPoint;
	if (type == "flower")
	{
		order = ZOrder::Flower;
		role = new RoleFlower;
	}
	if (type == "BirthPoint")
		role = new RoleMario;

	if (type == "MushroomAddLife")
	{
		role = new RoleMushroomAddLife;
		order = ZOrder::MushroomAddLife;
	}
	if (type == "MushroomReward")
	{
		order = ZOrder::MushroomReward;
		role = new RoleMushroomReward;
	}
	if (type == "tortoise")
		role = new RoleTortoise;

	if (type == "flyfish")
		role = new RoleFlyFish;

	if (type == "tortoise_round")
		role = new RoleTortoiseRound;

	if (type == "ladderLR")
		role = new RoleLadderLR;

	if (type == "tortoise_fly")
		role = new RoleTortoiseFly; 

	if (type == "fire_string")
		role = new RoleFireString;
	if (type == "boss")
		role = new RoleBoss;
	if (type == "bossbullet")
		role = new RoleBossBullet;
	if (type == "bridgestartpos")
		role = new RoleBridgeStart;

	if (role)
	{
		role->init(objProperty);
		role->setLocalZOrder((int)order);
		role->autorelease();
	}
	return role;
}

void Role::setRunning(bool run)
{
	if (_running == run)return;
	_running = run;
	updateStatus();
}
void Role::setRight(bool right)
{
	if (_right == right)
		return;
	_right = right;
	updateStatus();
}

void Role::setDead(bool deadByHit)
{
	if (_dead) return;

	_dead = true;
	_deadByHit = deadByHit;
	updateStatus();
}


void Role::setSpriteFrame(const char* name)
{
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);

	Sprite::setSpriteFrame(frame);
}

void Role::stopAnimation()
{
	if (_animate)
	{
		stopAction(_animate);
		_animate = nullptr;
	}
}

void Role::runAnimation(const char* name)
{
	Animation* ani = AnimationCache::getInstance()->getAnimation(name);
	Animate* animate = Animate::create(ani);
	RepeatForever* rep = RepeatForever::create(animate);
	this->runAction(rep);
	_animate = rep;
}

bool Role::init(ValueMap& objProperty)
{
	Sprite::init();

	/* ���ý�ɫ��λ�� */
	int x = objProperty["x"].asInt();
	int y = objProperty["y"].asInt() - 16;
	this->setPosition(x, y);
	this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	setType(objProperty["type"].asString());

	scheduleUpdate();

	return true;
}

void Role::update(float dt)
{
	move(dt);
}


Sprite* Role::getHitBlock()
{
	Rect rc = this->getBoundingBox();
	Vec2 pt[3];
	pt[1] = Vec2(rc.getMinX(), rc.getMaxY());
	pt[0] = Vec2(rc.getMidX(), rc.getMaxY());
	pt[2] = Vec2(rc.getMaxX(), rc.getMaxY());

	return getHitBlock(pt);
}

Sprite* Role::getHitBlock(Vec2 pts[3])
{
	Sprite* ret = nullptr;

	TMXLayer* layerBlock = _map->getLayer("block");
	Size layerSize = layerBlock->getLayerSize();

	for (int i = 0; i < 3; ++i)
	{
		Vec2 ptInMap = util->convertToMap(pts[i], _map);
		if (ptInMap.x < layerSize.width && ptInMap.y < layerSize.height && ptInMap.x >= 0 && ptInMap.y >= 0)
		{
			ret = layerBlock->getTileAt(ptInMap);
			if (ret) break;
		}
	}

	return ret;
}

bool Role::isBlockUp()
{
	Rect rc = this->getBoundingBox();
	Vec2 pt[3];
	pt[0] = Vec2(rc.getMinX(), rc.getMaxY());
	pt[1] = Vec2(rc.getMidX(), rc.getMaxY());
	pt[2] = Vec2(rc.getMaxX(), rc.getMaxY());

	return isBlockForPts(pt);
}

bool Role::isBlockLeft()
{
	Rect rc = this->getBoundingBox();
	Vec2 pt[3];
	pt[0] = Vec2(rc.getMinX(), rc.getMinY());
	pt[1] = Vec2(rc.getMinX(), rc.getMidY());
	pt[2] = Vec2(rc.getMinX(), rc.getMaxY());

	return isBlockForPts(pt);
}

bool Role::isBlockRight()
{
	Rect rc = this->getBoundingBox();
	Vec2 pt[3];
	pt[0] = Vec2(rc.getMaxX(), rc.getMinY());
	pt[1] = Vec2(rc.getMaxX(), rc.getMidY());
	pt[2] = Vec2(rc.getMaxX(), rc.getMaxY());

	return isBlockForPts(pt);
}

/* �ж�����µĽ��£��Ƿ���block, pipe, land */
bool Role::isBlockDown()
{
	// 047. ��õײ��������꣬�жϸ����������Ӧ�ĵ�ͼ�ϣ��Ƿ��У�שͷ��block����ˮ�ܣ�pipe�������أ�land��
	// ѡ��ŵ���������
	Rect rc = this->getBoundingBox();
	Vec2 pt[3];
	pt[0] = Vec2(rc.getMinX(), rc.getMinY());
	pt[1] = Vec2(rc.getMidX(), rc.getMinY());
	pt[2] = Vec2(rc.getMaxX(), rc.getMinY());

	return isBlockForPts(pt);
}

// �ж��������Ƿ����赲
bool Role::isBlockForPts(Vec2 pts[3])
{
	for (int i = 0; i < 3; ++i)
	{
		// 049. ѭ�������㣬�����ж�ÿ�����Ƿ����赲
		if (isBLockForPt(pts[i])) return true;
	}

	return false;
}

// �ж�һ�����Ƿ����赲
bool Role::isBLockForPt(const Vec2& pt)
{
	const char* layerNames[3] = { "block", "pipe", "land" };
	for (int i = 0; i < 3; ++i)
	{
		if (isBlockForPtInLayer(pt, layerNames[i])) return true;
	}
	return false;
}

// �ж�ĳ���㣬��layerName��Ӧ�Ĳ��У��Ƿ����赲
bool Role::isBlockForPtInLayer(const Vec2& pt, const char* layerName)
{
	Vec2 ptInMap = util->convertToMap(pt, _map);
	TMXLayer* layer = _map->getLayer(layerName);

	Size _layerSize = layer->getLayerSize();

	/* �ж�ptInMap�ǲ��ǺϷ�������� */
	if (ptInMap.x < _layerSize.width && ptInMap.y < _layerSize.height && ptInMap.x >= 0 && ptInMap.y >= 0)
	{
		uint32_t gid = layer->getTileGIDAt(ptInMap);
		return gid != 0;
	}

	return false;
}

void Role::move(float dt)
{
	moveRight(dt);
	moveLeft(dt);
	moveUp(dt);
	moveDown(dt);
}

void Role::setType(std::string type)
{
	_type = type;
}

std::string Role::getType()const
{
	return _type;
}
#if 0
void Role::setStatus(Status status)
{
	_status = status;
}

Role::Status Role::getStatus()const
{
	return _status;
}
#endif
#if 0
void Role::setGodMode(float duration)
{
	// �ϵ�ģʽһ��ʹ�ð�͸������
	this->setOpacity(128);

	// �����ϵ�ģʽ
	_godMode = true;

	//DelayTime* delay = DelayTime::create(duration);
	// ��durationʱ���ȥ֮��������Ϊ���޵�ģʽ
	Blink* blink = Blink::create(duration, duration * 2);
	CallFunc* callf = CallFunc::create(CC_CALLBACK_0(Role::unsetGodMode, this));
	this->runAction(Sequence::create(blink, callf, NULL));
}

void Role::unsetGodMode()
{
	this->setOpacity(255);
	_godMode = false;
}

void Role::setSpriteFrameByAnimation(const char* name)
{
	Animation* ani = AnimationCache::getInstance()->getAnimation(name);
	Vector<AnimationFrame*> aniFrames = ani->getFrames();
	AnimationFrame* aniFrame = aniFrames.at(0);
	Sprite::setSpriteFrame(aniFrame->getSpriteFrame());
}

#endif