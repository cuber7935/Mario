#include "LayerCtrl.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "LayerMenu.h"

bool LayerCtrl::init()
{
	Layer::init();

	_model->retain();

	Node* node = CSLoader::getInstance()->createNode("CtrlPanel.csb");
	addChild(node);

	_ctrlDir = (Sprite*)node->getChildByName("CtrlDir");

	ui::Button* ctrlMenu = (ui::Button*)node->getChildByName("CtrlMenu");
	ui::Button* ctrlJump = (ui::Button*)node->getChildByName("CtrlJump");
	ui::Button* ctrlFire = (ui::Button*)node->getChildByName("CtrlFire");

	ctrlMenu->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::menuCtrlCallback, this));
	ctrlJump->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::jumpCtrlCallback, this));
	ctrlFire->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::fireCtrlCallback, this));

	// 方向控制触摸处理
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerCtrl::TouchBegan, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerCtrl::TouchEnded, this);
	ev->onTouchMoved = CC_CALLBACK_2(LayerCtrl::TouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, _ctrlDir);

#ifdef WIN32
	// 用于windows系统的按键测试
	schedule(schedule_selector(LayerCtrl::checkKey));
#endif

	return true;
}

#ifdef WIN32
void LayerCtrl::checkKey(float dt)
{
	SHORT J = GetKeyState('J');
	if (J < 0)
	{
		_model->jump();
	}

	/*win32 API*/
	SHORT F = GetKeyState('F');
	SHORT D = GetKeyState('D');

	if (F >= 0 && D >= 0)
	{
		stop();
		return;
	}

	if (F < 0)
	{
		moveRight();
	}
	
	if (D < 0)
	{
		moveLeft();
	}
}
#endif

bool LayerCtrl::TouchBegan(Touch* touch, Event* ev)
{
	// 如果用户点击到精灵上，表明此次触摸是方向控制
	if (_ctrlDir->getBoundingBox().containsPoint(touch->getLocation()))
	{
		/* 判断触摸点在精灵的左半边还是右半边 */
		if (isTouchOnDirLeft(touch))
		{
			/* 调用LayerModel的接口，让Mario向左移动 */
			moveLeft();
		}
		else
		{
			/* 调用LayerModel的接口，让Mario向右移动 */
			moveRight();
		}

		return true;
	}

	return false;
}

void LayerCtrl::moveRight()
{
	_model->moveRight();
	this->_ctrlDir->setTexture("backKeyRight.png");
}
void LayerCtrl::moveLeft()
{
	_model->moveLeft();
	this->_ctrlDir->setTexture("backKeyLeft.png");
}
void LayerCtrl::stop()
{
	_model->stop();
	this->_ctrlDir->setTexture("backKeyImage.png");
}

void LayerCtrl::TouchEnded(Touch* touch, Event* ev)
{
	/* 调用LayerModel函数，让Mario停止 */
	stop();
	return ;
}

void LayerCtrl::TouchMoved(Touch* touch, Event* ev)
{
	/* 判断触摸点在精灵的左半边还是右半边 */
	if (isTouchOnDirLeft(touch))
	{
		/* 调用LayerModel的接口，让Mario向左移动 */
		moveLeft();
	}
	else if (isTouchOnDirRight(touch))
	{
		/* 调用LayerModel的接口，让Mario向右移动 */
		moveRight();
	}
	else
	{
		stop();
	}

	return ;
}

bool LayerCtrl::isTouchOnDirRight(Touch* touch)
{
	Vec2 pt = touch->getLocation();
	Rect rc = _ctrlDir->getBoundingBox();

	rc.origin.x = rc.getMidX();
	rc.size.width /= 2;

	return rc.containsPoint(pt);
}

bool LayerCtrl::isTouchOnDirLeft(Touch* touch)
{
	Vec2 pt = touch->getLocation();
	Rect rc = _ctrlDir->getBoundingBox();

	rc.size.width /= 2;
	return rc.containsPoint(pt);
}

void LayerCtrl::menuCtrlCallback(Ref*, ui::Widget::TouchEventType)
{
	/* 弹出菜单 */
	LayerMenu* menu = LayerMenu::create();
	addChild(menu);
}

void LayerCtrl::jumpCtrlCallback(Ref*, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		_model->jump();
	}
}

void LayerCtrl::fireCtrlCallback(Ref*, ui::Widget::TouchEventType)
{}

void LayerCtrl::onExit()
{
	Layer::onExit();

	_model->release();
}