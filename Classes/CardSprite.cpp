//
//  CardSprite.cpp
//  puke
//
//  Created by zcw on 14-5-27.
//
//

#include "CardSprite.h"

CCardSprite::CCardSprite()
: cardSeq(-1), bSelected(false){
    
}

void    CCardSprite::setSeq(int seq){
    cardSeq = seq;
}

void    CCardSprite::setSelected(bool bStatus){
    bSelected = bStatus;
}

bool    CCardSprite::isSelected(){
    return bSelected;
}

int     CCardSprite::getSeq(){
    return cardSeq;
}
