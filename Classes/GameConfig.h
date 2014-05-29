//
//  GameConfig.h
//  puke
//
//  Created by zcw on 14-5-28.
//
//

#ifndef puke_GameConfig_h
#define puke_GameConfig_h
#include "sigleton.h"
#include "Player.h"

typedef enum _gameStatus{
    game_wait, // 未全举手
    game_ready, // 全举手
    game_sendpuke, // 发牌中
    game_started, // 进行中
    game_over, // 游戏结束
}gameStatus;

#define WIN      1
#define LOSE     2
#define HE		3
#define CONTINUE     4

class CGameConfig {
public:
    vector<CPlayer> vecPlayers;
    
    int         gameMode;
    gameStatus  ganmeStatus;
    
    int         activePlayer;
    int         lastOutCards;
    bool        isDouble;
	int			baseSorcer;
    
    void        init();
    void        game_start();
    int         game_check();

	void		saveSorcer(int n, int val);
	int			getSorcer(int n);
};

typedef mysigleton<CGameConfig> GameConfig;
#endif
