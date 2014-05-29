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
    // init 花色
    CCSpriteFrame* flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(0,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower0");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(44,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower1");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(88,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower2");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(132,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "flower3");
    
    // init 点数
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
    
    // init 背景
    CCSpriteFrame* puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(0,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "front");
    puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(99,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "redking");
    puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(197,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "blackking");
    puke = CCSpriteFrame::create("game_list_poker_surface.png", CCRect(296,0,98,138));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(puke, "back");
    
    CCSpriteFrame* button = CCSpriteFrame::create("game_bg_play_long_btn.png", CCRect(0,0,152,61));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(button, "redbutton");
    button = CCSpriteFrame::create("game_bg_play_long_btn.png", CCRect(152,0,152,61));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(button, "greenbutton");
    
}

// 根据卡牌序号得到卡牌精灵
CCardSprite* CResourceManager::get_card(int seq){
    CCardSprite *card = new CCardSprite;
    if (seq == 52) {
        card->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("blackking"));
    }else if (seq == 53) {
        card->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("redking"));
    }else {
        card->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("front"));
        CCSize cardsize = card->getContentSize();
        char buf[32] = {0};
        int flowerNum = seq%4;
        int valueNum = seq/4;
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
    card->setSelected(false);
    card->setSeq(seq);
    return card;
}




