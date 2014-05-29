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
    CCLabelBMFont* mainTime1 = CCLabelBMFont::create("30", "fontWhiteBrownLevel.fnt");
    mainTime1->setPosition(ccp(winSize.width-150, winSize.height/2+100));
    mainTime1->setVisible(false);
    this->addChild(mainTime1, 1, tagTime1);
    CCLabelBMFont* mainTime2 = CCLabelBMFont::create("30", "fontWhiteBrownLevel.fnt");
    mainTime2->setPosition(ccp(150, winSize.height/2+100));
    mainTime2->setVisible(false);
    this->addChild(mainTime2, 1, tagTime2);
    
    GameConfig::instance()->ganmeStatus = game_over;
    
    // 胜负信息
    CCLabelTTF *lebWin = CCLabelTTF::create("你赢了！", "font/Marker Felt.ttf", 100);
    lebWin->setPosition(ccp(winSize.width/2, winSize.height/2+300));
    lebWin->setVisible(false);
    this->addChild(lebWin, 100, tagWin);
    CCLabelTTF *lebLose = CCLabelTTF::create("你输了！", "font/Marker Felt.ttf", 100);
    lebLose->setPosition(ccp(winSize.width/2, winSize.height/2+300));
    lebLose->setVisible(false);
    this->addChild(lebLose, 100, tagLose);
    
    // 地主头像
    CCSprite *dz = CCSprite::create("game_list_role.png");
    dz->setVisible(false);
    this->addChild(dz, 1, tagDZ);
    // 关闭窗口
    CCMenuItemImage *closeitem = CCMenuItemImage::create("CloseSelected.png", "CloseSelected.png", this, menu_selector(CGameLayer::onClose));
    CCMenu *closeMenu = CCMenu::create();
    closeMenu->addChild(closeitem);
    closeMenu->setPosition(ccp(winSize.width-50, winSize.height-50));
    this->addChild(closeMenu, 20);
    
    //this->scheduleUpdate();
    //this->schedule(schedule_selector(CGameLayer::update), 0.1f);
    this->schedule(schedule_selector(CGameLayer::playerSchedule), 0.1f);
    
    setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    return true;
}

void    CGameLayer::initGame(){
    clear();
    perCards.clear();
    for (int i=0; i<3; i++) {
        CCLabelBMFont* lb = getLabelTime(i);
        lb->setVisible(false);
    }
    CCLabelTTF* lbwin = (CCLabelTTF*)(this->getChildByTag(tagWin));
    lbwin->setVisible(false);
    CCLabelTTF* lbLose = (CCLabelTTF*)(this->getChildByTag(tagLose));
    lbLose->setVisible(false);
    
    GameConfig::instance()->game_start();
    CCSprite *dz = (CCSprite*)(this->getChildByTag(tagDZ));
    if (GameConfig::instance()->activePlayer == 0){
        dz->setPosition(ccp(winSize.width-200, 250));
    }else if (GameConfig::instance()->activePlayer == 1){
        dz->setPosition(ccp(winSize.width-80, winSize.height/2+250));
    }else{
        dz->setPosition(ccp(80, winSize.height/2+250));
    }
    
    dz->setVisible(true);
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
        if (n == 0)
            p->setPosition(ccp(posbegin+i*45, 350));
        else if (n == 1)
            p->setPosition(ccp(winSize.width/2+200, winSize.height-200-i*50));
        else
            p->setPosition(ccp(winSize.width/2-200, winSize.height-200-i*50));
        i++;
        this->addChild(p, 2, p->getSeq());
    }

    if (n != 0) {
        CCLabelBMFont* lbCards;
        if (n == 1)
            lbCards = (CCLabelBMFont*)(this->getChildByTag(tagCards1));
        else
            lbCards = (CCLabelBMFont*)(this->getChildByTag(tagCards2));
        int cardsNum = GameConfig::instance()->vecPlayers[n].getCardsList().size();
        char buf[20];
        memset(buf, 0, 20);
        sprintf(buf, "%d", cardsNum);
        lbCards->setString(buf);
    }
}

bool CGameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if (GameConfig::instance()->ganmeStatus == game_over) {
        //GameConfig::instance()->ganmeStatus = game_ready;
        initGame();
        GameConfig::instance()->ganmeStatus = game_started;
        int playerSeq = GameConfig::instance()->activePlayer%3;
        GameConfig::instance()->vecPlayers[playerSeq].isActive = true;
        return true;
    }
    
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
    if (GameConfig::instance()->ganmeStatus != game_started) {
        return;
    }
    
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

