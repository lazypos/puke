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
using namespace std;

#define IS_REDTEN(seq) (seq==9||seq==35)
#define IS_RPTHREE(seq) (seq==28)

typedef struct cardinfo{
    int seq;    // 0-53
    int val;    // 1-15 14/15 king
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
    void        getCard(int seq, vector<int>& vecCards);
};

typedef  mysigleton<CCardOperator>    CardOprator;

#endif
