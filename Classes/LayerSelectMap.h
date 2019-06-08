#ifndef _LAYER_SELECT_MAP_H_
#define _LAYER_SELECT_MAP_H_

#include "Util.h"

class MyTableViewDataSource : public TableViewDataSource
{
public:
	MyTableViewDataSource();

	virtual Size cellSizeForTable(TableView* table)override;

	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx)override;

	virtual ssize_t numberOfCellsInTableView(TableView *table)override;

	Vector<TableViewCell*> cells_;

private:
	// 添加选择 视图
	void addSelectViews();
};



// 选择关卡场景 
class LayerSelectMap : public Layer, public TableViewDelegate
{
public:
	CREATE_FUNC(LayerSelectMap);

	virtual bool init()override;

	virtual void tableCellTouched(TableView* table, TableViewCell* cell)override;

private:
	// 初始化背景
	void initBG();

	// 初始化TableView
	void initTableView();

	// 添加touch处理
	//void initTouch();

	// 添加返回按钮
	void initBackMenu();

	// 返回按钮的回调函数
	void itemCallBack(Ref* ref);

private:
	MyTableViewDataSource soruce_;
	TableView* view_ = nullptr;
};

#endif

