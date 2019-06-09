#ifndef _ROLE_MARIO_H_
#define _ROLE_MARIO_H_

#include "Role.h"


class RoleMario : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	/* �ⲿ�ӿڣ��޸����ԣ�������ʾ״̬ */
	void jump();        //��Ծ
	void moveLeft();    //�����ƶ�
	void moveRight();   //�����ƶ�
	void stop();        //ֹͣ����
	void Dead();        //����
	void autoCtrl1();   //�Զ�����1
	void autoCtrl2();   //�Զ�����2

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

	// װ���ϵ�ģʽ
	void setGodMode(float duration);

	// ж���ϵ�ģʽ
	void unsetGodMode();

	/* ״̬�����ı��� */
	bool _big = false;
	bool _flying = false;
	bool _autoCtrl1 = false;
	bool _autoCtrl2 = false;

	Role* _ladder = nullptr;
};

#endif
