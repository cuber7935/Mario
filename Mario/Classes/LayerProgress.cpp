#include "LayerProgress.h"
#include "LayerGame.h"


bool LayerProgress::init()
{
	Layer::init();

	initBG();
	
	// 016. 创建马里奥精灵
	_mario = Sprite::create();
	addChild(_mario);
	// 017. 为了方便马里奥精灵和LoadingBar对齐，把锚点设置到中下点
	_mario->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);

	// 018. 加载马里奥动画，让Mario执行
	/* 执行动画 */
	Vector<SpriteFrame*> arr;
	for (int i = 0; i < 10; ++i)
	{
		SpriteFrame* frame = SpriteFrame::create("smallWalkRight.png", Rect(i*14, 0, 14, 16));
		arr.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(arr, 0.05f);
	Animate* animate = Animate::create(animation);
	RepeatForever* rep = RepeatForever::create(animate);
	_mario->runAction(rep);

	// 019. 开始加载资源
	loadResources();

	return true;
}

void LayerProgress::initBG()
{
	Util::getInstance().addBg("bg.png", this);
}

static const char* filenames[] = 
{
"about_normal.png",
"about_select.png",
"AB_normal.png",
"AB_select.png",
"allow_walkLeft.png",
"allow_walkRight.png",
"arrow.png",
"arrowActionL.png",
"arrowActionR.png",
"arrowBroken.png",
"arrowBullet.png",
"arrow_die.png",
"axe.png",
"backA.png",
"backB.png",
"background.png",
"backKeyImage.png",
"backKeyLeft.png",
"backKeyRight.png",
"backToMenu.png",
"battery.png",
"batteryBoom1.png",
"batteryBoom2.png",
"batteryBoom3.png",
"batteryBullet.png",
"bg.png",
"blinkcoin.png",
"boss.png",
"bossBullet.png",
"brokencoin.png",
"bulletBorder.png",
"CloseNormal.png",
"CloseSelected.png",
"cloud.png",
"coinani.png",
"controlUI.png",
"darkCloud.png",
"fireActionL.png",
"fireActionR.png",
"fireBall.png",
"fireLeft.png",
"fireRight.png",
"fire_die.png",
"flag.png",
"flower0.png",
"flyFishLeft.png",
"flyFishRight.png",
"fps_images-hd.png",
"fps_images-ipadhd.png",
"fps_images.png",
"gameover.png",
"HelloWorld.png",
"ladder.png",
"left.png",
"leftright.png",
"lighting.png",
"Mushroom0.png",
"music_off.png",
"music_on.png",
"M_n.png",
"M_s.png",
"newgameA.png",
"newgameB.png",
"nextlevel_normal.png",
"nextlevel_select.png",
"normal_die.png",
"PassFailure.png",
"PassSuccess.png",
"princess.png",
"quitgame_normal.png",
"quitgame_select.png",
"restart_n.png",
"restart_s.png",
"resume_n.png",
"resume_s.png",
"retry_normal.png",
"retry_select.png",
"rewardMushroomSet.png",
"right.png",
"select_n.png",
"select_s.png",
"Setting_n.png",
"setting_s.png",
"Set_Menu.png",
"Set_Music.png",
"set_n.png",
"set_s.png",
"shanshuodecoin.png",
"singleblock.png",
"sliderProgress.png",
"sliderTrack.png",
"smallWalkLeft.png",
"smallWalkRight.png",
"small_die.png",
"sound_effect_off.png",
"sound_effect_on.png",
"startgame_normal.png",
"startgame_select.png",
"superMarioMap.png",
"switchBg.png",
"Tools.png",
"tortoise0.png",
"walkLeft.png",
"WalkLeft_fire.png",
"walkRight.png",
"WalkRight_fire.png",
};

