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

void  CPlayer::init(){
    time = 30;
    isActive = false;
    sorcer = 10000;
}

void    CPlayer::start(int num){
    clear();
    _num = num;
    
    vector<int> cards;
    CardOprator::instance()->getCard(num, cards);
    for (vector<int>::iterator iter = cards.begin(); iter != cards.end(); ++iter) {
        CCardSprite *card = ResourceManager::instance()->get_card(*iter);
        lstCards.push_back(card);
    }
}

void    CPlayer::clear(){
    CCardSprite *p;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        p = *iter;
        if (p) {
            delete p;
        }
    }
    lstCards.clear();
}

list<CCardSprite*>& CPlayer::getCardsList(){
    return lstCards;
}

void CPlayer::getSelectedCards(list<CCardSprite*>& lstSelected){
    CCardSprite *p;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        p = *iter;
        if (p->isSelected()) {
            lstSelected.push_back(p);
        }
    }
}

void CPlayer::deleteSelectedCards(){
    CCardSprite *p;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end();) {
        p = *iter;
        if (p->isSelected()) {
            iter = lstCards.erase(iter);
            if (iter == lstCards.end()) {
                break;
            }
        }
        else
            iter++;
    }
}





