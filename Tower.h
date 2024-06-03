#ifndef Tower_h
#define Tower_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class Monster;
// 塔的类型
enum TowerType
{
    BOTTLE,
    SHIT
};

// 塔类
class Tower : public cocos2d::Sprite
{
public:
    Tower(TowerType type);
    static Tower* create(TowerType type); // 通过类型创建不同的塔
    bool init() override;
    void onTowerInit();// 塔初始化
    bool onTowerUpdate(float dt);// 塔更新
    bool shoot(Monster* monster);// 射击
    void updateDirection(Monster* monster);
    TowerType type;
private:
    float shootDeltaTime;// 射击的间隔时间
    float range;// 攻击范围
};

#endif
