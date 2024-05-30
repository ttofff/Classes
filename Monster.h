#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"
#include <vector>
// ��������
enum MonsterType
{
	fly_yellow,
	fly_blue
};

// ������
class Monster : public cocos2d::Sprite
{
public:
	Monster(MonsterType type);
	static Monster* create(MonsterType type);
	bool init() override;
	void onMonsterInit(std::vector<cocos2d::Vec2> wayPoints);// �����ʼ��
	bool onMonsterUpdate(float dt);// ������£��ƶ���
	std::vector<cocos2d::Vec2> wayPoints; //�ƶ�·����
private:
	
	int curIndex;// Ŀǰ���ڵ�·�����±�
	MonsterType type;
public:
	int hp;// ����Ѫ��
};

#endif
