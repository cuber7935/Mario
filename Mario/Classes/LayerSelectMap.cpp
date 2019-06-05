#include "LayerSelectMap.h"
#include "LayerProgress.h"
#include "LayerStart.h"

// 014. 初始化
// 初始化背景，初始化滚动视图，初始化触摸，初始化菜单
// 初始化完毕之后，该场景的节点关系图看1.png
bool LayerSelectMap::init()
{
	Layer::init();

	initBG();
	initScrollView();
	initTouch();
	initBackMenu();

	return true;
}

void LayerSelectMap::initBG()
{
	/* 背景图片 */
	Util::getInstance().addBg("bg.png", this);
}
void LayerSelectMap::initScrollView()
{
	/* ScrollView */
	ScrollView* view = ScrollView::create(winSize);
	addChild(view);
	_view = view;

	Node* container = view->getContainer();
	for (int i = 0; i < 8; ++i)
	{
		const char* filename = Util::getInstance().format(i + 1, "select", ".jpg");
		Sprite* sprite = Util::getInstance().addBg(filename, container);
		Util::getInstance().moveNode(sprite, Vec2(winSize.width * i, 0));
	}
	/* 设置滚动区域尺寸 */
	view->setContentSize(Size(winSize.width * 8, winSize.height));
	view->setDirection(ScrollView::Direction::HORIZONTAL);

}
void LayerSelectMap::initTouch()
{
	/* 触摸处理 */
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerSelectMap::TouchBegan, this);
	//	ev->onTouchMoved = CC_CALLBACK_2(LayerSelectMap::TouchMoved, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerSelectMap::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
}
void LayerSelectMap::initBackMenu()
{
	/* 返回按钮 */
	auto menuCallback = [](Ref*)
	{
		Scene* scene = Util::getInstance().createScene(LayerStart::create());
		Director::getInstance()->replaceScene(scene);
	};
	MenuItem* item = MenuItemImage::create("backA.png", "backB.png", menuCallback);
	Menu* menu = Menu::createWithItem(item);
	addChild(menu);
	Rect rcItem = item->getBoundingBox();
	menu->setPosition(winSize.width - rcItem.size.width / 2, rcItem.size.height / 2);
}

bool LayerSelectMap::TouchBegan(Touch*, Event*)
{
	return true;
}

void LayerSelectMap::TouchEnded(Touch* touch, Event*)
{
	/* 判断是点击还是滑动 */
	Vec2 posNow = touch->getLocation();
	Vec2 posStart = touch->getStartLocation();
	if (posNow.getDistanceSq(posStart) > 25)
	{
		// 滑动
		// 该函数被调用时，滑动手指已经离开了屏幕
		// 但是SrollView还是惯性的滚动
		// 如果要调整位置，需要等待其静止以后，
		// 启动定时器，判断其是否静止
		schedule(schedule_selector(LayerSelectMap::detectScrollViewMoving), 0.05f);
		_lastScrollViewPosition = 100000;
	}
	else
	{
		// 015. 点击判断，如果点击了对应的精灵，那么进入该精灵对应的游戏场景（实际是进入Progress场景去加载资源）
		Node* container = _view->getContainer();
		Vector<Node*>& children = container->getChildren();

		Vec2 posNowInContainer = container->convertToNodeSpace(posNow);

		int idx = 1;
		for (Node* child : children)
		{
			if (child->getBoundingBox().containsPoint(posNowInContainer))
			{
				// 切换场景
				Util::getInstance()._mapIndex = idx;
				//Scene* scene = createTransitionByLayer(TransitionPageTurn, LayerProgress::create(), 1.0f, true);
				Director::getInstance()->replaceScene(Util::getInstance().createScene(LayerProgress::create()));
				break;
			}
			++idx;
		}
	}
}

void LayerSelectMap::adjustView()
{
	Node* container = _view->getContainer();
	Vector<Node*>& children = container->getChildren();
	for(Node* child : children)
	{
		Vec2 posChild = child->getPosition();
		/* 转换坐标体系到世界坐标 */
		Vec2 posChildInWorld = container->convertToWorldSpace(posChild);

		float dist = winSize.width / 2 - posChildInWorld.x;
		if (abs(dist) < winSize.width / 2)
		{
			/* 矫正 */
			container->runAction(MoveBy::create(abs(dist) / 200, Vec2(dist, 0)));
			break;
		}
	}
}

void LayerSelectMap::detectScrollViewMoving(float dt)
{
	
	// 检查ScrollView的container的位置，是否和上一帧相同，如果相同，说明其已经停止惯性
	float posNow = _view->getContainer()->getPositionX();
	if (posNow == _lastScrollViewPosition)
	{
		unschedule(schedule_selector(LayerSelectMap::detectScrollViewMoving));
		adjustView();
	}
	else
	{
		_lastScrollViewPosition = posNow;
	}
}

#if 0
void LayerSelectMap::TouchMoved(Touch*, Event*)
{
	
}
#endif