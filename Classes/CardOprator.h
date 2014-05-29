//
//  CardOprator.h
//  puke
//
//  Created by zcw on 14-5-26.
//
//

#ifndef puke_CardOprator_h
#define puke_CardOprator_h
#include <vector>
#include <time.h>
#include "sigleton.h"
#include "CardSprite.h"
using namespace std;

#define IS_REDTEN(seq) (seq==36||seq==38)
#define IS_RPTHREE(seq) (seq==10)
#define IS_KING(seq)    (seq==52||seq==53)
#define IS_AOR2(seq)    ((seq/4)==0||(seq/4)==1)

typedef enum _cardtype{
    unknow = -1,
    singal,     // 单张
    apair,      // 对子
    straight,   // 顺子
    boom,       // 炸弹
    kingboom,   // 王炸
    tenboom,    // 10炸
}cardtype;

typedef struct cardinfo{
    int seq;    // 0-53
    int val;    // 1-14 14 king
    int rval;   // 比大小用 2-12 A:13 2:14 小王:15 大王:16 红十:17
    int color;  // 0-4
}CardInfo;

class CCardOperator {
    vector<CardInfo>    vecCardInfo;
    int                 cardArray[52];
    
public:
    static void randArray(int* arr, int len);
    static void sortArray(int* arr, int len);
    
    void        init();
    void        shuffle();
    bool        getCard(int seq, vector<int>& vecCards);
    // 获取rval
    int         getRealValue(int seq);
    
    int         isStraight();
    
    // 获取出牌的类型
    cardtype    getCardsType(list<CCardSprite*>& lstCards);
    // 出牌类型是否允许
    bool        TypeValid(cardtype perType, cardtype nowType);
    // 是否能大于之前出的牌
    bool        BiggerThanBefore(list<CCardSprite*>& perCards, list<CCardSprite*>& nowCards);
    // 获取rval最小的牌
    int         getLittestCardRval(list<CCardSprite*>& lstCards);
    // 顺子最小值
    int         straightVal(list<CCardSprite*>& lstCards);
    // 顺子比较大小
    bool        straightBiggerThanBefore(list<CCardSprite*>& perCards, list<CCardSprite*>& nowCards);
};

typedef  mysigleton<CCardOperator>    CardOprator;

#endif
