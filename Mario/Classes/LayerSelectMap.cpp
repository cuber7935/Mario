#include "LayerSelectMap.h"
#include "LayerProgress.h"
#include "LayerStart.h"

// 014. ��ʼ��
// ��ʼ����������ʼ��������ͼ����ʼ����������ʼ���˵�
// ��ʼ�����֮�󣬸ó����Ľڵ��ϵͼ��1.png
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
	/* ����ͼƬ */
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
	/* ���ù�������ߴ� */
	view->setContentSize(Size(winSize.width * 8, winSize.height));
	view->setDirection(ScrollView::Direction::HORIZONTAL);

}
void LayerSelectMap::initTouch()
{
	/* �������� */
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerSelectMap::TouchBegan, this);
	//	ev->onTouchMoved = CC_CALLBACK_2(LayerSelectMap::TouchMoved, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerSelectMap::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
}
void LayerSelectMap::initBackMenu()
{
	/* ���ذ�ť */
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
	/* �ж��ǵ�����ǻ��� */
	Vec2 posNow = touch->getLocation();
	Vec2 posStart = touch->getStartLocation();
	if (posNow.getDistanceSq(posStart) > 25)
	{
		// ����
		// �ú���������ʱ��������ָ�Ѿ��뿪����Ļ
		// ����SrollView���ǹ��ԵĹ���
		// ���Ҫ����λ�ã���Ҫ�ȴ��侲ֹ�Ժ�
		// ������ʱ�����ж����Ƿ�ֹ
		schedule(schedule_selector(LayerSelectMap::detectScrollViewMoving), 0.05f);
		_lastScrollViewPosition = 100000;
	}
	else
	{
		// 015. ����жϣ��������˶�Ӧ�ľ��飬��ô����þ����Ӧ����Ϸ������ʵ���ǽ���Progress����ȥ������Դ��
		Node* container = _view->getContainer();
		Vector<Node*>& children = container->getChildren();

		Vec2 posNowInContainer = container->convertToNodeSpace(posNow);

		int idx = 1;
		for (Node* child : children)
		{
			if (child->getBoundingBox().containsPoint(posNowInContainer))
			{
				// �л�����
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
		/* ת��������ϵ���������� */
		Vec2 posChildInWorld = container->convertToWorldSpace(posChild);

		float dist = winSize.width / 2 - posChildInWorld.x;
		if (abs(dist) < winSize.width / 2)
		{
			/* ���� */
			container->runAction(MoveBy::create(abs(dist) / 200, Vec2(dist, 0)));
			break;
		}
	}
}

void LayerSelectMap::detectScrollViewMoving(float dt)
{
	
	// ���ScrollView��container��λ�ã��Ƿ����һ֡��ͬ�������ͬ��˵�����Ѿ�ֹͣ����
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