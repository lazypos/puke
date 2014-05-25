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

class CResourceManager {
    void    init();
    
public:
    CResourceManager();
};

typedef sigleton<CResourceManager> ResourceManager;

#endif
