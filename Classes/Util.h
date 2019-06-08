#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Resources.h"
USING_NS_CC;
USING_NS_CC_EXT;

//���ڴ�С
#define winSize Director::getInstance()->getWinSize()

//���ڵ����õ�
#define MYDEBUG 1


class Util
{
public:
	//���浱ǰ�ؿ���
	int _mapIndex = -1; /* mapIndex ��1��ʼ */

	//����ģʽ
	static Util* getInstance();

	//��������
	Scene* createScene(Node* layer);
	
	//��ӱ�������
	Sprite* addBg(const char* filename, Node* parent);
	
	//�ƶ�����λ��
	void moveNode(Node* node, const Vec2& off);

	//ƴ���ַ���
	const char* format(int idx, const char* prev, const char* suff);

	//���ض���
	void loadAnimation(const char* filename, const Size& frameSize,
		int startIdx, int count, const char* animationName, float delay = 0.0f);
	
	//���ؾ���֡
	void loadSpriteFrame(const char* filename, const Size& frameSize, int idx, const char* frameName);

	//ת������ͼ��������
	Vec2 convertToMap(Vec2 ptInGL, TMXTiledMap* map);

	//�Ƿ��ڵ�ͼ����ϵ��
	bool isCoodInMap(TMXTiledMap* map, Vec2 pos);

private:
	Util(){}
};

//�����л�ʱ����
#define createTransition(__Type, __scene, __dt, ...)\
	__Type::create(__dt, __scene, ##__VA_ARGS__)

#define createTransitionByLayer(__Type, __layer, __dt, ...)\
	createTransition(__Type, Util::getInstance()->createScene(__layer), __dt, ##__VA_ARGS__)

#endif

