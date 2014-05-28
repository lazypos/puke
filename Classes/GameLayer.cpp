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
#include "GameConfig.h"
#include "Global.h"
#include "CardAI.h"

CCScene* CGameLayer::scene(){
    CCScene *pScene = CCScene::create();
    CGameLayer *pGameLayer = CGameLayer::create();
    pScene->addChild(pGameLayer);
    return pScene;
}

bool    CGameLayer::init(){
    ResourceManager::instance()->init();
    GameConfig::instance()->init();
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
    
    // 主玩家信息
    CCSprite *sorcerPic = CCSprite::create("game_icon_treasure.png");
    sorcerPic->setPosition(ccp(winSize.width/2-100, 25));
    this->addChild(sorcerPic);
    int sorcer = GameConfig::instance()->vecPlayers[0].getSorcer();
    char buf[20];
    memset(buf, 0, 20);
    sprintf(buf, "%d", sorcer);
    CCLabelBMFont* sorcerLabel = CCLabelBMFont::create(buf, "fontGreen.fnt");
    sorcerLabel->setPosition(ccp(winSize.width/2, 25));
    this->addChild(sorcerLabel, 1, tagSorcer0);
    
    CCLabelTTF *lebname = CCLabelTTF::create("大狗哥", "font/Marker Felt.ttf", 35);
    lebname->setPosition(ccp(winSize.width/2+200, 25));
    this->addChild(lebname, 1, tagName0);
    
    // 其余玩家1信息
    CCSprite *sorcerPic1 = CCSprite::create("game_icon_treasure.png");
    sorcerPic1->setPosition(ccp(winSize.width-200, winSize.height/2+200));
    this->addChild(sorcerPic1);
    sorcer = GameConfig::instance()->vecPlayers[2].getSorcer();
    memset(buf, 0, 20);
    sprintf(buf, "%d", sorcer);
    CCLabelBMFont* sorcerLabel1 = CCLabelBMFont::create(buf, "fontGreen.fnt");
    sorcerLabel1->setPosition(ccp(winSize.width-100, winSize.height/2+200));
    this->addChild(sorcerLabel1, 1, tagSorcer1);
    
    CCLabelTTF *lebname1 = CCLabelTTF::create("玩家1", "font/Marker Felt.ttf", 35);
    lebname1->setPosition(ccp(winSize.width-100, winSize.height/2+150));
    this->addChild(lebname1, 1, tagName1);
    CCLabelBMFont* cardsNum1 = CCLabelBMFont::create("0", "fontVipLevel.fnt");
    cardsNum1->setPosition(ccp(winSize.width-50, winSize.height/2+100));
    this->addChild(cardsNum1, 1, tagCards1);
    
    // 其余玩家2信息
    CCSprite *sorcerPic2 = CCSprite::create("game_icon_treasure.png");
    sorcerPic2->setPosition(ccp(50, winSize.height/2+200));
    this->addChild(sorcerPic2);
    sorcer = GameConfig::instance()->vecPlayers[2].getSorcer();
    memset(buf, 0, 20);
    sprintf(buf, "%d", sorcer);
    CCLabelBMFont* sorcerLabel2 = CCLabelBMFont::create(buf, "fontGreen.fnt");
    sorcerLabel2->setPosition(ccp(150, winSize.height/2+200));
    this->addChild(sorcerLabel2, 1, tagSorcer2);
    
    CCLabelTTF *lebname2 = CCLabelTTF::create("玩家2", "font/Marker Felt.ttf", 35);
    lebname2->setPosition(ccp(100, winSize.height/2+150));
    this->addChild(lebname2, 1, tagName2);
    CCLabelBMFont* cardsNum2 = CCLabelBMFont::create("0", "fontVipLevel.fnt");
    cardsNum2->setPosition(ccp(50, winSize.height/2+100));
    this->addChild(cardsNum2, 1, tagCards2);

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
    
    // 倒计时菜单
    CCLabelBMFont* mainTime = CCLabelBMFont::create("30", "fontWhiteBrownLevel.fnt");
    mainTime->setPosition(ccp(winSize.width/2+250, 250));
    mainTime->setVisible(false);
    this->addChild(mainTime, 1, tagTime0);
    
    GameConfig::instance()->ganmeStatus = game_ready;
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(CGameLayer::playerSchedule), 0.1f);
    
    setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    return true;
}

void    CGameLayer::initGame(){
    GameConfig::instance()->game_start();
    for (int i=0; i<3; i++)
        reviewPlayer(i);
}

void    CGameLayer::reviewPlayer(int n){
    list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[n].getCardsList();
    
    int len, posbegin, i;
    CCardSprite *p;
    if (n == 0) {
        len = 120 + (lstCards.size()-1)*50;
        posbegin = (winSize.width-len)/2 + 60;
        
        i = 0;
        for (list<CCardSprite*>::iterator iter = lstCards.begin();
             iter != lstCards.end(); ++iter) {
            p = *iter;
            p->setPosition(ccp(posbegin+i*50, 120));
            i++;
            this->addChild(p, 2, p->getSeq());
        }
    }
    
    // 门前的牌
    len = 120 + (GameConfig::instance()->vecPlayers[n].lstFront.size()-1)*50;
    posbegin = (winSize.width-len)/2 + 60;
    i = 0;
    for (list<CCardSprite*>::iterator iter = GameConfig::instance()->vecPlayers[n].lstFront.begin();
         iter != GameConfig::instance()->vecPlayers[n].lstFront.end(); ++iter) {
        p = *iter;
        p->setPosition(ccp(posbegin+i*45, 350));
        i++;
        this->addChild(p, 2, p->getSeq());
    }

}

