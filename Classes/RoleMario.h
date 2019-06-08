
#ifndef __RoleMario_H__
#define __RoleMario_H__


#include "Role.h"

class RoleMario : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	/* �ⲿ�ӿڣ��޸����ԣ�������ʾ״̬ */
	void jump();
	void moveLeft();
	void moveRight();
	void stop();
	void Dead();
	void autoCtrl1();
	void autoCtrl2();

	/* ��ʱ��������������״̬�޸����ǵ�λ����Ϣ */
	void moveLeft(float dt);
	void moveRight(float dt);
	void moveUp(float dt);
	void moveDown(float dt);

	/* ����������ǵ���ʾ��ͼƬ */
	void updateStatus();

	/* ״̬��װ�����Ը��򵥵Ĵ���״̬�仯 */
	void setFlying(bool fly);
	void setBig(bool big);
	void setRight(bool right);

	/* ״̬�����ı��� */
	bool _big = false;
	bool _flying = false;
	bool _autoCtrl1 = false;
	bool _autoCtrl2 = false;

	Role* _ladder = nullptr;
};

#endif
