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

class CGameConfig {
public:
    vector<CPlayer> vecPlayers;
    
    void        init();
    
    int         gameMode;
    gameStatus  ganmeStatus;
    
    int         activePlayer;
    
    void        game_start();
};

typedef mysigleton<CGameConfig> GameConfig;
#endif
