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

// 创建角色，工厂类的创建函数，并非创建该类的对象，而是别的类对象
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

	/* 设置角色的位置 */
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

/* 判断马里奥的脚下，是否有block, pipe, land */
bool Role::isBlockDown()
{
	// 047. 获得底部三个坐标，判断该三个坐标对应的地图上，是否有：砖头（block）、水管（pipe），土地（land）
	// 选择脚底下三个点
	Rect rc = this->getBoundingBox();
	Vec2 pt[3];
	pt[0] = Vec2(rc.getMinX(), rc.getMinY());
	pt[1] = Vec2(rc.getMidX(), rc.getMinY());
	pt[2] = Vec2(rc.getMaxX(), rc.getMinY());

	return isBlockForPts(pt);
}

// 判断三个点是否有阻挡
bool Role::isBlockForPts(Vec2 pts[3])
{
	for (int i = 0; i < 3; ++i)
	{
		// 049. 循环三个点，依次判断每个点是否有阻挡
		if (isBLockForPt(pts[i])) return true;
	}

	return false;
}

// 判断一个点是否有阻挡
bool Role::isBLockForPt(const Vec2& pt)
{
	const char* layerNames[3] = { "block", "pipe", "land" };
	for (int i = 0; i < 3; ++i)
	{
		if (isBlockForPtInLayer(pt, layerNames[i])) return true;
	}
	return false;
}

// 判断某个点，在layerName对应的层中，是否有阻挡
bool Role::isBlockForPtInLayer(const Vec2& pt, const char* layerName)
{
	Vec2 ptInMap = util->convertToMap(pt, _map);
	TMXLayer* layer = _map->getLayer(layerName);

	Size _layerSize = layer->getLayerSize();

	/* 判断ptInMap是不是合法的坐标点 */
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
	// 上帝模式一般使用半透明形象
	this->setOpacity(128);

	// 设置上帝模式
	_godMode = true;

	//DelayTime* delay = DelayTime::create(duration);
	// 当duration时间过去之后，再设置为非无敌模式
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