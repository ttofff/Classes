#ifndef LoadingScene_h
#define LoadingScene_h

#include "cocos2d.h"
using namespace cocos2d;

class LoadingScene : public Scene
{
public:
	static LoadingScene* create(int i);
	bool init() override;

	int index;			//地图关卡数

	void onScheduleCallBack(float dt);

	ProgressTimer* loadingBar;

	int blockSize; // 像素方块大小

	void SetBlockSize(int size);
};

#endif