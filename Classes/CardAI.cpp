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

bool CCardAI::putBiggerSignal(int seq, list<CCardSprite*>& lst){
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

bool CCardAI::putBiggerApair(int rval, list<CCardSprite*>& lst){
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

bool CCardAI::putBiggerstraight(int val, int len, list<CCardSprite*>& lst){
    if (len < 14 && val < 13) {
        int minval = val - len + 1;
        list<CCardSprite*> lsttmp;
        for (list<CCardSprite*>::iterator iter = lst.begin();
             iter != lst.end(); ++iter) {
            for (list<CCardSprite*>::iterator iter = lst.begin();
                 iter != lst.end(); ++iter) {
                if (CardOprator::instance()->getRealValue((*iter)->getSeq()) > minval) {
                    lsttmp.push_back(*iter);
                }
            }
        }
        if (lsttmp.size() >= len) {
            
        }
    }
    return false;
}












