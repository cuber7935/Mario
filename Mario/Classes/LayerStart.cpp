#include "LayerStart.h"
#include "LayerSelectMap.h"

// 011. �л������ļ�д��
void LayerStart::startGame()
{
	// 010. ����LayerSelectMap
	Layer* layer = LayerSelectMap::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);;
}

/* 003. ��������ͼƬ�Ͳ˵��� */
bool LayerStart::init()
{
	Layer::init();

	/* ���ӱ���ͼƬ */
	Util::getInstance().addBg("background.png", this);

	/* 006. �˵������� */
	auto callback = [&](Ref* sender)
	{
		MenuItem* item = (MenuItem*)sender;
		// 007. ���ݲ˵����Tag����������ʲô����
		ItemType tag = (ItemType)item->getTag();

		
		Scene* scene = NULL;
		switch (tag)
		{
			// 009. ���start��ťʱ�Ĵ���
		case ItemType::Start:
			// Scene* scene = Util::getInstance().createScene(LayerSelectMap::create());
			
			// startGame();
			// 010. ��������createTransitionByLayer��û��ϵ����011
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

	/* 004. ���ݲ˵������ݴ����˵� */
	Menu* menu = Menu::create();
	addChild(menu);
	for (int i = 0; i < sizeof(itemData) / sizeof(*itemData); ++i)
	{
		MenuItem* item = MenuItemImage::create(itemData[i].filenameNormal, itemData[i].filenameSelect);
		item->setCallback(callback);
		// 008. �˵����Tag����������
		item->setTag(i);
		menu->addChild(item);
	}
	menu->alignItemsVertically();

	// 005. �����˵�λ��
	Util::getInstance().moveNode(menu, Vec2(0, -70));
	Util::getInstance().moveNode(menu->getChildByTag((int)ItemType::About), Vec2(170, 0));

	return true;
}