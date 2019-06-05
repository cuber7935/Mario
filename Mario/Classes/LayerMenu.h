#ifndef __LayerMenu_H__
#define __LayerMenu_H__
#include "Util.h"
class LayerMenu : public LayerColor
{
public:
	CREATE_FUNC(LayerMenu);

	bool init();

	bool _bMusicOn = true;
	bool _bEffectOn = true;
};

#endif

