#ifndef _LAYER_PROGRESS_H_
#define _LAYER_PROGRESS_H_

#include "Util.h"
#include "ui/CocosGUI.h"

#define util Util::getInstance()

// 进度条
class LayerProgress : public Layer
{
public:
	CREATE_FUNC(LayerProgress);

	virtual bool init()override;

	void update(float);

private:
	// 添加背景
	void initBG();

	// 添加进度条上的精灵
	void addSprite();

	// 精灵执行动画
	void loadAnimation();

	// 加载资源
	void loadResources();

	// 加载动画和帧
	void loadAnimationsAndFrames();

private:
	ui::LoadingBar* _loadingBar = nullptr;      // 进度条工具
	Sprite*			_mario		= nullptr;      // 进度条上跟随精灵
	int				_curLoadImageCount	= 0;    // 当前加载的资源数量
	int				_totalImageCount	= 0;    // 资源总量
};

#endif

