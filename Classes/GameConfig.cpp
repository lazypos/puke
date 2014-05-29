//
//  GameConfig.cpp
//  puke
//
//  Created by zcw on 14-5-28.
//
//

#include "GameConfig.h"
#include "CardOprator.h"

void        CGameConfig::init(){
    vecPlayers.clear();
    for (int i=0; i<3; i++) {
        CPlayer player;
        player.init();
        if (i == 0)
            player.isMainPlayer = true;
        vecPlayers.push_back(player);
    }
}

void        CGameConfig::game_start(){
    CardOprator::instance()->shuffle();
    
    isDouble = false;
    
    srand(time(NULL));
    int n = rand()%3;
    lastOutCards = n;
    printf("restart game:%d\n", n);
    for (int i=0; i<3; i++) {
        if (vecPlayers[n++].start(i))
            activePlayer = n-1;
        n %= 3;
    }
    ganmeStatus = game_started;
}

int        CGameConfig::game_check(){
    if (vecPlayers[0].isking) {
        if (vecPlayers[0].isOver){
            return WIN;
        }
        if (vecPlayers[1].isOver && vecPlayers[2].isOver) {
            return LOSE;
        }
    }else if (vecPlayers[1].isking){
        if (vecPlayers[1].isOver){
            return LOSE;
        }
        if (vecPlayers[0].isOver && vecPlayers[2].isOver) {
            return WIN;
        }
    }else {
        if (vecPlayers[2].isOver){
            return LOSE;
        }
        if (vecPlayers[0].isOver && vecPlayers[1].isOver) {
            return WIN;
        }
    }
    return CONTINUE;
}







