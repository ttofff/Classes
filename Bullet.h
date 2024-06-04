#ifndef Bullet_h
#define Bullet_h

#include "cocos2d.h"
#include "Tower.h"
class Monster;
class Bullet : public cocos2d::Sprite
{
public:
	Bullet(TowerType type);
	static Bullet* create(TowerType type);
	bool init() override;
	void onBulletInit(Monster* target);			// �ӵ���ʼ��
	void onBulletUpdate(float dt);				// �ӵ��ƶ�
	void updateDirection();						// ת��
public:
	Monster* target;							// �ӵ�����Ŀ��
	TowerType type;								// �ӵ�������������
private:
	cocos2d::Vec2 dir;							// �ӵ��ƶ�����
};

#endif
