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
    
    list<CCardSprite*> perCards;
    int                lastOutPlayer;
    
    CREATE_FUNC(CGameLayer)
    bool    init();
    void    initGame();
    void    reviewPlayer(int n);
    
    void    putCards(int n);
    void    passCards(int n);
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    void onGreenClicked(CCObject* pSender);
    void onRedClicked(CCObject* pSender);
    
    void    update(float dt);
    void    playerSchedule(float dt);
    
    void    clearSelected(int n);
    
    CCLabelBMFont* getLabelTime(int n);
    void    overDo(int n);
public:
    static CCScene* scene();
};


#endif
