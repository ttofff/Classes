#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"
#include <vector>
// ��������
enum MonsterType
{
	Monster1=1,
	Monster2,
	Monster3,
	Monster4,
	Monster5,
	Monster6,
	Monster7,
	Monster8
};

// ������
class Monster : public cocos2d::Sprite
{
public:
	Monster(MonsterType type);
	static Monster* create(MonsterType type, int kind);
	bool init() override;
	void onMonsterInit(std::vector<cocos2d::Vec2> wayPoints);// �����ʼ��
	bool onMonsterUpdate(float dt);// ������£��ƶ���
	std::vector<cocos2d::Vec2> wayPoints; //�ƶ�·����
private:
	float speed = 150.f;
	int curIndex;// Ŀǰ���ڵ�·�����±�
	MonsterType type;
public:
	int monsterKind; // ��������
	int hp;// ����Ѫ��
	float GetSpeed()const { return speed; }
	void SetSpeed(float s) { speed = s; }
};

#endif
