#include"AboutScene.h"
#include"StartScene.h"
#include"ui\CocosGUI.h"

using namespace cocos2d::ui;

int AboutScene::n = 1;

bool AboutScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//±³¾°Í¼
	Sprite* mainbg = Sprite::create("2.png");
	mainbg->setPosition(Vec2(480, 320));
	mainbg->setScale(1.5f);
	this->addChild(mainbg, 0);
	//´´½¨×ÔÎÒ½éÉÜ
	__String * str = __String::createWithFormat("zwjs\\%d.png", n);
	Button* theme_pack01 = Button::create(str->getCString());
	theme_pack01->setPosition(Vec2(480, 320));
	theme_pack01->setScale(0.5f);
	theme_pack01->setPressedActionEnabled(true);
	this->addChild(theme_pack01, 1);

	//×óÒÆ°´Å¥
	if (this->n > 1)
	{
		Button* theme_pointleft_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointleft_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointleft_pressed.png");
		theme_pointleft_normal->setPosition(Vec2(100, 320));
		theme_pointleft_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointleft_normal, 3);
		theme_pointleft_normal->addClickEventListener([&](Ref* ref)
		{
			this->n = this->n - 1 < 1 ? 1 : n - 1;
			Director* director = Director::getInstance();
			AboutScene* aboutScene =AboutScene::create();
			TransitionCrossFade* Cross = TransitionCrossFade::create(.5f, aboutScene);
			director->replaceScene(Cross);
		});

	}
	//ÓÒÒÆ°´Å¥
	if (this->n < Max)
	{
		Button* theme_pointright_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_pointright_normal.png", "Themes\\scene\\themescene1-hd\\theme_pointright_pressed.png");
		theme_pointright_normal->setPosition(Vec2(860, 320));
		theme_pointright_normal->setPressedActionEnabled(true);
		this->addChild(theme_pointright_normal, 3);
		theme_pointright_normal->addClickEventListener([&](Ref* ref)
		{
			this->n = this->n + 1 > Max ? Max : n + 1;
			Director* director = Director::getInstance();
			AboutScene* aboutScene = AboutScene::create();
			TransitionCrossFade* Cross = TransitionCrossFade::create(.5f, aboutScene);
			director->replaceScene(Cross);
		});
	}
	//·µ»ØÖ÷Ò³°´Å¥
	Button* theme_home_normal = Button::create("Themes\\scene\\themescene1-hd\\theme_home_normal.png", "Themes\\scene\\themescene1-hd\\theme_home_pressed.png");
	theme_home_normal->setPosition(Vec2(30, 610));
	theme_home_normal->setPressedActionEnabled(true);
	this->addChild(theme_home_normal, 3);
	theme_home_normal->setScale(1.2f);
	theme_home_normal->addClickEventListener([&](Ref* ref)
	{
		Director* director = Director::getInstance();
		StartScene* StartScene = StartScene::create();
		director->replaceScene(StartScene);
	});


	return true;
}

