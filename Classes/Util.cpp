#include "Util.h"

Util*  Util::getInstance()
{
	static Util util;
	return &util;
}

//��������
Scene * Util::createScene(Node * layer)
{
	Scene* ret = Scene::create();
	ret->addChild(layer);
	return ret;
}

//��ӱ�������
Sprite * Util::addBg(const char * filename, Node * parent)
{
	Sprite* sprite = Sprite::create(filename);
	parent->addChild(sprite);
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	return sprite;
}

//�ƶ�����λ��
void Util::moveNode(Node * node, const Vec2 & off)
{
	node->setPosition(node->getPosition() + off);
}

//ƴ���ַ���
const char * Util::format(int idx, const char * prev, const char * suff)
{
	static char ret[256];
	sprintf(ret, "%s%d%s", prev, idx, suff);
	return ret;
}

//���ض���
void Util::loadAnimation(const char * filename, const Size & frameSize, int startIdx, int count, const char * animationName, float delay)
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

//���ؾ���֡
void Util::loadSpriteFrame(const char * filename, const Size & frameSize, int idx, const char * frameName)
{
	SpriteFrame* frame = SpriteFrame::create(filename, Rect(idx*frameSize.width, 0, frameSize.width, frameSize.height));
	SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
}

Vec2 Util::convertToMap(Vec2 ptInGL, TMXTiledMap * map)
{
	Size sizeTile = map->getTileSize();
	int x = ptInGL.x / sizeTile.width;
	int y = ptInGL.y / sizeTile.height;

	y = map->getMapSize().height - 1 - y;

	return Vec2(x, y);
}

//�Ƿ��ڵ�ͼ����ϵ��
bool Util::isCoodInMap(TMXTiledMap * map, Vec2 pos)
{
	return pos.x < map->getMapSize().width && pos.y < map->getMapSize().height && pos.x >= 0 && pos.y >= 0;
}
