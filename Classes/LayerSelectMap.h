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
	// ���ѡ�� ��ͼ
	void addSelectViews();
};



// ѡ��ؿ����� 
class LayerSelectMap : public Layer, public TableViewDelegate
{
public:
	CREATE_FUNC(LayerSelectMap);

	virtual bool init()override;

	virtual void tableCellTouched(TableView* table, TableViewCell* cell)override;

private:
	// ��ʼ������
	void initBG();

	// ��ʼ��TableView
	void initTableView();

	// ���touch����
	//void initTouch();

	// ��ӷ��ذ�ť
	void initBackMenu();

	// ���ذ�ť�Ļص�����
	void itemCallBack(Ref* ref);

private:
	MyTableViewDataSource soruce_;
	TableView* view_ = nullptr;
};

#endif

