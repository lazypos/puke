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
    
    int                     sorcer;
    
public:
    float                   time;
    int                     _num;
    bool                    isActive; // 是否是该玩家出牌
    bool                    isMainPlayer;
    // 前一次出的牌
    list<CCardSprite*>      lstFront;
    
    void                init();
    bool                start(int num);
    list<CCardSprite*>& getCardsList();
    void                setSorcer(int n){sorcer = n;}
    int                 getSorcer(){return sorcer;}
    void                getSelectedCards(list<CCardSprite*>& lstSelected);
    void                deleteSelectedCards();
};

#endif
