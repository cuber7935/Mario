#include "LayerCtrl.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "LayerMenu.h"

LayerCtrl * LayerCtrl::create(LayerModel * model)
{
	LayerCtrl* ret = new LayerCtrl;
	ret->_model = model;
	ret->init();
	ret->autorelease();
	return ret;
}

bool LayerCtrl::init()
{
	if (!Layer::init())
		return false;

	// 引用计数加1， 防止使用已经被释放的对象
	_model->retain();

	// 加载 .csb 文件
	this->loadCsbFile();

	// 创建各种控件
	this->createCtrl();

	// 触摸处理
	this->addTouchCtrl();

#ifdef WIN32
	// 用于windows系统的按键测试
	schedule(schedule_selector(LayerCtrl::checkKey));
#endif

	return true;
}

// 加载 .csb 文件
void LayerCtrl::loadCsbFile()
{
	_node = CSLoader::getInstance()->createNode("CtrlPanel.csb");
	this->addChild(_node);
}

// 创建各种控制控件
void LayerCtrl::createCtrl()
{
	_ctrlDir = (Sprite*)_node->getChildByName("CtrlDir");

	_ctrlMenu = (ui::Button*)_node->getChildByName("CtrlMenu");
	_ctrlJump = (ui::Button*)_node->getChildByName("CtrlJump");
	_ctrlFire = (ui::Button*)_node->getChildByName("CtrlFire");
}

// 给各种控件增加触摸处理
void LayerCtrl::addTouchCtrl()
{
	_ctrlMenu->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::menuCtrlCallback, this));
	_ctrlJump->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::jumpCtrlCallback, this));
	_ctrlFire->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::fireCtrlCallback, this));

	// 方向控制触摸处理
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerCtrl::TouchBegan, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerCtrl::TouchEnded, this);
	ev->onTouchMoved = CC_CALLBACK_2(LayerCtrl::TouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, _ctrlDir);
}

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