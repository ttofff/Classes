#include "GameMap.h"
GameMap* GameMap::create(const std::string filename)
{
	GameMap* ret = new GameMap();
	if (ret && ret->init(filename))
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}

	return ret;
}
bool GameMap::init(const std::string filename)
{
	if (!TMXTiledMap::initWithTMXFile(filename))
	{
		return false;
	}

	return true;
}

// 通过瓦片地图获取怪物行走路径
void GameMap::getWayPoints(const std::string filename)
{
	// 获取PATH对象层
	TMXObjectGroup* group = this->getObjectGroup(filename);
	// 获取对象层上所有对象
	ValueVector valueVector = group->getObjects();
	// 遍历所有对象
	for (Value value : valueVector)
	{
		// 将Value转换为ValueMap
		ValueMap valueMap = value.asValueMap();
		// 获取对应的x和y属性
		float x = valueMap["x"].asFloat();
		float y = valueMap["y"].asFloat();
		// 将对应的x和y组成的向量添加到vector中
		// 注意:瓦片地图坐标建在左上角，转换到中心点各减格子大小一半
		wayPoints.push_back(Vec2(x + 40, y - 40));
	}
}

// 通过瓦片地图获取建塔区域
void GameMap::getTowerArea(const std::string filename)
{
	// 获取Obj对象层
	TMXObjectGroup* group = this->getObjectGroup(filename);
	// 获取对象层上所有对象
	ValueVector valueVector = group->getObjects();
	// 遍历所有对象
	for (Value value : valueVector)
	{
		// 将Value转换为ValueMap
		ValueMap valueMap = value.asValueMap();
		// 获取对应的x和y属性
		float x = valueMap["x"].asFloat();
		float y = valueMap["y"].asFloat();
		float width = valueMap["width"].asFloat();
		float height = valueMap["height"].asFloat();
		// 创建矩形，添加到矩形区域中
		towerArea.push_back(Rect(x, y, width, height));
	}
}