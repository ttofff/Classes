#ifndef _GameMap_H_
#define _GameMap_H_
#include "cocos2d.h"
using namespace cocos2d;
class GameMap : public TMXTiledMap
{
public:
	// 存储怪物行走路径
	std::vector<cocos2d::Vec2> wayPoints;
	// 存储建塔区域矩形
	std::vector<cocos2d::Rect> towerArea;
public:
	static GameMap* create(const std::string filename);
	virtual bool init(const std::string filename);

	// 通过瓦片地图获取怪物行走路径
	void getWayPoints(const std::string filename);
	// 通过瓦片地图获取建塔区域
	void getTowerArea(const std::string filename);
};
#endif