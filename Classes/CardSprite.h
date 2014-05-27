//
//  CardSprite.h
//  puke
//
//  Created by zcw on 14-5-27.
//
//

#ifndef puke_CardSprite_h
#define puke_CardSprite_h
#include "cocos2d.h"
USING_NS_CC;

class CCardSprite : public CCSprite {
    int     cardSeq;
    bool    bSelected;
    
public:
    CCardSprite();
    void    setSeq(int seq);
    int     getSeq();
    void    setSelected(bool bStatus);
    bool    isSelected();
};


#endif
