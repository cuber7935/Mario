#include "LayerModel.h"
#include "RoleMushroomReward.h"
#include "LayerGame.h"
#include "SimpleAudioEngine.h"
bool LayerModel::init()
{
	Layer::init();

	/* 028. ������Ƭ��ͼ����Ƭ��ͼ���±���LayerMapSelect�����У��Ѿ�ѡ��������ұ�����ȫ�ֵ�Util::_mapIndex */
	initMap();	
	/* 029. ��ʼ��Roles����ʵ��Ϸ��ɫ���Զ���������Ƭ��ͼ��objects����㣬
	��������㣬���ݶ�����е����ԣ���������������Ϸ���󼴿�
	��Ϸ��ɫ�����ǣ����ˣ����ߣ���Щ��ɫ��һЩ���������ԣ�������Ƕ��̳���Role�࣬
	Role����Ϊһ�������࣬�ṩ�������������ݲ�����������ͬ�Ķ���
	*/
	initRoles();

	initBossFireEvent();
	initBreakBridgeEvent();

	/* ������ײ��ⶨʱ�� */
	schedule(schedule_selector(LayerModel::collision));

	/* ����һ���Զ�����Ϣ������ */
	EventListenerCustom* cus = EventListenerCustom::create("hitblock", [&](EventCustom* ev)
	{
		// ��ȡ�Զ�����Ϣ��������һ������
		Sprite* block = (Sprite*)ev->getUserData();
		// ��ȡ����ľ���
		Rect rcBlock = block->getBoundingBox();

		Sequence* rewardAction = NULL;

		// �������н�ɫ�������þ��飨ש�飩���ǲ�����Ģ������
		for(auto it = _roles.begin(); it!=_roles.end(); ++it)
		{
			Role* role = *it;
			// �жϽ�ɫ�ǲ���Ģ��
			// �ж�Ģ���ǲ�����block��
			if(role->getType() == "MushroomReward" || role->getType()=="MushroomAddLife")
			{
				// Ģ������������ȡ��
				Rect rcRole = role->getBoundingBox();
				Vec2 center = Vec2(rcRole.getMidX(), rcRole.getMidY());

				// ���ש�����Ƿ������Ģ�����͵����ĵ�
				if (rcBlock.containsPoint(center))
				{
					//ToggleVisibility
					//RemoveSelf;
					//Place;
					//ToggleVisibility;
					//Show;
					//Hide
					// ��ʾ��������Ģ��������ʾ����
					TargetedAction* showAction = TargetedAction::create(role, Show::create());
					// ��������
					TargetedAction* moveAction = TargetedAction::create(role, MoveBy::create(0.3f, Vec2(0, 16)));
					// �ص������������ص���Ģ�����͵�growUp��������_bGrow���ó�true
					CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RoleMushroomReward::growUp, (RoleMushroomReward*)role));

					// ���sequence����
					rewardAction = Sequence::create(showAction, moveAction, callFunc, NULL);
					break;
				}
			}
		}

		// שͷ�����Ķ���
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

		// �ǵý�שͷrelease����Ϊ�����Զ�����Ϣʱ�����Ƕ�שͷ����retain
		// Ϊʲô������release�������Ƕ������֮��release������ΪAction�����block�Ѿ�retain��
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
	/* ���ж��Ƿ����� */
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
		/* ִ�з����ӵ� */
		void* p = ev->getUserData();
		Role* boss = (Role*)p;

		Rect rcBoss = boss->getBoundingBox();

		/* �����ӵ������� */
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
	// �Ż��Ļ��᣿������
	Rect rcMario = _mario->getBoundingBox();

	// Mario�����ж�
	isGameOver();

	// ��Mario����֮����ײ���ʧЧ
	if (_mario->_dead)
		return;

	// �����ײ���
	eatCoin();

	scrollMap();

	for (auto it = _roles.begin(); it != _roles.end();)
	{
		Role* role = *it;

		// �жϹ����Ƿ�Ҫ��������
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
				// ����Mario
				_mario->Dead();
				break;
			}
			else if (result == Role::CollisionResult::EAT_MUSHROOM_REWARD)
			{
				it = _roles.erase(it);

				// ����Mario
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
	// Mario���ĸ���
	Vec2 pts[4] = {
		Vec2(rc.getMinX(), rc.getMinY()),
		Vec2(rc.getMaxX(), rc.getMinY()),
		Vec2(rc.getMinX(), rc.getMaxY()),
		Vec2(rc.getMaxX(), rc.getMaxY()),
	};

	for (int i = 0; i < 4; ++i)
	{
		Vec2& pt = pts[i];
		// ������ת���ɵ�ͼ����
		Vec2 ptInMap = util.convertToMap(pt, _map);
		
		if (!util.isCoodInMap(_map, ptInMap))
			continue;
		// ��ȡ��ͼ�����У���Ҳ��gid�Ƿ�Ϊ0�������Ϊ0��˵���õ��н��
		uint32_t gid = coinLayer->getTileGIDAt(ptInMap);
		if (gid != 0)
		{
			// ������
			coinLayer->setTileGID(0, ptInMap);

			// �ۼӻ��ְ�

			// ��������
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("EatCoin.wma");
		}
	}
}

void LayerModel::scrollMap()
{
	// ����ͼ
	/* ����ͼ��������mario�������ڵ�һ�루�������꣩ */
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
		// ���Ľ���
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
	/*030. ��ȡ��Ƭ��ͼ�Ķ����*/
	TMXObjectGroup* objGroup = _map->getObjectGroup("objects");
	/* ��ȡ�����Ķ����������飬ֻ���ṩ��Role�����ͺ�λ�����ԣ���������ͼƬ��Դ */
	ValueVector& vv = objGroup->getObjects();

	// �������е����ԣ��������Դ�����ɫ�����Ҽ��뵽��ͼ��
	for (Value& v : vv)
	{
		// ÿ��ValueMap���󣬶�Ӧһ����ɫ���������ɫ�����ǣ�Ģ�����ڹ꣬Mario������
		ValueMap& obj = v.asValueMap();
		// �������ݴ�������
		Role* role = Role::create(obj);  // mario��Ģ�������ӣ��ڹ꣬��������
		if (role)
		{
			// �����Mario����������λ�ã����򶪵�������
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