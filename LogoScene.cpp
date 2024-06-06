#include "LogoScene.h"
#include "StartScene.h"

LogoScene* LogoScene::create()
{
    LogoScene* ret = new LogoScene();
    if(ret && ret->init())
    {
        ret->autorelease();
    }else
    {
        delete ret;
        ret = nullptr;
    }
    
    return ret;
}

bool LogoScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    // 创建白色背景
    LayerColor* layerColor = LayerColor::create(Color4B::WHITE);
    this->addChild(layerColor, 0);
    
    // 创建Logo图片背景
    Sprite* logo = Sprite::create("CarrotLogo.png");
    logo->setPosition(Vec2(480,320));
	logo->setScale(.5f);
    this->addChild(logo, 1);

	//切换到下一场景
	scheduleOnce([&](float dt){
		Director* director = Director::getInstance();
		StartScene* startScene = StartScene::create();
		TransitionCrossFade* cross = TransitionCrossFade::create(1.f, startScene);
		director->replaceScene(cross);
	}, 2.f, "start");

    return true;
}
