#ifndef __LayerProgress_H__
#define __LayerProgress_H__

#include "Util.h"
#include "ui/CocosGUI.h"

class LayerProgress : public Layer
{
public:
	CREATE_FUNC(LayerProgress);

	bool init();

	void initBG();
	void loadResources();
	void loadAnimationsAndFrames();

	ui::LoadingBar* _loadingBar;

	Sprite* _mario;

	int _curLoadImageCount;
	int _totalImageCount;

	void update(float);

	Util& util = Util::getInstance();
};

#endif

