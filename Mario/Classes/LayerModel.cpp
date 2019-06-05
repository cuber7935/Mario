#include "LayerModel.h"
#include "RoleMushroomReward.h"
#include "LayerGame.h"
#include "SimpleAudioEngine.h"
bool LayerModel::init()
{
	Layer::init();

	/* 028. 创建瓦片地图，瓦片地图的下标在LayerMapSelect场景中，已经选择过，并且保持在全局的Util::_mapIndex */
	initMap();	
	/* 029. 初始化Roles，其实游戏角色属性都保存在瓦片地图的objects对象层，
	遍历对象层，根据对象层中的属性，来创建和设置游戏对象即可
	游戏角色分主角，敌人，道具，这些角色有一些公共的属性，因此他们都继承自Role类，
	Role类作为一个工厂类，提供创建方法，根据参数，创建不同的对象
	*/
	initRoles();

	initBossFireEvent();
	initBreakBridgeEvent();

	/* 增加碰撞检测定时器 */
	schedule(schedule_selector(LayerModel::collision));

	/* 增加一个自定义消息监听器 */
	EventListenerCustom* cus = EventListenerCustom::create("hitblock", [&](EventCustom* ev)
	{
		// 获取自定义消息参数：是一个精灵
		Sprite* block = (Sprite*)ev->getUserData();
		// 获取精灵的矩形
		Rect rcBlock = block->getBoundingBox();

		Sequence* rewardAction = NULL;

		// 遍历所有角色，看看该精灵（砖块）中是不是有蘑菇奖赏
		for(auto it = _roles.begin(); it!=_roles.end(); ++it)
		{
			Role* role = *it;
			// 判断角色是不是蘑菇
			// 判断蘑菇是不是在block中
			if(role->getType() == "MushroomReward" || role->getType()=="MushroomAddLife")
			{
				// 蘑菇的中心坐标取出
				Rect rcRole = role->getBoundingBox();
				Vec2 center = Vec2(rcRole.getMidX(), rcRole.getMidY());

				// 检测砖块中是否包含了蘑菇奖赏的中心点
				if (rcBlock.containsPoint(center))
				{
					//ToggleVisibility
					//RemoveSelf;
					//Place;
					//ToggleVisibility;
					//Show;
					//Hide
					// 显示动作，让蘑菇奖赏显示出来
					TargetedAction* showAction = TargetedAction::create(role, Show::create());
					// 生长动作
					TargetedAction* moveAction = TargetedAction::create(role, MoveBy::create(0.3f, Vec2(0, 16)));
					// 回调函数动作，回调了蘑菇奖赏的growUp函数，让_bGrow设置成true
					CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RoleMushroomReward::growUp, (RoleMushroomReward*)role));

					// 组成sequence动作
					rewardAction = Sequence::create(showAction, moveAction, callFunc, NULL);
					break;
				}
			}
		}

		// 砖头跳动的动作
		TargetedAction* blockAction = TargetedAction::create(block, JumpBy::create(0.2f, Vec2(0, 0), 16, 1));
		if (rewardAction)
		{
			Sequence* seq = Sequence::createWithTwoActions(blockAction, rewardAction);
			runAction(seq);
		}
		else
		{
			runAction(blockAction);
		}

		// 记得将砖头release，因为发送自定义消息时，我们对砖头进行retain
		// 为什么在这里release，而不是动作完成之后release，是因为Action本身对block已经retain过
		// block->release();
	});

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(cus, this);

#if 0
	EventListenerTouchOneByOne* ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [](Touch*, Event*){return true; };
	ev->onTouchMoved = [&](Touch* touch, Event*)
	{
		util.moveNode(_map, touch->getDelta());
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
#endif

	return true;
}

