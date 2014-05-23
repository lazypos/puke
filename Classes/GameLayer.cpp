//
//  GameLayer.cpp
//  puke
//
//  Created by zcw on 14-5-23.
//
//

#include "GameLayer.h"

CCScene* CGameLayer::scene(){
    CCScene *pScene = CCScene::create();
    CGameLayer *pGameLayer = CGameLayer::create();
    pScene->addChild(pGameLayer);
    return pScene;
}

bool    CGameLayer::init(){
    CCSprite *puke = CCSprite::create("game_list_poker_flower.png");
    puke->setPosition(ccp(300, 300));
    this->addChild(puke);
    return true;
}