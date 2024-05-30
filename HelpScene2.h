#ifndef HelpScene2_h
#define HelpScene2_h

#include "cocos2d.h"
using namespace cocos2d;

class HelpScene2 : public Scene
{
public:
	static HelpScene2* create();
	bool init() override;
	static int a;
	const int MAX = 18;
};

#endif