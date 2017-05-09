#include <iostream>
#include <iomanip>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

#include "consts.h"
#include "structs.h"


namespace dominion {
    std::map<std::string, unsigned short> counts{};

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
            .cards_in_deck[rs.tok_card]
            = rs.cardamt;

        istr
            >> garbage                      // and
            >> rs.cardamt >> rs.tok_card    // 3 Estates
            ;

        pmap[rs.player_name]
            .cards_in_deck[rs.tok_card]
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

    void parse_players_turn(std::istream& istr, player_struct player) {
        using std::string;
        using std::cout;
        using std::endl;

        // next token should be a (set of) verb(s)
        string tok_verb;
        istr >> tok_verb;
        auto vf = tokens_map.find(tok_verb);
        if (vf != tokens_map.end())
        {
            switch (vf->second)
            {
            case tokens::Buy: {
                string t1, t2;
                istr >> t1 >> t2;
                if (t1 == "and" && t2 == "gains")
                {
                    ++counts["buys and gains"];
                }
                else
                {
                    std::cerr << "BUYS, but not \"and gains\"";
                    return;
                }
            }break;

            case tokens::Trash: {
                ++counts[tok_verb];
            }break;

            default:
                ;
            }
        }


        // rest of line
        string tok;
        while (istr >> tok) {

            if (tok == "a" || tok == "an")
                continue; // get next token

                          ///"and" should set a *flag*
            if (tok == "and" || tok == "their" || tok == "with")
                continue; // get next token

                          // ignore punctuation as final character, and proceed to process as standard token
            if (tok.back() == '.' || tok.back() == ',')
                tok.pop_back();

            if (tokens_map.count(tok) == 0)
            {
                try {
                    auto i = stoi(tok);
                }
                catch (...) {
                    cout << tok << endl;
                    //cin.get();
                }
            }
            else
            {
                ++counts[tok];
                switch (tokens_map.at(tok))
                {
                case tokens::Estate:
                {

                }break;
                default:
                    ;
                }
            }

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
            parse_players_turn(linestream, g.players_by_name[tok_first]);

            for (const auto& i : counts)
                cout << setw(20) << left << i.first << " " << i.second << endl;

            return;
        }
    }
}


