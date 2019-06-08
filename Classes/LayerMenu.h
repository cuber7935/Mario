#ifndef _LAYER_MENU_H_
#define _LAYER_MENU_H_

#include "Util.h"

class LayerMenu : public LayerColor
{
public:
	CREATE_FUNC(LayerMenu);

	virtual bool init()override;

private:
	// 创建音乐按钮
	void createMusicBtn();

	// 创建音效按钮
	void createEffectBtn();

	// 添加触摸
	void addTouchMusicAndEffect();

	//触摸处理函数
	bool TouchBegan(Touch* touch, Event* ev);
	void TouchEnded(Touch* touch, Event* ev);

private:
	Sprite*		_music	   = nullptr;  // 音乐精灵
	Sprite*		_effect	   = nullptr;  // 音效精灵
	bool		_bMusicOn  = true;     // 默认音乐打开
	bool		_bEffectOn = true;     // 默认音效打开
};

#endif

