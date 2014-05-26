//
//  GameLayer.cpp
//  puke
//
//  Created by zcw on 14-5-23.
//
//

#include "GameLayer.h"
#include "ResourceManager.h"

CCScene* CGameLayer::scene(){
    CCScene *pScene = CCScene::create();
    CGameLayer *pGameLayer = CGameLayer::create();
    pScene->addChild(pGameLayer);
    return pScene;
}

bool    CGameLayer::init(){
    ResourceManager::instance()->init();
    
//    CCSprite *puke = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("heitao"));
//    puke->setPosition(ccp(300, 300));
//    this->addChild(puke);
    
//    CCSprite *sp;
//    char buf[32] = {0};
//    for (int i=0; i<13; i++) {
//        memset(buf, 0, 32);
//        sprintf(buf, "blacknum%02d", i+1);
//        sp = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
//        sp->setPosition(ccp(i*40, 200));
//        this->addChild(sp);
//    }
    
    
    
    for (int i=0; i<13; i++) {
        CCSprite *card = ResourceManager::instance()->get_card(i);
        card->setPosition(ccp(50+i*50, 400));
        this->addChild(card);
    }
    for (int i=13; i<26; i++) {
        CCSprite *card = ResourceManager::instance()->get_card(i);
        card->setPosition(ccp(50+(i-13)*50, 300));
        this->addChild(card);
    }
    for (int i=26; i<39; i++) {
        CCSprite *card = ResourceManager::instance()->get_card(i);
        card->setPosition(ccp(50+(i-26)*50, 200));
        this->addChild(card);
    }
    for (int i=39; i<54; i++) {
        CCSprite *card = ResourceManager::instance()->get_card(i);
        card->setPosition(ccp(50+(i-39)*50, 100));
        this->addChild(card);
    }
    return true;
}







