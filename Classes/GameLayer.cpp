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

CCScene* CGameLayer::scene(){
    CCScene *pScene = CCScene::create();
    CGameLayer *pGameLayer = CGameLayer::create();
    pScene->addChild(pGameLayer);
    return pScene;
}

bool    CGameLayer::init(){
    ResourceManager::instance()->init();
    CardOprator::instance()->init();
    
    CCSprite * bg = CCSprite::create("game_bg_day.jpg");
    CCSize  winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize  bgSize = bg->getContentSize();
    bg->setScaleX(winSize.width/bgSize.width);
    bg->setScaleY(winSize.height/bgSize.height);
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(bg, -1);
    
    CardOprator::instance()->shuffle();
    vector<int> player;
    CardOprator::instance()->getCard(1, player);
    int pos = 0;
    for (vector<int>::iterator iter = player.begin(); iter != player.end(); ++iter,++pos) {
        CCSprite *card = ResourceManager::instance()->get_card(*iter);
        card->setPosition(ccp(100+pos*50, 100));
        this->addChild(card);
    }
    
    return true;
}







