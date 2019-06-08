#include "LayerStart.h"
#include "LayerSelectMap.h"

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

bool LayerStart::init()
{
	Layer::init();

	// 1.增加背景图片 
	this->createBG();

	// 2.根据菜单项数据创建菜单
	this->createItems();

	return true;
}

//创建背景
void LayerStart::createBG()
{
	Util::getInstance()->addBg("background.png", this);
}

//按钮选项
void LayerStart::createItems()
{	
	Menu* menu = Menu::create();
	this->addChild(menu);
	for (int i = 0; i < sizeof(itemData) / sizeof(*itemData); ++i)
	{
		MenuItem* item = MenuItemImage::create(itemData[i].filenameNormal, itemData[i].filenameSelect);
		item->setCallback(CC_CALLBACK_1(LayerStart::itemsCallback, this));
		// 设置菜单项的tag
		item->setTag(i);
		menu->addChild(item);
	}
	menu->alignItemsVertically();

	// 调整菜单位置
	Util::getInstance()->moveNode(menu, Vec2(0, -70));
	Util::getInstance()->moveNode(menu->getChildByTag((int)ItemType::About), Vec2(170, 0));
}

#if 0
//简单切换场景
void LayerStart::startGame()
{
	// 进入LayerSelectMap
	Layer* layer = LayerSelectMap::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}
#endif

//菜单项回调函数
void LayerStart::itemsCallback(Ref * ref)
{
	MenuItem* item = (MenuItem*)ref;
	// 根据菜单项的Tag，来决定做什么处理
	ItemType tag = (ItemType)item->getTag();

	Scene* scene = nullptr;

	switch (tag)
	{
	case ItemType::Start:    // 点击开始，进入选关界面
		scene = createTransitionByLayer(TransitionCrossFade, LayerSelectMap::create(), 2.0f);
		Director::getInstance()->replaceScene(scene);
		break;
	case ItemType::Quit:     // 点击退出， 游戏退出
		Director::getInstance()->end();
		break;
	case ItemType::About:    // 关于界面
		break;
	case ItemType::Setting:  // 设置界面
		break;
	default:
		break;
	}
}