bool CGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint p = pTouch->getLocation();
    
    list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[0].getCardsList();
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
    list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[0].getCardsList();
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
    if (GameConfig::instance()->activePlayer%3 != 0)
        return;
    
    list<CCardSprite*> lstSelected;
    GameConfig::instance()->vecPlayers[0].getSelectedCards(lstSelected);
    if (lstSelected.empty())
        return
    
    lstSelected.sort(mysort);
    
    if (!CardOprator::instance()->BiggerThanBefore(perCards, lstSelected))
        return;
    
    perCards = lstSelected;
    // 先清理之前门前的牌
    for (list<CCardSprite*>::iterator iter = GameConfig::instance()->vecPlayers[0].lstFront.begin();
         iter != GameConfig::instance()->vecPlayers[0].lstFront.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    // 再清理手牌
    GameConfig::instance()->vecPlayers[0].lstFront = lstSelected;
    list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[0].getCardsList();
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    
    GameConfig::instance()->vecPlayers[0].deleteSelectedCards();
    reviewPlayer(0);
    
    CCLabelBMFont* lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime0));
    GameConfig::instance()->vecPlayers[0].isActive = false;
    GameConfig::instance()->activePlayer++;
    lbTime->setVisible(false);
}

void CGameLayer::onRedClicked(CCObject* pSender){
    if (GameConfig::instance()->activePlayer%3 != 0)
        return;
    
    if (perCards.empty())
        return;
    
    // 清理门前的牌
    for (list<CCardSprite*>::iterator iter = GameConfig::instance()->vecPlayers[0].lstFront.begin();
         iter != GameConfig::instance()->vecPlayers[0].lstFront.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    
    CCLabelBMFont* lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime0));
    GameConfig::instance()->vecPlayers[0].isActive = false;
    GameConfig::instance()->activePlayer++;
    lbTime->setVisible(false);
}

void    CGameLayer::reviewOther(){
    int cardsNum = GameConfig::instance()->vecPlayers[1].getCardsList().size();
    CCLabelBMFont* lbCards = (CCLabelBMFont*)(this->getChildByTag(tagCards1));
    char buf[20];
    memset(buf, 0, 20);
    sprintf(buf, "%d", cardsNum);
    lbCards->setString(buf);
    
    cardsNum = GameConfig::instance()->vecPlayers[2].getCardsList().size();
    lbCards = (CCLabelBMFont*)(this->getChildByTag(tagCards2));
    memset(buf, 0, 20);
    sprintf(buf, "%d", cardsNum);
    lbCards->setString(buf);
}


void CGameLayer::update(float dt){
    if (GameConfig::instance()->ganmeStatus == game_ready) {
        initGame();
        reviewOther();
        GameConfig::instance()->ganmeStatus = game_started;
    }
    
    if (GameConfig::instance()->ganmeStatus == game_started) {
        int playerSeq = GameConfig::instance()->activePlayer%3;
        GameConfig::instance()->vecPlayers[playerSeq].isActive = true;
        if (playerSeq == 0) {
            CCLabelBMFont* lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime0));
            lbTime->setVisible(true);
        }
    }
}

void  CGameLayer::playerSchedule(float dt){
    int playerSeq = GameConfig::instance()->activePlayer%3;
    if (playerSeq == 0) {
        if (GameConfig::instance()->vecPlayers[0].isActive) {
            GameConfig::instance()->vecPlayers[0].time -= dt;
            CCLabelBMFont* lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime0));
            char buf[20];
            sprintf(buf, "%d", int(GameConfig::instance()->vecPlayers[0].time));
            lbTime->setString(buf);
            if (GameConfig::instance()->vecPlayers[0].time <= 0) {
                if (perCards.empty()) {
                    clearSelected(0);
                    list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[0].getCardsList();
                    CCardAI::putOneCard(lstCards);
                    onGreenClicked(NULL);
                    return;
                }
                else{
                    GameConfig::instance()->vecPlayers[0].isActive = false;
                    GameConfig::instance()->activePlayer++;
                    lbTime->setVisible(false);
                }
            }
        }
    }else if (playerSeq == 1) {
        reviewPlayer(1);
    }else {
        reviewPlayer(2);
    }
}

void CGameLayer::clearSelected(int n){
    list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[n].getCardsList();
    CCardSprite *p;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        p = *iter;
        if (p->isSelected()) {
            p->setSelected(false);
            if (n == 0)
                p->setPosition(ccp(p->getPositionX(), p->getPositionY()-30));
        }
    }
}

