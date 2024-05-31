#ifndef GameEnd_h
#define GameEnd_h

#include "cocos2d.h"
using namespace cocos2d;

class GameEnd : public Scene
{
public:
	CREATE_FUNC(GameEnd);
	bool init() override;
	void SetWave(int SWaveNumber);
	void SetMapIndex(int index);
private:

};

#endif