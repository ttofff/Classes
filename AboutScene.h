#ifndef AboutScene_h
#define AboutScene_h

#include "cocos2d.h"
using namespace cocos2d;

class AboutScene : public Scene
{
public:
	CREATE_FUNC(AboutScene);
	bool init() override;
	static int n;

	const int Max = 4;
};

#endif