void LayerProgress::loadAnimationsAndFrames()
{
	/* 蘑菇怪使用的资源 */
	util.loadAnimation("Mushroom0.png", Size(16, 16), 0, 2, ANI_MUSHROOM_RUN, 0.05f);
	util.loadSpriteFrame("Mushroom0.png", Size(16, 16), 2, FRA_MUSHROOM_DIE1);
	util.loadSpriteFrame("Mushroom0.png", Size(16, 16), 3, FRA_MUSHROOM_DIE2);


	/* 乌龟使用的资源 */
	util.loadAnimation("tortoise0.png", Size(18, 24), 0, 2, ANI_TORTOISE_FLY_LEFT, 0.05f);
	util.loadAnimation("tortoise0.png", Size(18, 24), 2, 2, ANI_TORTOISE_RUN_LEFT, 0.05f);
	util.loadAnimation("tortoise0.png", Size(18, 24), 4, 2, ANI_TORTOISE_RUN_RIGHT, 0.05f);
	util.loadAnimation("tortoise0.png", Size(18, 24), 6, 2, ANI_TORTOISE_FLY_RIGHT, 0.05f);
	util.loadAnimation("tortoise0.png", Size(18, 24), 8, 2, ANI_TORTOISE_SCARED, 0.05f);

	/* 花 */
	util.loadAnimation("flower0.png", Size(16, 24), 0, 2, ANI_FLOWER, 0.05f);

	/* 蘑菇奖赏的帧 */
	util.loadSpriteFrame("rewardMushroomSet.png", Size(16, 16), 0, FRA_MUSHROOM_REWARD1);
	util.loadSpriteFrame("rewardMushroomSet.png", Size(16, 16), 1, FRA_MUSHROOM_REWARD2);
	util.loadSpriteFrame("rewardMushroomSet.png", Size(16, 16), 2, FRA_MUSHROOM_REWARD3);

	/* 马里奥 */
	util.loadAnimation("smallWalkLeft.png", Size(14, 16), 0, 10, ANI_MARIO_WALK_LEFT_SML, 0.05f);
	util.loadAnimation("smallWalkRight.png", Size(14, 16), 0, 10, ANI_MARIO_WALK_RIGHT_SML, 0.05f);
	util.loadAnimation("small_die.png", Size(16, 18), 0, 7, ANI_MARIO_DIE_SML, 0.05f);

	util.loadAnimation("walkLeft.png", Size(18, 32), 0, 10, ANI_MARIO_WALK_LEFT_BIG, 0.05f);
	util.loadAnimation("walkRight.png", Size(18, 32), 0, 10, ANI_MARIO_WALK_RIGHT_BIG, 0.05f);

	util.loadSpriteFrame("smallWalkLeft.png", Size(14, 16), 10, FRA_MARIO_JUMP_LEFT_SML);
	util.loadSpriteFrame("smallWalkRight.png", Size(14, 16), 10, FRA_MARIO_JUMP_RIGHT_SML);

	util.loadSpriteFrame("walkLeft.png", Size(18, 32), 10, FRA_MARIO_JUMP_LEFT_BIG);
	util.loadSpriteFrame("walkRight.png", Size(18, 32), 10, FRA_MARIO_JUMP_RIGHT_BIG);
	
	/* 棋点 */
	util.loadSpriteFrame("flag.png", Size(32, 16), 0, FRA_FLAG);

	/* 飞鱼 */
	util.loadAnimation("flyFishLeft.png", Size(16, 16), 0, 6, ANI_FLYFISH_LEFT, 0.05f);
	util.loadAnimation("flyFishRight.png", Size(16, 16), 0, 6, ANI_FLYFISH_RIGHT, 0.05f);

	/* Boss动画 */
	util.loadAnimation("boss.png", Size(32, 32), 0, 4, ANI_BOSS_LEFT, 0.05f);
	util.loadAnimation("boss.png", Size(32, 32), 4, 4, ANI_BOSS_RIGHT, 0.05f);

	/* 子弹动画加载 */
	util.loadAnimation("bossBullet.png", Size(24, 8), 0, 2, ANI_BOSS_BULLET_LEFT, 0.05f);
	util.loadAnimation("bossBullet.png", Size(24, 8), 2, 2, ANI_BOSS_BULLET_RIGHT, 0.05f);
}

void LayerProgress::update(float)
{
	// 024. 记载纹理和推进进度条
	Director::getInstance()->getTextureCache()->addImage(filenames[_curLoadImageCount++]);
	_loadingBar->setPercent(_curLoadImageCount*100.0f / _totalImageCount);

	// 移动马里奥
	Rect rc = _loadingBar->getBoundingBox();
	_mario->setPositionX((rc.getMaxX() - rc.getMinX()) * _loadingBar->getPercent() / 100 + rc.getMinX());

	if (_totalImageCount == _curLoadImageCount)
	{
		unscheduleUpdate();

		// 整理纹理资源
		loadAnimationsAndFrames();

		// 025. 进入游戏场景
		Scene* scene = createTransitionByLayer(TransitionCrossFade, LayerGame::create(), 1.0f);
		Director::getInstance()->replaceScene(scene);
	}
}

void LayerProgress::loadResources()
{
	/* 020. 创建LoadingBar */
	_loadingBar = ui::LoadingBar::create("sliderProgress.png");
	addChild(_loadingBar);
	_loadingBar->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	// 021. 根据LoadingBar的位置，设置mario的位置，为了实现让Mario在LoadingBar上面移动
	Rect rc = _loadingBar->getBoundingBox();
	_mario->setPositionY(rc.getMaxY());
	_mario->setPositionX(rc.getMinX());


	/* 022. 计算一共需要加载的纹理数，初始化已经加载的纹理数，加载纹理资源 */
	_totalImageCount = sizeof(filenames) / sizeof(*filenames);
	_curLoadImageCount = 0;

	/* 023. 启动定时器，实现加载 */
	scheduleUpdate();

#if 0
	// _loadingBar->setPercent只是改变了进度条的属性，没有改变界面
	for(int i=0;i <_totalImageCount;++i)
	{
		Director::getInstance()->getTextureCache()->addImage(filenames[i]);
		++_curLoadImageCount;
		_loadingBar->setPercent(_curLoadImageCount*100.0f / _totalImageCount);

	//	Director::getInstance()->getRunningScene()->visit();
	}
#endif

#if 0

	auto loadTextureCallback = [&](Texture2D*)
	{
		// 计算加载的图片数量
		++_curLoadImageCount;
		_loadingBar->setPercent(_curLoadImageCount*100.0f / _totalImageCount);

		// 移动mario x坐标值
		Rect rc = _loadingBar->getBoundingBox();
		_mario->setPositionX((rc.getMaxX() - rc.getMinX()) * _loadingBar->getPercent() / 100 + rc.getMinX());

		CCLOG("%d, %d", _curLoadImageCount, _totalImageCount);

		/* 加载完成 */
		if (_curLoadImageCount == _totalImageCount)
		{
			Scene* scene = createTransitionByLayer(TransitionCrossFade, LayerGame::create(), 1.0f);
		//	Director::getInstance()->replaceScene(scene);
		}
	};

	for (int i = 0; i < _totalImageCount; ++i)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(filenames[i], loadTextureCallback);
	}
#endif

}

