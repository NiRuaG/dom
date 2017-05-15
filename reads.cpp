#include <iostream>
#include <iomanip>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "consts.h"
#include "structs.h"


namespace dominion {
    std::map<std::string, unsigned short> counts{};

    // getline function that excludes period '.' character at end of line
    auto read_line(std::istream& f, std::string& s) -> decltype(std::getline(f, s)) {
        auto& ret = std::getline(f, s);
        if (!s.empty() && s.back() == '.')
            s.pop_back();
        return ret;
    }

    void read_startofgame_playerstartcards(std::istream&& istr, game_struct::map_str_players& pmap)
    {
        using std::string;

        string garbage;
        struct read_struct {
            string player_name;
            int cardamt;
            string tok_card;
        } rs{};

        istr
            >> rs.player_name               // N
            >> garbage >> garbage           // starts with
            >> rs.cardamt >> rs.tok_card;   // 7 Coppers

        pmap[rs.player_name]
            .cards_in_deck[tokens_map.at(rs.tok_card)]
            = rs.cardamt;

        istr
            >> garbage                      // and
            >> rs.cardamt >> rs.tok_card    // 3 Estates
            ;

        pmap[rs.player_name]
            .cards_in_deck[tokens_map.at(rs.tok_card)]
            = rs.cardamt;

        return;
    }

    void read_startofgame(std::ifstream &f, game_struct& g) {
        using std::string;
        using std::stringstream;

        string line_gamenum;
        string line_Pstartdeck;
        string line_cmd;

        string tok;

        read_line(f, line_gamenum);      // Game #3280874, unrated.
        while (f.peek() != 10) // until blank line
        {
            read_line(f, line_Pstartdeck);   // N starts with 7 Coppers and 3 Estates.
            read_startofgame_playerstartcards(stringstream(line_Pstartdeck), g.players_by_name);
            read_line(f, line_cmd);          // N shuffles their deck.
            read_line(f, line_cmd);          // N draws # Coppers and # Estates.
        }

        /// recognize player identifying characters
        return;
    }
    
    tokens parse_verb(std::istream& istr) {
        std::string verb;
        istr >> verb;
        auto verb_find = tokens_map.find(verb);
        if (verb_find != tokens_map.end())
        {
            if (verb_find->second == tokens::Buy) {
                std::string t1, t2;
                istr >> t1 >> t2; /// !this is destructive
                if (t1 == "and" && t2 == "gains")
                {
                    ++counts["buys and gains"];
                }
                else
                {
                    std::cerr << "\b! BUYS, but not \"and gains\"";
                    std::cin.get();
                }
            }

            if (verb_find->second == tokens::React) {
                std::string t;
                istr >> t; ///! destructive
                if (t == "with")
                    ++counts["reacts with"];
                else
                {
                    std::cerr << "\b! REACTS, but not \"with\"";
                    std::cin.get();
                }
            }

            ++counts[verb_find->first];
            return verb_find->second;
        }

        std::cerr << "couldnt find verb for: [" << verb << "]";
        std::cin.get();
        throw;
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
            std::cout << "caught exception from stoi on string: " << str << std::endl;
            std::cin.get();
            i = 0;
        }
        return i;
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

            auto card_find = tokens_map.find(str_card);
            if (card_find != tokens_map.end())
            {
                ++counts[card_find->first];
                card = card_find->second;
            }
            else
            {
                std::cerr << "\b! couldnt find card: [" << str_card<< "]";
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

    void parse_line_players_turn(std::istream& istr, player_struct& player) {
        using std::string;
        using std::cout;
        using std::endl;

        // next token should be a (set of) verb(s)
        tokens verb;
        try{
            verb = parse_verb(istr);
        }
        catch (...)
        {
            std::cout << "\b! caught parse_verb exception";
            std::cin.get();
        }
        
        if (verb == tokens::Shuffle)
            return; //ennd of line is ".. shuffles their deck"

        // rest of line is set of cards
        decltype(parse_cards(istr)) cards;
        try{
            cards = parse_cards(istr);
        }
        catch (...){
            std::cout << "\b! caught parse_cards exception";
            std::cin.get();
        }

        if (verb == tokens::Buy){
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
    }

    void read_restofgame(std::ifstream& f, game_struct& g) {
        using std::string;
        using std::map;
        using std::stringstream;
        using std::cout;
        using std::endl;
        using std::setw;
        using std::left;

        string line;
        while (read_line(f, line)) {
            if (line.empty()) // skip the blank lines that occur between turns
                continue;

            ///DEBUG line
            cout << line << endl;
            //std::cin.get();


            stringstream linestream(line);

            string tok_first;
            linestream >> tok_first; // "Turn" or player ID 

            // process turn 'header' lines separately
            if (tok_first == "Turn") {
                int i;
                string garbage;
                linestream >> i >> garbage;
                read_line(linestream, line);
                ++g.players_by_name[line].num_turns;

                continue;
            }
            // else
            parse_line_players_turn(linestream, g.players_by_name[tok_first]);
        }

        for (const auto& i : counts)
            cout << setw(20) << left << i.first << " " << i.second << endl;

        return;
    }
}


