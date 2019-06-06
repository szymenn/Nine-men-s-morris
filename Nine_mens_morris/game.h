#pragma once
#include "player.h"
#include "linked_list.h"
#include "game_base.h"

class game : public game_base{
	void play(player &player1, player &player2) override;
public:
	game();
	~game();
	
};