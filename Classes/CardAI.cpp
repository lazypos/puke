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

bool CCardAI::findStraightFrom(int minVal, int len, list<CCardSprite*>& lst){
    // 不算A
    list<CCardSprite*> shouldSelect;
    int tmp = minVal;
    int tmplen = 0;
    for (list<CCardSprite*>::iterator iter = lst.begin();
         iter != lst.end(); ++iter){
        if ((*iter)->getSeq()/4 == tmp) {
            shouldSelect.push_back(*iter);
            tmp++;
            tmplen++;
            if (tmplen == len) // 找到
                break;
        }
    }
    if (tmplen == len) {
        for (list<CCardSprite*>::iterator iter = shouldSelect.begin();
             iter != shouldSelect.end(); ++iter) {
            (*iter)->setSelected(true);
        }
        return true;
    }
    return false;
}

bool CCardAI::putBiggerstraight(int val, int len, list<CCardSprite*>& lst){
    if (len < 14 && val < 13) {
        int minval = val - len + 2;
        list<CCardSprite*> lsttmp;
        for (list<CCardSprite*>::iterator iter = lst.begin();
             iter != lst.end(); ++iter) {
            int seq = (*iter)->getSeq();
            if (CardOprator::instance()->getRealValue(seq) > minval) {
                if (seq/4==1 && minval != 0)
                    continue;
                if (IS_KING(seq))
                    continue;
                
                lsttmp.push_back(*iter);
            }
        }
        if (lsttmp.size() >= len) {
            // 不算a
            for (int i=minval; i<minval+12-val; i++) {
                if (findStraightFrom(i, len, lsttmp))
                    return true;
            }
            // suan a
            if (lsttmp.front()->getSeq()/4 == 0) {
                list<CCardSprite*> shouldSelect;
                int tmp = 14-len;
                for (list<CCardSprite*>::iterator iter = lsttmp.begin();
                     iter != lsttmp.end(); ++iter){
                    if ((*iter)->getSeq()/4 == tmp) {
                        shouldSelect.push_back(*iter);
                        tmp++;
                        if (tmp == 13)
                            break;
                    }
                }
                if (tmp == 13) {
                    lsttmp.front()->setSelected(true);
                    for (list<CCardSprite*>::iterator iter = shouldSelect.begin();
                         iter != shouldSelect.end(); ++iter) {
                        (*iter)->setSelected(true);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool CCardAI::putBigger(list<CCardSprite*>& lstPer, list<CCardSprite*>& lstNow){
    if (lstPer.empty()) {
        for (int i = 8; i<3; i--) {
            if (putBiggerstraight(2, i, lstNow)) {
                return true;
            }
        }
        if (!putBiggerstraight(2, 3, lstNow)
            && !putBiggerApair(2, lstNow)) {
            putOneCard(lstNow);
        }
        
        return true;
    }
    
    cardtype ct = CardOprator::instance()->getCardsType(lstPer);
    
    bool canput = false;
    if (lstPer.size() == 1) {
        canput = putBiggerSignal(lstPer.front()->getSeq(), lstNow);
    }
    
    if (ct == apair) {
        int seq = lstPer.front()->getSeq();
        int rval = CardOprator::instance()->getRealValue(seq);
        canput = putBiggerApair(rval, lstNow);
    }else if (ct == straight){
        int val = CardOprator::instance()->straightVal(lstPer);
        canput = putBiggerstraight(val, lstPer.size(), lstNow);
    }
    
    return canput;
}













