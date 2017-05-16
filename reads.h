#pragma once

#include <istream>
#include "structs.h"

namespace dominion {
    void read_startofgame_playerstartcards(std::istream&&, game_struct::map_str_players&);
    void read_startofgame(std::istream&, game_struct&);
    tokens parse_verb(std::istream&);
    unsigned short parse_card_num(std::string&);
    std::map<tokens, unsigned short> parse_cards(std::istream&);
    void parse_turnline_players_action(std::istream&, player_struct&);
    void read_restofgame(std::istream&, game_struct&);
}