void LayerModel::initBreakBridgeEvent()
{
	EventListenerCustom* cus = EventListenerCustom::create("breakbridge", CC_CALLBACK_1(LayerModel::breakBridge, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(cus, this);
}

void LayerModel::breakBridge(EventCustom*)
{
	/* 先判断是否有桥 */
	if (_bridge)
	{
		Vec2 pos = _bridge->getPosition();
		pos += Vec2(8, 8);

#if 0
		TMXLayer* land = _map->getLayer("land");
		for (int i = 0; i < 14; ++i)
		{
			land->setTileGID(0, util.convertToMap(pos, _map));
			pos.x += 16;
		}
#endif
		breakBridge1(pos, 0);
	}
}

void LayerModel::breakBridge1(Vec2 pos, int idx)
{
	if (idx == 14)
		return;

	TMXLayer* land = _map->getLayer("land");
	land->setTileGID(0, util.convertToMap(pos, _map));

	pos.x += 16;

	DelayTime* delay = DelayTime::create(0.1f);
	CallFunc* call = CallFunc::create(CC_CALLBACK_0(LayerModel::breakBridge1, this, pos, idx+1));
	this->runAction(Sequence::create(delay, call, NULL));
}

void LayerModel::initBossFireEvent()
{
	EventListenerCustom* cus = EventListenerCustom::create("bossfire", [&](EventCustom* ev){
		/* 执行发射子弹 */
		void* p = ev->getUserData();
		Role* boss = (Role*)p;

		Rect rcBoss = boss->getBoundingBox();

		/* 创建子弹。。。 */
		ValueMap objProperty;
		objProperty["type"] = "bossbullet";

		if (boss->_right)
		{
			objProperty["x"] = (int)rcBoss.getMaxX();
		}
		else
		{
			objProperty["x"] = (int)rcBoss.getMinX() - 24;
		}

		objProperty["y"] = (int)(rcBoss.getMinY() + rcBoss.size.height * .9f);
		objProperty["right"] = boss->_right;

		Role* bullet = Role::create(objProperty);

		_roles.pushBack(bullet);
		_map->addChild(bullet);
	});

	_eventDispatcher->addEventListenerWithSceneGraphPriority(cus, this);
}

void LayerModel::collision(float)
{
	// 优化的机会？？？？
	Rect rcMario = _mario->getBoundingBox();

	// Mario死亡判断
	isGameOver();

	// 在Mario死亡之后，碰撞检测失效
	if (_mario->_dead)
		return;

	// 金币碰撞检测
	eatCoin();

	scrollMap();

	for (auto it = _roles.begin(); it != _roles.end();)
	{
		Role* role = *it;

		// 判断怪物是否要继续存在
		if (_mario->getPositionX() - role->getPositionX() > winSize.width)
		{
			role->removeFromParent();
			it = _roles.erase(it);
			continue;
		}


		if (role->_running)
		{
			Role::CollisionResult result = role->collsion(_mario, rcMario);
			if (result == Role::CollisionResult::RoleDie)
			{
				it = _roles.erase(it);
				continue;
			}
			else if (result == Role::CollisionResult::FINAL)
			{
				++util._mapIndex;
				unschedule(schedule_selector(LayerModel::collision));
				Scene* scene = createTransitionByLayer(TransitionCrossFade, LayerGame::create(), 1.0f);
				Director::getInstance()->replaceScene(scene);
				return;
			}
			else if (result == Role::CollisionResult::MarioDie)
			{
				// 处理Mario
				_mario->Dead();
				break;
			}
			else if (result == Role::CollisionResult::EAT_MUSHROOM_REWARD)
			{
				it = _roles.erase(it);

				// 处理Mario
				_mario->setBig(true);

				continue;
			}
		}

		++it;
	}

	
}

void LayerModel::isGameOver()
{
	if (_mario->getBoundingBox().getMaxY() < 0)
	{
		unschedule(schedule_selector(LayerModel::collision));
		Scene* scene = createTransitionByLayer(TransitionCrossFade, LayerGame::create(), 1.0f);
		Director::getInstance()->replaceScene(scene);
	}
}

void LayerModel::eatCoin()
{
	TMXLayer* coinLayer = _map->getLayer("coin");
	Rect rc = _mario->getBoundingBox();
	// Mario的四个角
	Vec2 pts[4] = {
		Vec2(rc.getMinX(), rc.getMinY()),
		Vec2(rc.getMaxX(), rc.getMinY()),
		Vec2(rc.getMinX(), rc.getMaxY()),
		Vec2(rc.getMaxX(), rc.getMaxY()),
	};

	for (int i = 0; i < 4; ++i)
	{
		Vec2& pt = pts[i];
		// 把坐标转换成地图坐标
		Vec2 ptInMap = util.convertToMap(pt, _map);
		
		if (!util.isCoodInMap(_map, ptInMap))
			continue;
		// 获取地图坐标中，金币层的gid是否为0，如果不为0，说明该点有金币
		uint32_t gid = coinLayer->getTileGIDAt(ptInMap);
		if (gid != 0)
		{
			// 消灭金币
			coinLayer->setTileGID(0, ptInMap);

			// 累加积分板

			// 播放声音
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("EatCoin.wma");
		}
	}
}

void LayerModel::scrollMap()
{
	// 卷动地图
	/* 卷动地图的条件：mario超过窗口的一半（世界坐标） */
	Vec2 posMarioInMap = _mario->getPosition();
	Vec2 posMarioInWorld = _map->convertToWorldSpace(posMarioInMap);

	Vec2 mapRight = Vec2(_map->getContentSize().width, 0);
	Vec2 mapRightInWorld = _map->convertToWorldSpace(mapRight);

	if (posMarioInWorld.x >= winSize.width / 2 && mapRightInWorld.x > winSize.width)
	{
		_map->setPositionX(_map->getPositionX() - (posMarioInWorld.x - winSize.width / 2));
	}
	else if (mapRightInWorld.x < winSize.width)
	{
		// 最后的矫正
		//	mapRightInWorld.x = winSize.width;
		_map->setPositionX(winSize.width - _map->getContentSize().width);
	}
}

void LayerModel::jump()
{
	_mario->jump();
}
void LayerModel::moveRight()
{
	_mario->moveRight();
}
void LayerModel::moveLeft()
{
	_mario->moveLeft();
}
void LayerModel::stop()
{
	_mario->stop();
}

void LayerModel::initMap()
{
	this->_map = TMXTiledMap::create(util.format(util._mapIndex, "MarioMap", ".tmx"));
	addChild(_map);

	this->_map->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->_map->setPosition(Vec2(0, winSize.height));

	Role::_map = _map;

	const char* layerNames[] = {"block", "pipe"};
	ZOrder zorders[] = { ZOrder::Block, ZOrder::Pipe };
	for (int i = 0; i < sizeof(layerNames)/sizeof(*layerNames); ++i)
	{
		_map->getLayer(layerNames[i])->setLocalZOrder((int)(zorders[i]));
	}
}

void LayerModel::initRoles()
{
	/*030. 获取瓦片地图的对象层*/
	TMXObjectGroup* objGroup = _map->getObjectGroup("objects");
	/* 获取对象层的对象属性数组，只是提供了Role的类型和位置属性，并不包括图片资源 */
	ValueVector& vv = objGroup->getObjects();

	// 遍历所有的属性，根据属性创建角色，并且加入到地图中
	for (Value& v : vv)
	{
		// 每个ValueMap对象，对应一个角色对象，这个角色可能是，蘑菇，乌龟，Mario。。。
		ValueMap& obj = v.asValueMap();
		// 根据数据创建精灵
		Role* role = Role::create(obj);  // mario，蘑菇，棋子，乌龟，花。。。
		if (role)
		{
			// 如果是Mario保存在特殊位置，否则丢到数组中
			if (role->getType() == "BirthPoint")
				this->_mario = (RoleMario*)role;
			else
				this->_roles.pushBack(role);

			if (role->getType() == "bridgestartpos")
				this->_bridge = role;

			_map->addChild(role);
		}
	}

#if 1
	float startOffset = 1900;
	_mario->setPositionX(_mario->getPositionX() + startOffset);
	_map->setPositionX(_map->getPositionX() - startOffset);
//	_mario->setPositionY(1000);
#endif
}