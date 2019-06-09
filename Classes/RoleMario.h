#ifndef _ROLE_MARIO_H_
#define _ROLE_MARIO_H_

#include "Role.h"


class RoleMario : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	/* 外部接口：修改属性，更新显示状态 */
	void jump();        //跳跃
	void moveLeft();    //向左移动
	void moveRight();   //向右移动
	void stop();        //停止不动
	void Dead();        //死亡
	void autoCtrl1();   //自动控制1
	void autoCtrl2();   //自动控制2

	/* 定时器处理函数：根据状态修改主角的位置信息 */
	void moveLeft(float dt);
	void moveRight(float dt);
	void moveUp(float dt);
	void moveDown(float dt);

	/* 负责更新主角的显示的图片 */
	void updateStatus();

	/* 状态封装，可以更简单的处理状态变化 */
	void setFlying(bool fly);
	void setBig(bool big);
	void setRight(bool right);

	// 装载上帝模式
	void setGodMode(float duration);

	// 卸载上帝模式
	void unsetGodMode();

	/* 状态变量的保存 */
	bool _big = false;
	bool _flying = false;
	bool _autoCtrl1 = false;
	bool _autoCtrl2 = false;

	Role* _ladder = nullptr;
};

#endif
