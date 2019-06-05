#include "LayerStart.h"
#include "LayerSelectMap.h"

// 011. 切换场景的简单写法
void LayerStart::startGame()
{
	// 010. 进入LayerSelectMap
	Layer* layer = LayerSelectMap::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);;
}

/* 003. 创建背景图片和菜单项 */
bool LayerStart::init()
{
	Layer::init();

	/* 增加背景图片 */
	Util::getInstance().addBg("background.png", this);

	/* 006. 菜单处理函数 */
	auto callback = [&](Ref* sender)
	{
		MenuItem* item = (MenuItem*)sender;
		// 007. 根据菜单项的Tag，来决定做什么处理
		ItemType tag = (ItemType)item->getTag();

		
		Scene* scene = NULL;
		switch (tag)
		{
			// 009. 点击start按钮时的处理
		case ItemType::Start:
			// Scene* scene = Util::getInstance().createScene(LayerSelectMap::create());
			
			// startGame();
			// 010. 如果不理解createTransitionByLayer，没关系，看011
			scene = createTransitionByLayer(TransitionCrossFade, LayerSelectMap::create(), 2.0f);
			Director::getInstance()->replaceScene(scene);
			break;
		default:
			break;
		}
	};

	struct
	{
		const char* filenameNormal;
		const char* filenameSelect;
	} itemData[4] =
	{
		{"startgame_normal.png", "startgame_select.png"},
		{ "Setting_n.png", "setting_s.png" },
		{ "quitgame_normal.png", "quitgame_select.png" },
		{ "about_normal.png", "about_select.png" }
	};

	/* 004. 根据菜单项数据创建菜单 */
	Menu* menu = Menu::create();
	addChild(menu);
	for (int i = 0; i < sizeof(itemData) / sizeof(*itemData); ++i)
	{
		MenuItem* item = MenuItemImage::create(itemData[i].filenameNormal, itemData[i].filenameSelect);
		item->setCallback(callback);
		// 008. 菜单项的Tag在这里设置
		item->setTag(i);
		menu->addChild(item);
	}
	menu->alignItemsVertically();

	// 005. 调整菜单位置
	Util::getInstance().moveNode(menu, Vec2(0, -70));
	Util::getInstance().moveNode(menu->getChildByTag((int)ItemType::About), Vec2(170, 0));

	return true;
}