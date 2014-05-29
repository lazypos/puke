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
#include "GameConfig.h"

void  CPlayer::init(){
    sorcer = 10000;
}

bool    CPlayer::start(int num){
    clear();
    lstFront.clear();
    _num = num;
    
    bool bactive = false;
    isOver = false;
    time = 30;
    isWin = false;
    vector<int> cards;
    if(CardOprator::instance()->getCard(num, cards))
    {
        isking = true;
        bactive = true;
    }
    for (vector<int>::iterator iter = cards.begin(); iter != cards.end(); ++iter) {
        CCardSprite *card = ResourceManager::instance()->get_card(*iter);
        lstCards.push_back(card);
    }
    return bactive;
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




