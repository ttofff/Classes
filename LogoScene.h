#ifndef LogoScene_h
#define LogoScene_h

#include "cocos2d.h"
using namespace cocos2d;

class LogoScene : public Scene
{
public:
    static LogoScene* create();
    bool init() override;
};

#endif
