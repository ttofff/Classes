#ifndef Boss_h
#define Boss_h

#include "cocos2d.h"
using namespace cocos2d;




class Boss : public Scene
{
public:
	static Boss* create();		
	bool init() override;		
	static int smallcheck;		//�ؿ���
	const int MAX = 7;			//���ؿ���
private:
	
};

#endif