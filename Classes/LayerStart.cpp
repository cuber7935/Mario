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

	// 1.���ӱ���ͼƬ 
	this->createBG();

	// 2.���ݲ˵������ݴ����˵�
	this->createItems();

	return true;
}

//��������
void LayerStart::createBG()
{
	Util::getInstance()->addBg("background.png", this);
}

//��ťѡ��
void LayerStart::createItems()
{	
	Menu* menu = Menu::create();
	this->addChild(menu);
	for (int i = 0; i < sizeof(itemData) / sizeof(*itemData); ++i)
	{
		MenuItem* item = MenuItemImage::create(itemData[i].filenameNormal, itemData[i].filenameSelect);
		item->setCallback(CC_CALLBACK_1(LayerStart::itemsCallback, this));
		// ���ò˵����tag
		item->setTag(i);
		menu->addChild(item);
	}
	menu->alignItemsVertically();

	// �����˵�λ��
	Util::getInstance()->moveNode(menu, Vec2(0, -70));
	Util::getInstance()->moveNode(menu->getChildByTag((int)ItemType::About), Vec2(170, 0));
}

#if 0
//���л�����
void LayerStart::startGame()
{
	// ����LayerSelectMap
	Layer* layer = LayerSelectMap::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}
#endif

//�˵���ص�����
void LayerStart::itemsCallback(Ref * ref)
{
	MenuItem* item = (MenuItem*)ref;
	// ���ݲ˵����Tag����������ʲô����
	ItemType tag = (ItemType)item->getTag();

	Scene* scene = nullptr;

	switch (tag)
	{
	case ItemType::Start:    // �����ʼ������ѡ�ؽ���
		scene = createTransitionByLayer(TransitionCrossFade, LayerSelectMap::create(), 2.0f);
		Director::getInstance()->replaceScene(scene);
		break;
	case ItemType::Quit:     // ����˳��� ��Ϸ�˳�
		Director::getInstance()->end();
		break;
	case ItemType::About:    // ���ڽ���
		break;
	case ItemType::Setting:  // ���ý���
		break;
	default:
		break;
	}
}