void   CGameLayer::putCards(int n){
    list<CCardSprite*> lstSelected;
    GameConfig::instance()->vecPlayers[n].getSelectedCards(lstSelected);
    if (lstSelected.empty())
        return;
    
    if (!CardOprator::instance()->BiggerThanBefore(perCards, lstSelected))
        return;
    
    perCards = lstSelected;
    lastOutPlayer = n;
    // 先清理之前门前的牌
    for (list<CCardSprite*>::iterator iter = GameConfig::instance()->vecPlayers[n].lstFront.begin();
         iter != GameConfig::instance()->vecPlayers[n].lstFront.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    GameConfig::instance()->vecPlayers[n].lstFront = lstSelected;
    if (n == 0) {
        // 清理手牌
        list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[0].getCardsList();
        for (list<CCardSprite*>::iterator iter = lstCards.begin();
             iter != lstCards.end(); ++iter) {
            if ((*iter)) {
                this->removeChildByTag((*iter)->getSeq());
            }
        }
    }
    
    GameConfig::instance()->vecPlayers[n].deleteSelectedCards();
    reviewPlayer(n);
    if (n != 0) {
        clearSelected(n);
    }
    if (GameConfig::instance()->vecPlayers[n].getCardsList().size() <= 0) {
        GameConfig::instance()->vecPlayers[n].isOver = true;
        int rst = GameConfig::instance()->game_check();
        if (rst == WIN) {
            GameConfig::instance()->ganmeStatus = game_over;
            CCLabelTTF* lbwin = (CCLabelTTF*)(this->getChildByTag(tagWin));
            lbwin->setVisible(true);
        }else if (rst == LOSE){
            GameConfig::instance()->ganmeStatus = game_over;
            CCLabelTTF* lbLose = (CCLabelTTF*)(this->getChildByTag(tagLose));
            lbLose->setVisible(true);
        }
    }
    overDo(n);
}

void CGameLayer::onGreenClicked(CCObject* pSender){
    if (GameConfig::instance()->ganmeStatus != game_started
        || GameConfig::instance()->vecPlayers[0].isOver) {
        return;
    }
    
    if (GameConfig::instance()->activePlayer%3 != 0)
        return;
    
    putCards(0);
}

void CGameLayer::passCards(int n){
    if (perCards.empty())
        return;
    
    //reviewPlayer(n);
    overDo(n);
}

void  CGameLayer::overDo(int n){
    CCLabelBMFont* lbTime = getLabelTime(n);
    lbTime->setVisible(false);
    GameConfig::instance()->vecPlayers[n].isActive = false;
    GameConfig::instance()->activePlayer++;
    int playerSeq = GameConfig::instance()->activePlayer%3;
    GameConfig::instance()->vecPlayers[playerSeq].isActive = true;
    GameConfig::instance()->vecPlayers[playerSeq].time = 30;
    CCLabelBMFont* nextlbtime = getLabelTime(playerSeq);
    nextlbtime->setVisible(true);
    
    // 清理门前的牌
    for (list<CCardSprite*>::iterator iter = GameConfig::instance()->vecPlayers[playerSeq].lstFront.begin();
         iter != GameConfig::instance()->vecPlayers[playerSeq].lstFront.end(); ++iter) {
        if ((*iter)) {
            this->removeChildByTag((*iter)->getSeq());
        }
    }
    if (lastOutPlayer == playerSeq) {
        perCards.clear();
    }
}

void CGameLayer::onRedClicked(CCObject* pSender){
    if (GameConfig::instance()->ganmeStatus != game_started
        || GameConfig::instance()->vecPlayers[0].isOver) {
        return;
    }
    if (GameConfig::instance()->activePlayer%3 != 0)
        return;
    
    passCards(0);
}

void  CGameLayer::playerSchedule(float dt){
    if (GameConfig::instance()->ganmeStatus != game_started) {
        return;
    }
    int playerSeq = GameConfig::instance()->activePlayer%3;
    if (GameConfig::instance()->vecPlayers[playerSeq].isActive) {
        if (!GameConfig::instance()->vecPlayers[playerSeq].isOver) {
            GameConfig::instance()->vecPlayers[playerSeq].time -= dt;
            CCLabelBMFont* lbTime = getLabelTime(playerSeq);
            lbTime->setVisible(true);
            char buf[20];
            sprintf(buf, "%d", int(GameConfig::instance()->vecPlayers[playerSeq].time));
            lbTime->setString(buf);
            
            list<CCardSprite*> lstCards = GameConfig::instance()->vecPlayers[playerSeq].getCardsList();
            // 超时
            if (GameConfig::instance()->vecPlayers[playerSeq].time <= 0){
                if (perCards.empty()) { // 强制出牌
                    clearSelected(playerSeq);
                    CCardAI::putOneCard(lstCards);
                    putCards(playerSeq);
                    return;
                }else {
                    lbTime->setVisible(false);
                }
            }else{
                if (playerSeq != 0) {
                    if (GameConfig::instance()->vecPlayers[playerSeq].time > 29)
                        return;
                    clearSelected(playerSeq);
                    if (CCardAI::putBigger(perCards, lstCards))
                        putCards(playerSeq);
                    else
                        passCards(playerSeq);
                    return;
                }
                else
                    return;
            }
        }
    }
 
    overDo(playerSeq);
}

CCLabelBMFont* CGameLayer::getLabelTime(int n){
    CCLabelBMFont* lbTime;
    if (n == 0) {
        lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime0));
    }else if (n == 1) {
        lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime1));
    }else {
        lbTime = (CCLabelBMFont*)(this->getChildByTag(tagTime2));
    }
    return lbTime;
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

void    CGameLayer::clear(){
    for (int i=0; i<54; i++) {
        CCNode* node =  this->getChildByTag(i);
        if (node) {
            this->removeChildByTag(i);
        }
    }
}

void   CGameLayer::onClose(){
    CCMessageBox("Exit game?", "Alert");
    exit(0);
}

