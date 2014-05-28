//
//  CardOprator.cpp
//  puke
//
//  Created by zcw on 14-5-27.
//
//

#include "CardOprator.h"

void CCardOperator::init(){
    for (int i=0,j=0; i<54; i++)
	{
		if (!IS_REDTEN(i))
			cardArray[j++] = i;
        
		CardInfo  card;
		memset(&card, 0, sizeof(CardInfo));
		card.seq = i;
		card.color = i%4;
		if (i == 52) {
			card.val = 14;
            card.rval = 15;
		}else if (i == 53) {
			card.val = 15;
            card.rval = 16;
        }else {
			card.val = i/4+1;
            card.rval = card.val;
		}
        
        if (i/4 == 0) {
			card.val = 1;
            card.rval = 13;
        }else if (i/4 == 1) {
			card.val = 2;
            card.rval = 14;
		}
        
        if (IS_REDTEN(i)) {
            card.rval = 17;
        }
		vecCardInfo.push_back(card);
	}
}

void CCardOperator::randArray(int* arr, int len){
    srand((unsigned int)time(NULL));
	int tmp = 0;
	for (int t=0; t<3; t++)
	{
		for (int i=0; i<len; i++){
			int n = rand()%len;
			tmp = arr[i];
			arr[i] = arr[n];
			arr[n] = tmp;
		}
	}
}

void CCardOperator::sortArray(int* arr, int len){
    int tmp;
	for (int i=0; i<len-1; i++)
	{
		for (int j=0; j<len-1-i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				tmp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void CCardOperator::shuffle(){
    randArray(cardArray, 52);
}

bool CCardOperator::getCard(int seq, vector<int>& vecCards){
    int begin, end;
    if (seq == 0) {
        begin = 0;
        end = 18;
    }else {
        begin = seq * 17 + 1;
        end = begin + 17;
    }
    sortArray(cardArray+begin, end-begin);
    vecCards.clear();
    bool    redThree = false;
    for (int i=begin; i<end; i++) {
        vecCards.push_back(cardArray[i]);
        if (IS_RPTHREE(cardArray[i])) {
            redThree = true;
        }
    }
    if (redThree) {
        vecCards.push_back(36);
        vecCards.push_back(38);
        return true;
    }
    return false;
}

cardtype CCardOperator::getCardsType(list<CCardSprite*>& lstCards){
    if (lstCards.size() <= 0)
        return unknow;
    
    vector<int> vecCards;
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        vecCards.push_back((*iter)->getSeq());
    }
    
    if (lstCards.size() == 1) {
        return singal;
    } else if (lstCards.size() == 2) {
        if (IS_KING(vecCards[0]) && IS_KING(vecCards[1])) {
            return kingboom;
        } else if (IS_REDTEN(vecCards[0]) && IS_REDTEN(vecCards[1])) {
            return tenboom;
        } else {
            if (vecCards[0]/4 == vecCards[1]/4) {
                return apair;
            }
        }
    } else if (lstCards.size() == 3) {
        if (IS_KING(vecCards[2]))
            return unknow;
        
        if (vecCards[0]/4 == vecCards[1]/4 &&
            vecCards[0]/4 == vecCards[2]/4 ) {
            return boom;
        } else {
            if (vecCards[0]/4 == 0 && vecCards[1]/4 == 11 && vecCards[2]/4 == 12) { // QKA
                return straight;
            } else {
                if (vecCards[0]/4 == vecCards[1]/4-1 && vecCards[0]/4 == vecCards[2]/4-2) {
                    return straight;
                }
            }
        }
    }else if (lstCards.size() == 4) {
        if (IS_KING(vecCards[2]))
            return unknow;

        if (vecCards[0]/4 == vecCards[1]/4 &&
            vecCards[0]/4 == vecCards[2]/4 &&
            vecCards[0]/4 == vecCards[3]/4) {
            return boom;
        }else {
            if (vecCards[1]/4 == 0 && vecCards[1]/4 == 10
                && vecCards[2]/4 == 11 && vecCards[3]/4 == 12) { // JQKA
                return straight;
            } else {
                if (vecCards[0]/4 == vecCards[1]/4-1
                    && vecCards[0]/4 == vecCards[2]/4-2
                    && vecCards[0]/4 == vecCards[3]/4-3) {
                    return straight;
                }
            }
        }
    }else {
        int len = vecCards.size();
        if (len < 15) {
            bool isstraight = true;
            for (int i=1; i<len-1; i++) {
                if (vecCards[i]/4 != vecCards[i+1]/4-1) {
                    isstraight = false;
                    break;
                }
            }
            // last
            if (isstraight) {
                if (vecCards[0]/4 == vecCards[1]/4-1) {
                    return straight;
                }else if (vecCards[0]/4 == 0 && vecCards[len-1]/4 == 12) {
                    return straight;
                }
            }
        }
    }
    return unknow;
}

bool CCardOperator::TypeValid(cardtype perType, cardtype nowType){
    if (nowType == unknow || perType == tenboom)
        return false;
    
    if (nowType == kingboom || nowType == tenboom || perType == unknow || perType == nowType)
        return true;
    
    if (nowType == boom && perType != tenboom)
        return true;
    
    return false;
}

int CCardOperator::getRealValue(int seq){
    return vecCardInfo[seq].rval;
}

bool CCardOperator::BiggerThanBefore(list<CCardSprite*>& perCards, list<CCardSprite*>& nowCards){
    cardtype perType = getCardsType(perCards);
    cardtype nowType = getCardsType(nowCards);
    
    if (!TypeValid(perType, nowType))
        return false;
    
    if (perType == unknow)
        return true;

    int perval = getLittestCardRval(perCards);
    int nowval = getLittestCardRval(nowCards);
    
    if (perType == boom) {
        if (nowval <= perval || perCards.size() > nowCards.size()) {
            return false;
        }
    } else {
        if (nowType != boom) {
            if (nowval <= perval || nowCards.size() != perCards.size())
                return false;
        }
    }
    
    return true;
}

int CCardOperator::getLittestCardRval(list<CCardSprite*>& lstCards){
    int seq = lstCards.front()->getSeq();
    int rval = vecCardInfo[seq].rval;
    
    for (list<CCardSprite*>::iterator iter = lstCards.begin();
         iter != lstCards.end(); ++iter) {
        seq = (*iter)->getSeq();
        if (vecCardInfo[seq].rval < rval) {
            rval = vecCardInfo[seq].rval;
        }
    }
    return rval;
}



