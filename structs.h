#pragma once
#include <map>
#include "consts.h"

struct player_struct {
    unsigned int num_turns = 0;
    typedef std::map<dominion::card_tokens, unsigned short> map_str_card_amt;
    map_str_card_amt cards_in_deck;
};

struct game_struct {
    unsigned int game_number = -1;
    typedef std::map<std::string, player_struct> map_str_players;
    map_str_players players_by_name;
};
