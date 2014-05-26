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
USING_NS_CC;

class CResourceManager {
    
    
public:
    CResourceManager();
    void    init();
};

typedef sigleton<CResourceManager> ResourceManager;

#endif
