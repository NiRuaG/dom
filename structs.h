#pragma once
#include <map>
#include "consts.h"

struct player_struct {
    unsigned int num_turns = 0;
    typedef std::map<dominion::card const*const, unsigned short> map_card_amt;
    map_card_amt cards_in_deck;
};

struct game_struct {
    unsigned int game_number = -1;
    typedef std::map<std::string, player_struct> map_str_players;
    map_str_players players_by_name;
};
