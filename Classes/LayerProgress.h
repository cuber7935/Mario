#ifndef _LAYER_PROGRESS_H_
#define _LAYER_PROGRESS_H_

#include "Util.h"
#include "ui/CocosGUI.h"

#define util Util::getInstance()

// ������
class LayerProgress : public Layer
{
public:
	CREATE_FUNC(LayerProgress);

	virtual bool init()override;

	void update(float);

private:
	// ��ӱ���
	void initBG();

	// ��ӽ������ϵľ���
	void addSprite();

	// ����ִ�ж���
	void loadAnimation();

	// ������Դ
	void loadResources();

	// ���ض�����֡
	void loadAnimationsAndFrames();

private:
	ui::LoadingBar* _loadingBar = nullptr;      // ����������
	Sprite*			_mario		= nullptr;      // �������ϸ��澫��
	int				_curLoadImageCount	= 0;    // ��ǰ���ص���Դ����
	int				_totalImageCount	= 0;    // ��Դ����
};

#endif

