#pragma once

#include "structs.h"
struct istream;

namespace dominion {
    class gameReader
    {
    public:
        gameReader(std::istream& is, game_struct& g);

        void read_game();

    private:
        std::istream& istrm_;
        game_struct& game_;

        void read_turnblock();  
    };
}