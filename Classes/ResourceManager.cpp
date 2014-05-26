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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "fangpian");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(44,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "meihua");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(88,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "hongtao");
    flowerframe = CCSpriteFrame::create("game_list_poker_flower.png", CCRect(132,0,44,42));
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(flowerframe, "heitao");
    
    // init number
    CCSpriteFrame* numframe;
    char buf[32] = {0};
    for (int i=0; i<13; i++) {
        memset(buf, 0, 32);
        sprintf(buf, "rednum%2d", i+1);
        numframe = CCSpriteFrame::create("game_list_poker_num.png", CCRect(i*39,39,39,39));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(numframe, buf);
        memset(buf, 0, 32);
        sprintf(buf, "blacknum%2d", i+1);
        numframe = CCSpriteFrame::create("game_list_poker_num.png", CCRect(i*39,0,39,39));
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(numframe, buf);
    }
}