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
		card.color = i/13;
		if (i == 52) {
			card.val = 14;
		}else if (i == 53) {
			card.val = 15;
		}else {
			card.val = i%13+1;
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

void CCardOperator::getCard(int seq, vector<int>& vecCards){
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
    for (int i=begin; i<end; i++) {
        vecCards.push_back(cardArray[i]);
    }
}




