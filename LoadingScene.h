#ifndef LoadingScene_h
#define LoadingScene_h

#include "cocos2d.h"
using namespace cocos2d;

class LoadingScene : public Scene
{
public:
	static LoadingScene* create(int i);
	bool init() override;

	int index;			//��ͼ�ؿ���

	void onScheduleCallBack(float dt);

	ProgressTimer* loadingBar;

	int blockSize; // ���ط����С

	void SetBlockSize(int size);
};

#endif