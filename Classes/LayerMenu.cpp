#include "LayerMenu.h"


bool LayerMenu::init()
{
	// ��ɫ�����㣬 ��͸��
	LayerColor::initWithColor(Color4B(166, 166, 166, 128));

	// ��ͣ��Ϸ 
	Director::getInstance()->pause();

	// ��ӱ���
	Sprite* bg = Util::getInstance()->addBg("Set_Music.png", this);

	// ������ְ�ť
	this->createMusicBtn();

	// �����Ч��ť
	this->createEffectBtn();

	// ��Ӵ���
	this->addTouchMusicAndEffect();

	return true;
}

// �������ְ�ť
void LayerMenu::createMusicBtn()
{
	_music = Util::getInstance()->addBg("music_on.png", this);
	//_music->setTag(100);
	Util::getInstance()->moveNode(_music, Vec2(20, 30));
}

// ������Ч��ť
void LayerMenu::createEffectBtn()
{
	_effect = Util::getInstance()->addBg("sound_effect_on.png", this);
	//_effect->setTag(101);
	Util::getInstance()->moveNode(_effect, Vec2(20, -30));
}

// ��Ӵ���
void LayerMenu::addTouchMusicAndEffect()
{
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerMenu::TouchBegan, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerMenu::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
}

//����������
bool LayerMenu::TouchBegan(Touch* touch, Event* ev)
{
	if (_music->getBoundingBox().containsPoint(touch->getLocation())
		|| _effect->getBoundingBox().containsPoint(touch->getLocation()))
	{
		return true;
	}

	// ������Ϸ
	Director::getInstance()->resume();
	
	this->removeFromParent();

	return false;
}

void LayerMenu::TouchEnded(Touch* touch, Event* ev)
{
	//Sprite* music = (Sprite*)getChildByTag(100);
	//Sprite* effect = (Sprite*)getChildByTag(101);
	if (_music->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->_bMusicOn = !this->_bMusicOn;
		if (_bMusicOn)
		{
			_music->setTexture("music_on.png");
			// ��������
		}
		else
		{
			_music->setTexture("music_off.png");
			// ��ͣ����
		}
	}

	if (_effect->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->_bEffectOn = !this->_bEffectOn;
		if (_bEffectOn)
		{
			_effect->setTexture("sound_effect_on.png");
			// ������Ч
		}
		else 
		{
			_effect->setTexture("sound_effect_off.png");
			// ��ͣ��Ч
		}
	}
}