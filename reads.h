#pragma once

#include <istream>
#include <vector>

#include "structs.h"

namespace dominion {
    void read_startofgame_playerstartcards(std::istream&&, game_struct::map_str_players&);
    void read_startofgame(std::istream&, game_struct&);
    verb_tokens parse_verb(std::istream&);
    unsigned short parse_card_num(std::string&);
    using pair_card_num = std::pair<unsigned short, card_tokens>;
    std::vector<pair_card_num> parse_cards(std::istream&);
    void parse_turnline_players_action(std::istream&, player_struct&);
    void read_restofgame(std::istream&, game_struct&);
}