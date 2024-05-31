#ifndef _GameMap_H_
#define _GameMap_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameMap : public TMXTiledMap
{
public:
	// �洢��������·��
	std::vector<cocos2d::Vec2> wayPoints;
	// �洢�����������
	std::vector<cocos2d::Rect> towerArea;
public:
	static GameMap* create(const std::string filename);
	virtual bool init(const std::string filename);

	// ͨ����Ƭ��ͼ��ȡ��������·��
	void getWayPoints(const std::string filename);
	// ͨ����Ƭ��ͼ��ȡ��������
	void getTowerArea(const std::string filename);
};
#endif