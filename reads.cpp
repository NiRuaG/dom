#include "reads.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <deque>
#include <stack>

#include "parser.h"

namespace dominion {
    // helper function: 
    //   getline that excludes period '.' character at end of line
    auto read_line(std::istream& f, std::string& s) -> decltype(std::getline(f, s)) {
        auto& ret = std::getline(f, s);
        if (!s.empty() && s.back() == '.')
            s.pop_back();
        return ret;
    }

    gameReader::gameReader(decltype(istrm_) is, decltype(game_) g)
        : istrm_(is), game_(g)
    {}

    void gameReader::read_game()
    {
        while (istrm_.good())
            read_turnblock();
       
        return;
    }

    void gameReader::read_turnblock() {
        std::string headerline;
        read_line(istrm_, headerline);
        /* process 'header' lines separately
        "Turn" or "Game #0000000, "
        }*/
        
        while (istrm_.peek() != 10 && istrm_.good())
        {
            // action lines
            // buy lines
            // draw line
            std::string s;
            read_line(istrm_, s);
            auto turnparse = parser::parse_turnline(s);
            

            auto& p = game_.players_by_name[turnparse.playerID];
            if (turnparse.verb == verb_tokens::Starts) {
                for (auto const&c : turnparse.cards)
                    p.cards_in_deck[c.second] = c.first;
            }
            if (turnparse.verb == verb_tokens::Buy || turnparse.verb == verb_tokens::Gain) {
                for (auto const&c : turnparse.cards)
                    p.cards_in_deck[c.second] += c.first;
            }
            if (turnparse.verb == verb_tokens::Trash) {
                for (auto const&c : turnparse.cards)
                    p.cards_in_deck[c.second] -= c.first;
            }
        }
        istrm_.get();

        return;
    }   
} // namespace dominion


