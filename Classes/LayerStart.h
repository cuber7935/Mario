#ifndef _LAYER_START_H_
#define _LAYER_START_H_

#include "Util.h"

/* ������һ������ */
class LayerStart : public Layer
{
public:
	CREATE_FUNC(LayerStart);
	virtual bool init()override;

private:
	//�˵�������
	enum class ItemType { Start, Setting, Quit, About };

	//��������
	void createBG();

	//��ťѡ��
	void createItems();

	//��ʼ��Ϸ
	//void startGame();

	//�˵���ص�����
	void itemsCallback(Ref* ref);
};

#endif

