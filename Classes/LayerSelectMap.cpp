#include "LayerSelectMap.h"
#include "LayerStart.h"
#include "LayerProgress.h"


MyTableViewDataSource::MyTableViewDataSource()
{
	this->addSelectViews();
}

Size MyTableViewDataSource::cellSizeForTable(TableView* table)
{
	return winSize;
}

TableViewCell* MyTableViewDataSource::tableCellAtIndex(TableView *table, ssize_t idx)
{	
	return this->cells_.at(idx);
}

ssize_t MyTableViewDataSource::numberOfCellsInTableView(TableView *table)
{
	return this->cells_.size();
}

void MyTableViewDataSource::addSelectViews()
{
	for (int i = 0; i < 8; ++i)
	{
		TableViewCell* cell = TableViewCell::create();

		const char* filename = Util::getInstance()->format(i + 1, "select", ".jpg");
		Sprite* sprite = Util::getInstance()->addBg(filename, cell);

		sprite->setTag(i + 1000);
		
		this->cells_.pushBack(cell);
	}
}

bool LayerSelectMap::init()
{
	if (!Layer::init())
		return false;

	// ��ӱ���
	initBG();

	// ��ӹ�����ͼ
	initTableView();

	// ���Ӵ���
	//initTouch();

	// ���ӷ��ذ�ť
	initBackMenu();

	return true;
}

void LayerSelectMap::tableCellTouched(TableView * table, TableViewCell * cell)
{
	//log("%d", cell->getIdx());
	//ѡ��
	Util::getInstance()->_mapIndex = cell->getIdx() + 1;
	//Scene* scene = createTransitionByLayer(TransitionPageTurn, LayerProgress::create(), 1.0f, true);
	Director::getInstance()->replaceScene(Util::getInstance()->createScene(LayerProgress::create()));
}

// ��ӱ���
void LayerSelectMap::initBG()
{

	Util::getInstance()->addBg("bg.png", this);
}

// ��ӹ�����ͼ
void LayerSelectMap::initTableView()
{
	// ����TableView
	view_ = TableView::create(&soruce_, winSize);
	this->addChild(view_);
	view_->setDirection(ScrollView::Direction::HORIZONTAL);

	// ���¼�����ͼ
	view_->reloadData();

	// ���ô���
	view_->setDelegate(this);
}

// ��ӷ��ذ�ť
void LayerSelectMap::initBackMenu()
{
	MenuItem* item = MenuItemImage::create("backA.png", "backB.png");
	item->setCallback(CC_CALLBACK_1(LayerSelectMap::itemCallBack, this));
	
	Menu* menu = Menu::createWithItem(item);
	this->addChild(menu);

	Rect rcItem = item->getBoundingBox();
	menu->setPosition(winSize.width - rcItem.size.width / 2, rcItem.size.height / 2);
}

// ���ذ�ť�Ļص�����
void LayerSelectMap::itemCallBack(Ref * ref)
{
	Scene* scene = Util::getInstance()->createScene(LayerStart::create());
	Director::getInstance()->replaceScene(scene);
}
