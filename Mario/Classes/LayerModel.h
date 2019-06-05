#ifndef __LayerModel_H__
#define __LayerModel_H__

#include "Util.h"
#include "Role.h"
#include "RoleMario.h"

class LayerModel : public Layer
{
public:
	CREATE_FUNC(LayerModel);

	TMXTiledMap* _map;
	RoleMario* _mario;
	Role* _bridge = nullptr;
	Vector<Role*> _roles;

	void collision(float dt);
	void scrollMap();
	void isGameOver();
	void eatCoin();

	Util& util = Util::getInstance();

	bool init();
	void initMap();
	void initRoles();
	void initBossFireEvent();
	void initBreakBridgeEvent();

	void breakBridge(EventCustom*);
	void breakBridge1(Vec2 pos, int idx);

	/* for mario */
	void jump();
	void moveLeft();
	void moveRight();
	void stop();
};

#endif

