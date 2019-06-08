#include "LayerMenu.h"


bool LayerMenu::init()
{
	// 灰色场景层， 半透明
	LayerColor::initWithColor(Color4B(166, 166, 166, 128));

	// 暂停游戏 
	Director::getInstance()->pause();

	// 添加背景
	Sprite* bg = Util::getInstance()->addBg("Set_Music.png", this);

	// 添加音乐按钮
	this->createMusicBtn();

	// 添加音效按钮
	this->createEffectBtn();

	// 添加触摸
	this->addTouchMusicAndEffect();

	return true;
}

// 创建音乐按钮
void LayerMenu::createMusicBtn()
{
	_music = Util::getInstance()->addBg("music_on.png", this);
	//_music->setTag(100);
	Util::getInstance()->moveNode(_music, Vec2(20, 30));
}

// 创建音效按钮
void LayerMenu::createEffectBtn()
{
	_effect = Util::getInstance()->addBg("sound_effect_on.png", this);
	//_effect->setTag(101);
	Util::getInstance()->moveNode(_effect, Vec2(20, -30));
}

// 添加触摸
void LayerMenu::addTouchMusicAndEffect()
{
	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = CC_CALLBACK_2(LayerMenu::TouchBegan, this);
	ev->onTouchEnded = CC_CALLBACK_2(LayerMenu::TouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
}

//触摸处理函数
bool LayerMenu::TouchBegan(Touch* touch, Event* ev)
{
	if (_music->getBoundingBox().containsPoint(touch->getLocation())
		|| _effect->getBoundingBox().containsPoint(touch->getLocation()))
	{
		return true;
	}

	// 继续游戏
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
			// 播放音乐
		}
		else
		{
			_music->setTexture("music_off.png");
			// 暂停音乐
		}
	}

	if (_effect->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->_bEffectOn = !this->_bEffectOn;
		if (_bEffectOn)
		{
			_effect->setTexture("sound_effect_on.png");
			// 播放音效
		}
		else 
		{
			_effect->setTexture("sound_effect_off.png");
			// 暂停音效
		}
	}
}