//
//  Player.h
//  puke
//
//  Created by zcw on 14-5-27.
//
//

#ifndef puke_Player_h
#define puke_Player_h
#include "CardSprite.h"
#include <list>
using namespace std;

class CPlayer{
    
    void    clear();
    
    list<CCardSprite*>      lstCards;
    
public:
    void    start(int num);
    list<CCardSprite*>& getCardsList();
};

#endif
