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

// ͨ����Ƭ��ͼ��ȡ��������·��
void GameMap::getWayPoints(const std::string filename)
{
	// ��ȡPATH�����
	TMXObjectGroup* group = this->getObjectGroup(filename);
	// ��ȡ����������ж���
	ValueVector valueVector = group->getObjects();
	// �������ж���
	for (Value value : valueVector)
	{
		// ��Valueת��ΪValueMap
		ValueMap valueMap = value.asValueMap();
		// ��ȡ��Ӧ��x��y����
		float x = valueMap["x"].asFloat();
		float y = valueMap["y"].asFloat();
		// ����Ӧ��x��y��ɵ�������ӵ�vector��
		// ע��:��Ƭ��ͼ���꽨�����Ͻǣ�ת�������ĵ�������Ӵ�Сһ��
		wayPoints.push_back(Vec2(x + 40, y - 40));
	}
}

// ͨ����Ƭ��ͼ��ȡ��������
void GameMap::getTowerArea(const std::string filename)
{
	// ��ȡObj�����
	TMXObjectGroup* group = this->getObjectGroup(filename);
	// ��ȡ����������ж���
	ValueVector valueVector = group->getObjects();
	// �������ж���
	for (Value value : valueVector)
	{
		// ��Valueת��ΪValueMap
		ValueMap valueMap = value.asValueMap();
		// ��ȡ��Ӧ��x��y����
		float x = valueMap["x"].asFloat();
		float y = valueMap["y"].asFloat();
		float width = valueMap["width"].asFloat();
		float height = valueMap["height"].asFloat();
		// �������Σ���ӵ�����������
		towerArea.push_back(Rect(x, y, width, height));
	}
}