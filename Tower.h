#ifndef Tower_h
#define Tower_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class Monster;
// 塔的类型
enum TowerType
{
	BOTTLE,
	SHIT,
	FAN,
	STAR
};

// 塔类
class Tower : public cocos2d::Sprite
{
public:
	Tower(TowerType type);
	static Tower* create(TowerType type); // 通过类型创建不同的塔
	static Tower* create(TowerType type,int i); // 通过类型创建不同的塔
	bool init() override;
	void onTowerInit();// 塔初始化
	bool onTowerUpdate(float dt);// 塔更新
	bool shoot(Monster* monster);// 射击
	void updateDirection(Monster* monster);
	TowerType type;
	__String* TowerAnim;
	int Uptime;			//升级次数
	__String* dz;
	Sprite* dzsp;
private:
	float shootDeltaTime;// 射击的间隔时间
	float range;// 攻击范围
	bool IsRotator;			//本体是否转动
	
};

#endif
