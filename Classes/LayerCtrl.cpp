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

	// ���ü�����1�� ��ֹʹ���Ѿ����ͷŵĶ���
	_model->retain();

	// ���� .csb �ļ�
	this->loadCsbFile();

	// �������ֿؼ�
	this->createCtrl();

	// ��������
	this->addTouchCtrl();

#ifdef WIN32
	// ����windowsϵͳ�İ�������
	schedule(schedule_selector(LayerCtrl::checkKey));
#endif

	return true;
}

// ���� .csb �ļ�
void LayerCtrl::loadCsbFile()
{
	_node = CSLoader::getInstance()->createNode("CtrlPanel.csb");
	this->addChild(_node);
}

// �������ֿ��ƿؼ�
void LayerCtrl::createCtrl()
{
	_ctrlDir = (Sprite*)_node->getChildByName("CtrlDir");

	_ctrlMenu = (ui::Button*)_node->getChildByName("CtrlMenu");
	_ctrlJump = (ui::Button*)_node->getChildByName("CtrlJump");
	_ctrlFire = (ui::Button*)_node->getChildByName("CtrlFire");
}

// �����ֿؼ����Ӵ�������
void LayerCtrl::addTouchCtrl()
{
	_ctrlMenu->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::menuCtrlCallback, this));
	_ctrlJump->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::jumpCtrlCallback, this));
	_ctrlFire->addTouchEventListener(CC_CALLBACK_2(LayerCtrl::fireCtrlCallback, this));

	// ������ƴ�������
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerCtrl::TouchBegan, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerCtrl::TouchEnded, this);
	ev->onTouchMoved = CC_CALLBACK_2(LayerCtrl::TouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, _ctrlDir);
}

bool LayerCtrl::TouchBegan(Touch* touch, Event* ev)
{
	// ����û�����������ϣ������˴δ����Ƿ������
	if (_ctrlDir->getBoundingBox().containsPoint(touch->getLocation()))
	{
		/* �жϴ������ھ�������߻����Ұ�� */
		if (isTouchOnDirLeft(touch))
		{
			/* ����LayerModel�Ľӿڣ���Mario�����ƶ� */
			moveLeft();
		}
		else
		{
			/* ����LayerModel�Ľӿڣ���Mario�����ƶ� */
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
	/* ����LayerModel��������Marioֹͣ */
	stop();
	return ;
}

void LayerCtrl::TouchMoved(Touch* touch, Event* ev)
{
	/* �жϴ������ھ�������߻����Ұ�� */
	if (isTouchOnDirLeft(touch))
	{
		/* ����LayerModel�Ľӿڣ���Mario�����ƶ� */
		moveLeft();
	}
	else if (isTouchOnDirRight(touch))
	{
		/* ����LayerModel�Ľӿڣ���Mario�����ƶ� */
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
	/* �����˵� */
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