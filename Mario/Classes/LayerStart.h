#ifndef __LayerStart_H__
#define __LayerStart_H__

#include "Util.h"

/* 002. 开场第一个场景 */
class LayerStart : public Layer
{
public:
	CREATE_FUNC(LayerStart);

	enum class ItemType{Start, Setting, Quit, About};

	bool init();
	void startGame();
};

#endif

