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

#include "structs.h"
#include "consts.h"


const auto FILE_NAME_PATH = R"(.\gamesaves\3289127.txt)";


game_struct THE_GAME;

namespace dominion {
    void read_startofgame(ifstream&, game_struct&);
    void read_restofgame (ifstream&, game_struct&);
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
        auto cut_name = p.first;
        cut_name.resize(20);
        cout << setw(20) << cut_name << endl;
        for (auto const& c : p.second.cards_in_deck)
        {
            cout << '\t' << setw(20) << c.first << " " << c.second << endl;
        }
    }
    return;
}

int main(int argc, char *argv[]){
    ifstream gamefile(FILE_NAME_PATH);
    if (!gamefile.is_open()) {
        cout << "\nerror opening file at\n" << FILE_NAME_PATH << endl;
    }
    else {
        dominion::read_startofgame(gamefile, THE_GAME);
        dominion::read_restofgame (gamefile, THE_GAME);

        print_summary();
    }
    
    std::cin.get();
}