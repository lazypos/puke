//
//  CardAI.h
//  puke
//
//  Created by zcw on 14-5-28.
//
//

#ifndef puke_CardAI_h
#define puke_CardAI_h
#include "CardOprator.h"

class CCardAI {

    
public:
    static void putOneCard(list<CCardSprite*>& lst);
    static bool putBiggerSignal(int seq, list<CCardSprite*>& lst);
    static bool putBiggerApair(int rval, list<CCardSprite*>& lst);
};


#endif
