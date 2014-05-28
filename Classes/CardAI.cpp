//
//  CardAI.cpp
//  puke
//
//  Created by zcw on 14-5-28.
//
//

#include "CardAI.h"

void CCardAI::putOneCard(list<CCardSprite*>& lst){
    if (lst.size()) {
        lst.front()->setSelected(true);
    }
}

bool putBiggerSignal(int seq, list<CCardSprite*>& lst){
    int rval = CardOprator::instance()->getRealValue(seq);
    for (list<CCardSprite*>::iterator iter = lst.begin();
         iter != lst.end(); ++iter) {
        if (CardOprator::instance()->getRealValue((*iter)->getSeq()) > rval) {
            (*iter)->setSelected(true);
            return true;
        }
    }
    return false;
}

bool putBiggerApair(int rval, list<CCardSprite*>& lst){
    int perValue = -1;
    CCardSprite *p;
    for (list<CCardSprite*>::iterator iter = lst.begin();
         iter != lst.end(); ++iter) {
        if (perValue < 0) {
            perValue = CardOprator::instance()->getRealValue((*iter)->getSeq());
            p = *iter;
        }else {
            int nowrval = CardOprator::instance()->getRealValue((*iter)->getSeq());
            if (nowrval == perValue && nowrval > rval) {
                (*iter)->setSelected(true);
                p->setSelected(true);
                return true;
            }
        }
    }
    return false;
}










