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

	// 添加背景
	initBG();

	// 添加滚动视图
	initTableView();

	// 增加触摸
	//initTouch();

	// 增加返回按钮
	initBackMenu();

	return true;
}

void LayerSelectMap::tableCellTouched(TableView * table, TableViewCell * cell)
{
	//log("%d", cell->getIdx());
	//选关
	Util::getInstance()->_mapIndex = cell->getIdx() + 1;
	//Scene* scene = createTransitionByLayer(TransitionPageTurn, LayerProgress::create(), 1.0f, true);
	Director::getInstance()->replaceScene(Util::getInstance()->createScene(LayerProgress::create()));
}

// 添加背景
void LayerSelectMap::initBG()
{

	Util::getInstance()->addBg("bg.png", this);
}

// 添加滚动视图
void LayerSelectMap::initTableView()
{
	// 创建TableView
	view_ = TableView::create(&soruce_, winSize);
	this->addChild(view_);
	view_->setDirection(ScrollView::Direction::HORIZONTAL);

	// 重新加载视图
	view_->reloadData();

	// 设置代理
	view_->setDelegate(this);
}

// 添加返回按钮
void LayerSelectMap::initBackMenu()
{
	MenuItem* item = MenuItemImage::create("backA.png", "backB.png");
	item->setCallback(CC_CALLBACK_1(LayerSelectMap::itemCallBack, this));
	
	Menu* menu = Menu::createWithItem(item);
	this->addChild(menu);

	Rect rcItem = item->getBoundingBox();
	menu->setPosition(winSize.width - rcItem.size.width / 2, rcItem.size.height / 2);
}

// 返回按钮的回调函数
void LayerSelectMap::itemCallBack(Ref * ref)
{
	Scene* scene = Util::getInstance()->createScene(LayerStart::create());
	Director::getInstance()->replaceScene(scene);
}
