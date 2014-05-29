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
		player.sorcer = getSorcer(i);
        if (i == 0)
            player.isMainPlayer = true;
        vecPlayers.push_back(player);
    }
}

void        CGameConfig::game_start(){
    CardOprator::instance()->shuffle();
    
    isDouble = false;
    baseSorcer =  20;

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
	int rst = CONTINUE;
    if (vecPlayers[0].isking) {
        if (vecPlayers[0].isOver){
            if (vecPlayers[1].isOver || vecPlayers[2].isOver)
				rst = HE;
			else{
				vecPlayers[0].sorcer += 2*baseSorcer;
				vecPlayers[1].sorcer -= baseSorcer;
				vecPlayers[2].sorcer -= baseSorcer;
				rst = WIN;
			}
        }
        if (vecPlayers[1].isOver && vecPlayers[2].isOver) {
			vecPlayers[0].sorcer -= 2*baseSorcer;
			vecPlayers[1].sorcer += baseSorcer;
			vecPlayers[2].sorcer += baseSorcer;
            rst = LOSE;
        }
    }
    
    if (vecPlayers[1].isking){
        if (vecPlayers[1].isOver){
			if (vecPlayers[0].isOver || vecPlayers[2].isOver)
				rst = HE;
			else{
				vecPlayers[0].sorcer -= baseSorcer;
				vecPlayers[1].sorcer += 2*baseSorcer;
				vecPlayers[2].sorcer -= baseSorcer;
				rst = LOSE;
			}
        }
        if (vecPlayers[0].isOver && vecPlayers[2].isOver) {
			vecPlayers[0].sorcer += baseSorcer;
			vecPlayers[1].sorcer -= 2*baseSorcer;
			vecPlayers[2].sorcer += baseSorcer;
            rst = WIN;
        }
    }
    
    if (vecPlayers[2].isking){
        if (vecPlayers[2].isOver){
			if (vecPlayers[0].isOver || vecPlayers[1].isOver)
				rst = HE;
			else{
				vecPlayers[0].sorcer -= baseSorcer;
				vecPlayers[1].sorcer -= baseSorcer;
				vecPlayers[2].sorcer += 2*baseSorcer;
				rst = LOSE;
			}
        }
        if (vecPlayers[0].isOver && vecPlayers[1].isOver) {
			vecPlayers[0].sorcer += baseSorcer;
			vecPlayers[1].sorcer += baseSorcer;
			vecPlayers[2].sorcer -= 2*baseSorcer;
            rst = WIN;
        }
    }
	for (int k=0; k<3; k++) {
        if (vecPlayers[k].sorcer <= 0) {
            vecPlayers[k].sorcer = 10000;
        }
		saveSorcer(k, vecPlayers[k].sorcer);
	}
    return rst;
}

void CGameConfig::saveSorcer(int n, int val)
{
	char buf[20] = {0};
	sprintf(buf, "re%01d.vd", n);
	FILE *fd = fopen(buf, "wb");
	if (fd){
		fwrite((char*)&val, 4, 1, fd);
		fclose(fd);
	}
}

int	CGameConfig::getSorcer(int n){
	int val = 10000;
	char buf[20] = {0};
	sprintf(buf, "re%01d.vd", n);
	FILE *fd = fopen(buf, "rb");
	if (fd){
		fread((char*)&val, 4, 1, fd);
		fclose(fd);
	}
	return val;
}





