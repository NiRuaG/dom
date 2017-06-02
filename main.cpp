// I/O
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
// FILES
#include <fstream>
using std::ifstream;
// STRINGS
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

#include "gInc.h"
#include "structs.h"
#include "consts.h"
#include "reads.h"
#include "parser.h"

const auto FILE_NAME_PATH = R"(.\gamesaves\3943515.txt)";


game_struct THE_GAME;


/*
bool isVictoryCard(dominion::card_tokens c)
{
    using dominion::card_tokens;
    return (
        c == card_tokens::Estate
        || c == card_tokens::Duchy
        || c == card_tokens::Province
        || c == card_tokens::Gardens
        );
}
*/

unsigned short calc_VP(player_struct const& plyr)
{
    using namespace dominion;

    return_type_of<decltype(&calc_VP)> ret = 0;

    unsigned short gV = floor(plyr.cards_in_deck.size() / 10);

    auto
    f = plyr.cards_in_deck.find(&Estate  );
    if (f != plyr.cards_in_deck.end())
        ret +=  1 * f->second;
    
    f = plyr.cards_in_deck.find(&Duchy   );
    if (f != plyr.cards_in_deck.end())
        ret +=  3 * f->second;
    
    f = plyr.cards_in_deck.find(&Province);
    if (f != plyr.cards_in_deck.end())
        ret +=  6 * f->second;
    
    f = plyr.cards_in_deck.find(&Gardens );
    if (f != plyr.cards_in_deck.end())
        ret += gV * f->second;
    
    return ret;
}

void print_summary() {
    cout << "\nNumber of Turns\n";
    for (auto const& i : THE_GAME.players_by_name)
    {
        auto cut_name = i.first;
        cut_name.resize(20);
        cout << setw(20) << cut_name << " " << i.second.num_turns << endl;
    }

    cout << "\nPlayer decks:\n";
    for (auto const& p : THE_GAME.players_by_name)
    {
        int tot_cost = 0;
        cout << endl << setw(20) << p.first.substr(0,20);
        for (auto const& c : p.second.cards_in_deck)
        {
            cout << "\n\t" << setw(20) << dominion::card_tokens_map.right.at(c.first) << " " << c.second;
            tot_cost += c.first->cost * c.second;
        }

        // Victory Points
        cout << "\nVP: " << calc_VP(p.second) << endl;
        cout << "total cost of deck: " << tot_cost << endl;
    }

    return;
}

int main(int argc, char *argv[]){
    ifstream gamefile(FILE_NAME_PATH);

    if (!gamefile.is_open()) {
        cout << "\b! error opening file at\n" << FILE_NAME_PATH << endl;
    }
    else {
        std::ios::sync_with_stdio(false);

        dominion::gameReader(gamefile, THE_GAME).read_game();
        
        for (const auto& i : dominion::parser::counts_)
            std::cout << std::setw(20) << std::left << i.first << " " << i.second << std::endl;

        print_summary();
    }
    
    char c_exit;
    do{std::cin.get(c_exit);
    }while (c_exit != 'x'); 
}