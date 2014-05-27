//
//  Player.cpp
//  puke
//
//  Created by zcw on 14-5-27.
//
//

#include "Player.h"
#include "CardOprator.h"
#include "ResourceManager.h"

void    CPlayer::start(int num){
    clear();
    
    vector<int> cards;
    CardOprator::instance()->getCard(num, cards);
    for (vector<int>::iterator iter = cards.begin(); iter != cards.end(); ++iter) {
        CCardSprite *card = ResourceManager::instance()->get_card(*iter);
        lstCards.push_back(card);
    }

}

void    CPlayer::clear(){
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        CCardSprite *p = *iter;
        if (p) {
            delete p;
        }
    }
    lstCards.clear();
}

list<CCardSprite*>& CPlayer::getCardsList(){
    return lstCards;
}

