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
	// menu ����������
	void menuCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	// A ��ť ����������
	void jumpCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	// B ��ť ����������
	void fireCtrlCallback(Ref* sender, ui::Widget::TouchEventType eventType);

	// ����������
	bool TouchBegan(Touch*, Event*);
	void TouchEnded(Touch*, Event*);
	void TouchMoved(Touch*, Event*);

private:
	// ���� .csb �ļ�
	void loadCsbFile();

	// �������ֿ��ƿؼ�
	void createCtrl();

	// �����ֿؼ����Ӵ�������
	void addTouchCtrl();

	// �ж��Ƿ�������������
	bool isTouchOnDirLeft(Touch*);

	// �ж��Ƿ�����������ұ�
	bool isTouchOnDirRight(Touch*);

	// �����ƶ�
	void moveRight();

	// �����ƶ�
	void moveLeft();

	// ֹͣ����
	void stop();

private:
	LayerModel*		_model	  = nullptr;    // ���ݴ����
	
	Node*			_node	  = nullptr;    // ����csb�ļ�����
	Sprite*			_ctrlDir  = nullptr;    // ������Ƽ�
	ui::Button*     _ctrlMenu = nullptr;    // menu��ť
	ui::Button*     _ctrlJump = nullptr;    // A������Ծ����
	ui::Button*     _ctrlFire = nullptr;    // B�����ӵ���
};

#endif

