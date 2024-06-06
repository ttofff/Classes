#ifndef AdventureFirstScene_h
#define AdventureFirstScene_h

#include "cocos2d.h"
using namespace cocos2d;

class AdventureFirstScene : public Scene
{
public:
	static AdventureFirstScene* create(int i);
	bool init() override;
	static int smallcheck;
	static int bigcheck;
	const int MAX = 7;

	int blockSize;
	int monsterKind;
	
};

#endif