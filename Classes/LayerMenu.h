#ifndef _LAYER_MENU_H_
#define _LAYER_MENU_H_

#include "Util.h"

class LayerMenu : public LayerColor
{
public:
	CREATE_FUNC(LayerMenu);

	virtual bool init()override;

private:
	// �������ְ�ť
	void createMusicBtn();

	// ������Ч��ť
	void createEffectBtn();

	// ��Ӵ���
	void addTouchMusicAndEffect();

	//����������
	bool TouchBegan(Touch* touch, Event* ev);
	void TouchEnded(Touch* touch, Event* ev);

private:
	Sprite*		_music	   = nullptr;  // ���־���
	Sprite*		_effect	   = nullptr;  // ��Ч����
	bool		_bMusicOn  = true;     // Ĭ�����ִ�
	bool		_bEffectOn = true;     // Ĭ����Ч��
};

#endif

