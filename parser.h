#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "consts.h"

namespace dominion {
    namespace parser {
        using pair_card_num = std::pair<unsigned short, card const*>;
        
        struct struct_turnline {
            std::string playerID;
            dominion::verb_tokens verb;
            std::vector<pair_card_num> cards;
        };
        struct_turnline parse_turnline(std::string&);

        verb_tokens parse_verb(std::string&);
        unsigned short parse_card_num(std::string&);
        std::vector<pair_card_num> parse_cards(std::istream&);

        extern std::map<std::string, unsigned short> counts_;
    }
}