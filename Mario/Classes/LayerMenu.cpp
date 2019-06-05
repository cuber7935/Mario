#include "LayerMenu.h"


bool LayerMenu::init()
{
	LayerColor::initWithColor(Color4B(166, 166, 166, 128));

	/* ÔÝÍ£ÓÎÏ· */
	Director::getInstance()->pause();

	Sprite* bg = Util::getInstance().addBg("Set_Music.png", this);

	Sprite* music = Util::getInstance().addBg("sound_effect_on.png", this);
	Sprite* effect = Util::getInstance().addBg("sound_effect_on.png", this);

	music->setTag(100);
	effect->setTag(101);

	Util::getInstance().moveNode(music, Vec2(20, 30));
	Util::getInstance().moveNode(effect, Vec2(20, -30));

	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [&](Touch* touch, Event*)
	{
		if (getChildByTag(100)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			return true;
		}

		if (getChildByTag(101)->getBoundingBox().containsPoint(touch->getLocation()))
		{
			return true;
		}

		Director::getInstance()->resume();
		this->removeFromParent();
		return false;
	};

	ev->onTouchEnded = [&](Touch* touch, Event*)
	{
		Sprite* music = (Sprite*)getChildByTag(100);
		Sprite* effect = (Sprite*)getChildByTag(101);
		if (music->getBoundingBox().containsPoint(touch->getLocation()))
		{
			this->_bMusicOn = !this->_bMusicOn;
			if (_bMusicOn)

				music->setTexture("sound_effect_on.png");
			else
				music->setTexture("sound_effect_off.png");
		}

		if (effect->getBoundingBox().containsPoint(touch->getLocation()))
		{
			this->_bEffectOn = !this->_bEffectOn;
			if (_bEffectOn)
				effect->setTexture("sound_effect_on.png");
			else
				effect->setTexture("sound_effect_off.png");
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);

	return true;
}