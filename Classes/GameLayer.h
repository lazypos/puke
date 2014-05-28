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
#include "CardSprite.h"
USING_NS_CC;

static inline bool  mysort (CCardSprite *a, CCardSprite *b){
    return a->getSeq() < b->getSeq();
}

class  CGameLayer : public CCLayer{
    int lastseq;
    CCSize  winSize;
    list<CCardSprite*> lstFront;
    list<CCardSprite*> perCards;
    
    CREATE_FUNC(CGameLayer)
    bool    init();
    void    initGame();
    void    reviewPlayer();
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    void onGreenClicked(CCObject* pSender);
    void onRedClicked(CCObject* pSender);
    
    void    update(float dt);
    void    mainPlayerSchedule(float dt);
    void    upPlayerSchedule(float dt);
    void    downlayerSchedule(float dt);
    
public:
    static CCScene* scene();
};


#endif
