#ifndef _LAYER_CTRL_H_
#define _LAYER_CTRL_H_

#include "Util.h"
#include "LayerModel.h"
#include "ui/CocosGUI.h"

class LayerCtrl : public Layer
{
public:
	//CREATE_FUNC(LayerCtrl);

	static LayerCtrl* create(LayerModel* model);

	virtual bool init()override;

	void onExit();

#ifdef WIN32
	void checkKey(float);
#endif
	// menu 触摸处理函数
	void menuCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	// A 按钮 触摸处理函数
	void jumpCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	// B 按钮 触摸处理函数
	void fireCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	// 触摸处理函数
	bool TouchBegan(Touch*, Event*);
	void TouchEnded(Touch*, Event*);
	void TouchMoved(Touch*, Event*);

private:
	// 加载 .csb 文件
	void loadCsbFile();

	// 创建各种控制控件
	void createCtrl();

	// 给各种控件增加触摸处理
	void addTouchCtrl();

	// 判断是否触摸方向键的左边
	bool isTouchOnDirLeft(Touch*);

	// 判断是否触摸方向键的右边
	bool isTouchOnDirRight(Touch*);

	// 向右移动
	void moveRight();

	// 向左移动
	void moveLeft();

	// 停止不动
	void stop();

private:
	LayerModel*		_model	  = nullptr;    // 数据处理层
	
	Node*			_node	  = nullptr;    // 保存csb文件内容
	Sprite*			_ctrlDir  = nullptr;    // 方向控制键
	ui::Button*     _ctrlMenu = nullptr;    // menu按钮
	ui::Button*     _ctrlJump = nullptr;    // A键（跳跃键）
	ui::Button*     _ctrlFire = nullptr;    // B键（子弹）
};

#endif

