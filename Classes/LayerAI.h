#ifndef __LayerAI_H__
#define __LayerAI_H__

#include "Util.h"
#include "LayerModel.h"

class LayerAI : public Layer
{
public:
	static LayerAI* create(LayerModel* model);

	virtual bool init()override;

	void onExit();
	
	// ��ʱ�� ���������жϽ�ɫ���Ƿ��˶���
	void checkRunning(float);

	// Դmodel �д�Ž�ɫ�ǵ����� �����ز�����
	void loadModelDataAndSort();

private:
	LayerModel*		_model = nullptr;
	Vector<Role*>	_stopRoles;
};

#endif

