//
//  GameLayer.h
//  puke
//
//  Created by zcw on 14-5-23.
//
//

#ifndef puke_GameLayer_h
#define puke_GameLayer_h
#include "cocos2d.h"
USING_NS_CC;

class  CGameLayer : public CCLayer{
    
    
    CREATE_FUNC(CGameLayer)
    bool    init();
    
public:
    static CCScene* scene();
};


#endif
