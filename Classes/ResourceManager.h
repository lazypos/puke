//
//  ResourceManager.h
//  puke
//
//  Created by zcw on 14-5-25.
//
//

#ifndef puke_ResourceManager_h
#define puke_ResourceManager_h
#include "sigleton.h"
#include "cocos2d.h"
#include "CardSprite.h"
USING_NS_CC;

#define NUM_SIZE    39

class CResourceManager {
    
    
public:
    CResourceManager();
    void    init();
    CCardSprite* get_card(int seq);
};

typedef mysigleton<CResourceManager> ResourceManager;

#endif
