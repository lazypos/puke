//
//  GameLayer.cpp
//  puke
//
//  Created by zcw on 14-5-23.
//
//

#include "GameLayer.h"
#include "ResourceManager.h"
#include "CardOprator.h"
#include "CardSprite.h"

CCScene* CGameLayer::scene(){
    CCScene *pScene = CCScene::create();
    CGameLayer *pGameLayer = CGameLayer::create();
    pScene->addChild(pGameLayer);
    return pScene;
}

bool    CGameLayer::init(){
    ResourceManager::instance()->init();
    CardOprator::instance()->init();
    
    lastseq = -1;
    
    CCSprite * bg = CCSprite::create("game_bg_day.jpg");
    CCSize  winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize  bgSize = bg->getContentSize();
    bg->setScaleX(winSize.width/bgSize.width);
    bg->setScaleY(winSize.height/bgSize.height);
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(bg, -1);
    
    CardOprator::instance()->shuffle();
    initMainPlayer(1);
    
    setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    return true;
}

void    CGameLayer::initMainPlayer(int num){
    mainPlayer.start(num);
    list<CCardSprite*> lstCards = mainPlayer.getCardsList();
    
    CCardSprite *p;
    int pos = 0;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        p = *iter;
        p->setPosition(ccp(100+pos*50, 150));
        pos++;
        this->addChild(p);
    }
}

bool CGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint p = pTouch->getLocation();
    
    list<CCardSprite*> lstCards = mainPlayer.getCardsList();
    CCardSprite *card;
    for (list<CCardSprite*>::reverse_iterator riter = lstCards.rbegin();
         riter != lstCards.rend(); ++riter) {
        card = *riter;
        CCRect recv = card->boundingBox();
        if (recv.containsPoint(p)) {
            lastseq =card->getSeq();
            if (card->isSelected()) {
                card->setSelected(false);
                card->setPosition(ccp(card->getPositionX(), card->getPositionY()-30));
            } else {
                card->setSelected(true);
                card->setPosition(ccp(card->getPositionX(), card->getPositionY()+30));
            }
            break;
        }
    }
    return true;
}

void CGameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint p = pTouch->getLocation();
    list<CCardSprite*> lstCards = mainPlayer.getCardsList();
    CCardSprite *card;
    for (list<CCardSprite*>::reverse_iterator riter = lstCards.rbegin();
         riter != lstCards.rend(); ++riter) {
        card = *riter;
        CCRect recv = card->boundingBox();
        if (recv.containsPoint(p)) {
            if (lastseq == card->getSeq())
                break;
            
            lastseq = card->getSeq();
            if (card->isSelected()) {
                card->setSelected(false);
                card->setPosition(ccp(card->getPositionX(), card->getPositionY()-30));
            } else {
                card->setSelected(true);
                card->setPosition(ccp(card->getPositionX(), card->getPositionY()+30));
            }
            break;
        }
    }
}





