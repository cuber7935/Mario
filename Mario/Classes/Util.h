#ifndef __Util_H__
#define __Util_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#include "Resources.h"

#define winSize Director::getInstance()->getWinSize()

#define MYDEBUG 1


class Util
{
public:
	int _mapIndex = -1; /* mapIndex ´Ó1¿ªÊ¼ */

	static Util& getInstance()
	{
		static Util obj;
		return obj;
	}

	Scene* createScene(Node* layer)
	{
		Scene* ret = Scene::create();
		ret->addChild(layer);
		return ret;
	}

	Sprite* addBg(const char* filename, Node* parent)
	{
		Sprite* sprite = Sprite::create(filename);
		parent->addChild(sprite);
		sprite->setPosition(winSize.width / 2, winSize.height / 2);
		return sprite;
	}

	void moveNode(Node* node, const Vec2& off)
	{
		node->setPosition(node->getPosition() + off);
	}

	const char* format(int idx, const char* prev, const char* suff)
	{
		static char ret[256];
		sprintf(ret, "%s%d%s", prev, idx, suff);
		return ret;
	}

	void loadAnimation(const char* filename, const Size& frameSize, 
		int startIdx, int count, const char* animationName, float delay=0.0f)
	{
		if (AnimationCache::getInstance()->getAnimation(animationName))
			return;

		Vector<SpriteFrame*> frames;
		for (int i = startIdx; i < startIdx + count; ++i)
		{
			SpriteFrame* frame = SpriteFrame::create(filename, Rect(i*frameSize.width, 0, frameSize.width, frameSize.height));
			frames.pushBack(frame);
		}
		
		Animation* ani = Animation::createWithSpriteFrames(frames, delay);
		AnimationCache::getInstance()->addAnimation(ani, animationName);
	}
	
	void loadSpriteFrame(const char* filename, const Size& frameSize, int idx, const char* frameName)
	{
		SpriteFrame* frame = SpriteFrame::create(filename, Rect(idx*frameSize.width, 0, frameSize.width, frameSize.height));
		SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
	}

	Vec2 convertToMap(Vec2 ptInGL, TMXTiledMap* map)
	{
		Size sizeTile = map->getTileSize();
		int x = ptInGL.x / sizeTile.width;
		int y = ptInGL.y / sizeTile.height;

		y = map->getMapSize().height - 1 - y;

		return Vec2(x, y);
	}

	Vec2 convertToGL(Vec2 ptInMap, TMXTiledMap* map)
	{}

	bool isCoodInMap(TMXTiledMap* map, Vec2 pos)
	{
		return pos.x < map->getMapSize().width && pos.y < map->getMapSize().height && pos.x >= 0 && pos.y >= 0;
	}
private:
	Util(){}
};

#define createTransition(__Type, __scene, __dt, ...)\
	__Type::create(__dt, __scene, ##__VA_ARGS__)

#define createTransitionByLayer(__Type, __layer, __dt, ...)\
	createTransition(__Type, Util::getInstance().createScene(__layer), __dt, ##__VA_ARGS__)



#endif

