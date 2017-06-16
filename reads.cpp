#include "reads.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <deque>
#include <stack>
#include <algorithm>

#include "gInc.h"
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
        std::string s;
        // Game ###, un/rated.
        read_line(istrm_, s);
        while (istrm_.peek() != 10)
            read_line(istrm_, s);
        istrm_.get();

        //rest of game
        while (istrm_.good())
            read_turnblock();

        return;
    }

    void gameReader::read_turnblock() {
        std::string s;
        // "Turn # - [Player]" line
        read_line(istrm_, s);

        using T = return_type_of<decltype(&parser::parse_turnline)>;
        std::vector<T> action_lines{};
        T trsr_line{};
        T buys_line{};
        T draw_line{};
        while (istrm_.good() && istrm_.peek() != 10)
        {
            read_line(istrm_, s);
            T turnparse = parser::parse_turnline(s);

            auto& p = game_.players_by_name[turnparse.playerID];
            action_lines.push_back(turnparse);
            switch (turnparse.verb)
            {
            case verb_tokens::Buy: //fall through to share Gain operation
            case verb_tokens::Gain: {
                for (auto const& c : turnparse.cards)
                {
                    p.cards_in_deck[c.second] += c.first;
                }

            }break;
            case verb_tokens::Start: {
                for (auto const& c : turnparse.cards)
                {
                    p.cards_in_deck[c.second] = c.first;
                }

            }break;
            case verb_tokens::Trash: {
                for (auto const&c : turnparse.cards)
                {
                    p.cards_in_deck[c.second] -= c.first;
                }
            }break;
            default:
                ;
            }
        } istrm_.get(); // newline character (10)

        if (action_lines.back().verb == verb_tokens::Draw) {
            draw_line = action_lines.back();
            action_lines.pop_back();
        }
        if (action_lines.back().verb == verb_tokens::Shuffle)
            action_lines.pop_back();
        if (action_lines.back().verb == verb_tokens::Buy) {
            buys_line = action_lines.back();
            action_lines.pop_back();

            if (action_lines.back().verb == verb_tokens::Play
                && (std::find_if(action_lines.back().cards.begin(), action_lines.back().cards.end(),
                    [](decltype(action_lines.back().cards)::value_type c) {
                        return c.second->type.test(dominion::card::types::Treasure);
            })) != action_lines.back().cards.end()) {
                trsr_line = action_lines.back();
                action_lines.pop_back();
            }
        }


#ifdef _DEBUG
        std::cout << "\nACTIONS:\n";
        for (auto const& i : action_lines) {
            std::cout << verb_tokens_map.right.at(i.verb) << ":";
            for (auto const& c : i.cards) {
                std::cout << " " << c.first << " " << card_tokens_map.right.at(c.second);
            }
            std::cout << std::endl;
        }
        std::cout << "\nSPEND: ";
        if (!trsr_line.cards.empty()) {
            for (auto const& c : trsr_line.cards) {
                std::cout << " " << c.first << " " << card_tokens_map.right.at(c.second);
            }
            std::cout << std::endl;
        }
        std::cout << "\nBUY: ";
        if (!buys_line.cards.empty()) {
            for (auto const& c : buys_line.cards) {
                std::cout << " " << c.first << " " << card_tokens_map.right.at(c.second);
            }
            std::cout << std::endl;
        }
        std::cout << "\nDRAW: ";
        if (!draw_line.cards.empty()) {
            for (auto const& c : draw_line.cards) {
                std::cout << " " << c.first << " " << card_tokens_map.right.at(c.second);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        //std::cin.get();
#endif
        return;
    }
} // namespace dominion