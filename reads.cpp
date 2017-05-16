#include <iostream>
#include <iomanip>
#include <istream>
#include <string>
#include <sstream>
#include <algorithm>

#include "consts.h"
#include "structs.h"
#include "reads.h"

namespace dominion {
    std::map<std::string, unsigned short> counts{};

    // helper function: 
    //   getline that excludes period '.' character at end of line
    auto read_line(std::istream& f, std::string& s) -> decltype(std::getline(f, s)) {
        auto& ret = std::getline(f, s);
        if (!s.empty() && s.back() == '.')
            s.pop_back();
        return ret;
    }

    void read_startofgame(std::istream& strm, game_struct& g) {
        using std::string;
        using std::stringstream;

        string line_gamenum;
        read_line(strm, line_gamenum);      // Game #3280874, unrated.

        while (strm.peek() != 10) // until blank line
        {
            string str_line;
            string str_player;

            read_line(strm, str_line);
            stringstream strm_line(str_line);
            strm_line >> str_player;

            parse_turnline_players_action(strm_line, g.players_by_name[str_player]);
        }

        /// recognize player identifying characters
        return;
    }
    void read_restofgame(std::istream& strm, game_struct& g) {
        using std::string;
        using std::map;
        using std::stringstream;
        using std::cout;
        using std::endl;
        using std::setw;
        using std::left;

        string line;
        while (read_line(strm, line)) {
            if (line.empty()) // skip the blank lines that occur between turns
                continue;

            ///DEBUG
            //cout << line << endl;
            //std::cin.get();


            stringstream linestream(line);

            string str_first;
            linestream >> str_first; // "Turn" or player ID 

            // process turn 'header' lines separately
            if (str_first == "Turn") {
                int i;
                string garbage;
                linestream >> i >> garbage;
                read_line(linestream, line);
                ++g.players_by_name[line].num_turns;

                continue;
            }
            // else
            parse_turnline_players_action(linestream, g.players_by_name[str_first]);
        }

        for (const auto& i : counts)
            cout << setw(20) << left << i.first << " " << i.second << endl;

        return;
    }
    
    void parse_turnline_players_action(std::istream& strm, player_struct& player) {
        using std::string;
        using std::cout;
        using std::endl;

        // next token should be a (set of) verb(s)
        decltype(parse_verb(strm)) verb;
        try {
            verb = parse_verb(strm);
        }
        catch (...)
        {
            std::cout << "\b! caught parse_verb exception";
            std::cin.get();
        }

        if (verb == tokens::Shuffle)
            return; //ennd of line is ".. shuffles their deck"

                    // rest of line is set of cards
        decltype(parse_cards(strm)) cards;
        try {
            cards = parse_cards(strm);
        }
        catch (...) {
            std::cout << "\b! caught parse_cards exception";
            std::cin.get();
        }

        if (verb == tokens::Starts) {
            auto find = cards.find(tokens::Estate);
            if (find != cards.end())
                player.cards_in_deck[tokens::Estate] = find->second;
            find = cards.find(tokens::Duchy);
            if (find != cards.end())
                player.cards_in_deck[tokens::Duchy] = find->second;
            find = cards.find(tokens::Province);
            if (find != cards.end())
                player.cards_in_deck[tokens::Province] = find->second;
        }
        if (verb == tokens::Buy) {
            auto find = cards.find(tokens::Estate);
            if (find != cards.end())
                player.cards_in_deck[tokens::Estate] += find->second;
            find = cards.find(tokens::Duchy);
            if (find != cards.end())
                player.cards_in_deck[tokens::Duchy] += find->second;
            find = cards.find(tokens::Province);
            if (find != cards.end())
                player.cards_in_deck[tokens::Province] += find->second;
        }
        if (verb == tokens::Trash) {
            auto find = cards.find(tokens::Estate);
            if (find != cards.end())
                player.cards_in_deck[tokens::Estate] -= find->second;
            find = cards.find(tokens::Duchy);
            if (find != cards.end())
                player.cards_in_deck[tokens::Duchy] -= find->second;
            find = cards.find(tokens::Province);
            if (find != cards.end())
                player.cards_in_deck[tokens::Province] -= find->second;
        }
    }
    
    tokens parse_verb(std::istream& strm) {
        std::string verb;
        strm >> verb;
        auto verb_find = tokens_map.left.find(verb);
        if (verb_find != tokens_map.left.end())
        {
            // special verb cases
            switch (verb_find->second)
            {
            case tokens::Buy: {
                std::string t1, t2;
                strm >> t1 >> t2; /// !this is destructive
                if (t1 == "and" && t2 == "gains")
                {
                    ++counts["buys and gains"];
                }
                else
                {
                    std::cerr << "\b! BUYS, but not \"and gains\"";
                    std::cin.get();
                }
            }break;

            case tokens::React: {
                std::string t;
                strm >> t; ///! destructive
                if (t == "with")
                    ++counts["reacts with"];
                else
                {
                    std::cerr << "\b! REACTS, but not \"with\"";
                    std::cin.get();
                }
            }break;

            case tokens::Starts: {
                std::string t;
                strm >> t; /// destructive
                if (t == "with")
                    ++counts["starts with"];
                else
                {
                    std::cerr << "\b! STARTS, but not \"with\"";
                    std::cin.get();
                }
            }break;

            default:
                ;
            }//switch verb
            ++counts[verb_find->first];
            return verb_find->second;
        }// if verb found

        std::cerr << "couldnt find verb for: [" << verb << "]";
        std::cin.get();
        throw;
    }

    std::map<tokens, unsigned short> parse_cards(std::istream& istr) {
        std::map<tokens, unsigned short> cards;

        std::string str;
        while (istr >> str)
        {
            if (str == "and")
                continue; // get next token

                          // number part of pair
            unsigned short num = parse_card_num(str);

            // card part of pair
            tokens card;
            std::string str_card;
            istr >> str_card;
            // ignore ',' as final character
            if (!str_card.empty() && str_card.back() == ',')
                str_card.pop_back();

            // singular-ize
            auto sing_find = singular.find(str_card);
            if (sing_find != singular.end())
                str_card = singular.at(str_card);

            auto card_find = tokens_map.left.find(str_card);
            if (card_find != tokens_map.left.end())
            {
                ++counts[card_find->first];
                card = card_find->second;
            }
            else
            {
                std::cerr << "\b! couldnt find card: [" << str_card << "]";
                std::cin.get();
                throw;
            }

            ///DEBUG
            //std::cout
            //    << card_find->first << ": (int)" << (int)card
            //    << "\t # " << num << std::endl;
            //std::cin.get();

            cards[card] = num;
        }

        ///DEBUG
        /*for (auto const& i : cards){
        std::cout << (int)i.first << ": " << i.second << std::endl;
        }
        std::cin.get();*/

        return cards;
    }
    unsigned short parse_card_num(std::string& str)
    {
        if (str == "a" || str == "an"){
            return 1;
        }
        //else
        unsigned short i;
        try {
            i = stoi(str);
        }
        catch (...) {
            std::cout << "\b! caught exception from stoi on string: " << str << std::endl;
            std::cin.get();
            i = 0;
        }
        return i;
    }
}


