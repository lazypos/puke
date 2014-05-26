//
//  ResourceManager.cpp
//  puke
//
//  Created by zcw on 14-5-25.
//
//

#include "ResourceManager.h"

CResourceManager::CResourceManager(){
    
}

void CResourceManager::init(){
    // init flower
    CCSpriteFrame* flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(0,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower0");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(44,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower1");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(88,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower2");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(132,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower3");
    
    // init number
    CCSpriteFrame* numframe;
    char buf[32] = {0};
    for (int i=0; i<13; i++) {
        memset(buf, 0, 32);
        sprintf(buf, "rednum%02d", i);
        numframe = CCSpriteFrame::create("game_list_poker_num.png", CCRect(i*NUM_SIZE,NUM_SIZE,NUM_SIZE,NUM_SIZE));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(numframe, buf);
        memset(buf, 0, 32);
        sprintf(buf, "blacknum%02d", i);
        numframe = CCSpriteFrame::create("game_list_poker_num.png", CCRect(i*NUM_SIZE,0,NUM_SIZE,NUM_SIZE));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(numframe, buf);
    }
    
    // init surface
    CCSpriteFrame* puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(0,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "front");
    puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(98,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "redking");
    puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(196,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "blackking");
    puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(294,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "back");
    
}

CCSprite* CResourceManager::get_card(int seq){
    CCSprite *card = NULL;
    if (seq == 52) {
         card = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("redking"));
    }else if (seq == 53) {
        card = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackking"));
    }else {
        card = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("front"));
        CCSize cardsize = card->getContentSize();
        char buf[32] = {0};
        int flowerNum = seq/13;
        int valueNum = seq%13;
        CCSprite * num = NULL;
        if (flowerNum == 0 || flowerNum == 2) {
            sprintf(buf, "rednum%02d", valueNum);
        }else {
            sprintf(buf, "blacknum%02d", valueNum);
        }
        num = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
        num->setPosition(ccp(NUM_SIZE/2+10,cardsize.height-NUM_SIZE/2-10));
        card->addChild(num);
        
        memset(buf, 0, 32);
        sprintf(buf, "flower%d", flowerNum);
        CCSprite *color = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
        color->setPosition(ccp(cardsize.width/2, cardsize.height/2));
        card->addChild(color);
    }
    return card;
}






