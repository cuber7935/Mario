#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Resources.h"
USING_NS_CC;
USING_NS_CC_EXT;

//窗口大小
#define winSize Director::getInstance()->getWinSize()

//用于调试用的
#define MYDEBUG 1


class Util
{
public:
	//保存当前关卡数
	int _mapIndex = -1; /* mapIndex 从1开始 */

	//单列模式
	static Util* getInstance();

	//创建场景
	Scene* createScene(Node* layer);
	
	//添加背景精灵
	Sprite* addBg(const char* filename, Node* parent);
	
	//移动精灵位置
	void moveNode(Node* node, const Vec2& off);

	//拼接字符串
	const char* format(int idx, const char* prev, const char* suff);

	//加载动画
	void loadAnimation(const char* filename, const Size& frameSize,
		int startIdx, int count, const char* animationName, float delay = 0.0f);
	
	//加载精灵帧
	void loadSpriteFrame(const char* filename, const Size& frameSize, int idx, const char* frameName);

	//转换到地图格子坐标
	Vec2 convertToMap(Vec2 ptInGL, TMXTiledMap* map);

	//是否在地图坐标系中
	bool isCoodInMap(TMXTiledMap* map, Vec2 pos);

private:
	Util(){}
};

//场景切换时动画
#define createTransition(__Type, __scene, __dt, ...)\
	__Type::create(__dt, __scene, ##__VA_ARGS__)

#define createTransitionByLayer(__Type, __layer, __dt, ...)\
	createTransition(__Type, Util::getInstance()->createScene(__layer), __dt, ##__VA_ARGS__)

#endif

