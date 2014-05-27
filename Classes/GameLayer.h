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
#include "Player.h"
USING_NS_CC;

class  CGameLayer : public CCLayer{
    CPlayer mainPlayer;
    int lastseq;
    CCSize  winSize;
    
    CREATE_FUNC(CGameLayer)
    bool    init();
    void    initMainPlayer(int num);
    void    reviewPlayer();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    void onGreenClicked(CCObject* pSender);
    
public:
    static CCScene* scene();
};


#endif
