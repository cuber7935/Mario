#ifndef _LAYER_MODEL_H_
#define _LAYER_MODEL_H_

#include "Util.h"
#include "Role.h"
#include "RoleMario.h"
#define util Util::getInstance()

// ��Ÿ������ݵĲ�
class LayerModel : public Layer
{
public:
	CREATE_FUNC(LayerModel);

	virtual bool init()override;

	// ��ײ��� ������
	void collision(float dt);

	/* for mario */
	void jump();
	void moveLeft();
	void moveRight();
	void stop();

	// ��ȡ��ǰ��ͼ
	TMXTiledMap* getCurTiledMap()const;

private:
	// ��ʼ����ͼ
	void initMap();

	// ��ʼ����ɫ��
	void initRoles();

	// boss �����ӵ��¼�
	void initBossFireEvent();

	// �ж����¼�
	void initBreakBridgeEvent();

	// Mario ���� שͷ �¼�
	void initHitBlockEvent();

	// BOSS�����ӵ� ������
	void bossFire(EventCustom* ev);

	// �ж��� ������
	void breakBridge(EventCustom*);

	// Mario ����שͷ ������
	void hitBlock(EventCustom* ev);

	// �ж���
	void breakBridge1(Vec2 pos, int idx);
	
	// ������ͼ
	void scrollMap();

	// �ж���Ϸ�Ƿ����
	void isGameOver();

	// �Խ��
	void eatCoin();

public:
	Vector<Role*>	_roles;               // ��Ÿ��ֽ�ɫ���Ա��Ӣ������ײ���

private:
	TMXTiledMap*	_map	= nullptr;    // ��ͼ
	RoleMario*		_mario  = nullptr;    // Ӣ��
	Role*			_bridge = nullptr;    // ��
};

#endif

