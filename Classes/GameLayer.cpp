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
    
    // 背景
    CCSprite * bg = CCSprite::create("game_bg_day.jpg");
    winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize  bgSize = bg->getContentSize();
    bg->setScaleX(winSize.width/bgSize.width);
    bg->setScaleY(winSize.height/bgSize.height);
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(bg, -1);
    
    CCSprite *sorcerPic = CCSprite::create("game_icon_treasure.png");
    sorcerPic->setPosition(ccp(winSize.width/2-100, 25));
    this->addChild(sorcerPic);
    CCLabelBMFont* sorcerLabel = CCLabelBMFont::create("000000", "fontGreen.fnt");
    sorcerLabel->setPosition(ccp(winSize.width/2, 25));
    this->addChild(sorcerLabel, 1, 100);

    // 出牌菜单
    CCSprite *redbutton = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("redbutton"));
    CCSprite *greenbutton = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("greenbutton"));

    CCMenuItemImage *redbuttonItem = CCMenuItemImage::create();
    redbuttonItem->initWithNormalSprite(redbutton, redbutton, redbutton, this, menu_selector(CGameLayer::onRedClicked));
    redbuttonItem->setPosition(ccp(-100, 0));
    CCMenuItemImage *greenbuttonItem = CCMenuItemImage::create();
    greenbuttonItem->initWithNormalSprite(greenbutton, greenbutton, greenbutton, this, menu_selector(CGameLayer::onGreenClicked));
    greenbuttonItem->setPosition(ccp(100, 0));
    CCMenu *pMenu = CCMenu::create();
    pMenu->alignItemsInColumns(2);
    pMenu->setPosition(ccp(winSize.width/2, 250));
    pMenu->addChild(redbuttonItem);
    pMenu->addChild(greenbuttonItem);
    this->addChild(pMenu);
    
    CardOprator::instance()->shuffle();
    initMainPlayer(1);
    
    setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    return true;
}

void    CGameLayer::initMainPlayer(int num){
    mainPlayer.start(num);
    reviewPlayer();
}

void    CGameLayer::reviewPlayer(){
    list<CCardSprite*> lstCards = mainPlayer.getCardsList();
    
    int len = 120 + (lstCards.size()-1)*50;
    int posbegin = (winSize.width-len)/2 + 60;
    
    CCardSprite *p;
    int i = 0;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        p = *iter;
        p->setPosition(ccp(posbegin+i*50, 120));
        i++;
        this->addChild(p, 2, p->getSeq());
    }
    
    // 门前的牌
    len = 120 + (lstFront.size()-1)*50;
    posbegin = (winSize.width-len)/2 + 60;
    i = 0;
    for (list<CCardSprite*>::iterator iter = lstFront.begin();
         iter != lstFront.end(); ++iter) {
        p = *iter;
        p->setPosition(ccp(posbegin+i*50, 350));
        i++;
        this->addChild(p, 2, p->getSeq());
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

void CGameLayer::onGreenClicked(CCObject* pSender){
    list<CCardSprite*> lstSelected;
    mainPlayer.getSelectedCards(lstSelected);
    lstSelected.sort(mysort);
    
    if (!CardOprator::instance()->BiggerThanBefore(perCards, lstSelected))
        return;
    
    perCards = lstSelected;
    // 先清理之前门前的牌
    for (list<CCardSprite*>::iterator iter = lstFront.begin();
         iter != lstFront.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    // 再清理手牌
    lstFront = lstSelected;
    list<CCardSprite*> lstCards = mainPlayer.getCardsList();
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    
    mainPlayer.deleteSelectedCards();
    reviewPlayer();
}

void CGameLayer::onRedClicked(CCObject* pSender){
    // 清理门前的牌
    for (list<CCardSprite*>::iterator iter = lstFront.begin();
         iter != lstFront.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
}


