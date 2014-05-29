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
        if (vecPlayers[n].start(i))
            activePlayer = n;
        n = (n+1)%3;
    }
}

int        CGameConfig::game_check(){
    if (vecPlayers[0].isking) {
        if (vecPlayers[0].isOver){
            return WIN;
        }
        if (vecPlayers[1].isOver && vecPlayers[2].isOver) {
            return LOSE;
        }
    }
    
    if (vecPlayers[1].isking){
        if (vecPlayers[1].isOver){
            return LOSE;
        }
        if (vecPlayers[0].isOver && vecPlayers[2].isOver) {
            return WIN;
        }
    }
    
    if (vecPlayers[2].isking){
        if (vecPlayers[2].isOver){
            return LOSE;
        }
        if (vecPlayers[0].isOver && vecPlayers[1].isOver) {
            return WIN;
        }
    }
    return CONTINUE;
}







