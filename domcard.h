#pragma once

#include <vector>
#include <map>
#include "lib\BitFlag.h"

namespace dominion {
    struct card {
        enum class type {
            Action=0,
            Treasure,
            Victory ,
            Curse   ,
            Attack  ,
            Reaction,
            _END    ,
        };

        int cost;
        BitFlag<type> types;
        int plus_actions() const{
            static std::map<card const *const, int> m =
            {
                { &Cellar    , 1 },
                { &Festival  , 2 },
                { &Harbinger , 1 },
                { &Laboratory, 1 },
                { &Market    , 1 },
                { &Merchant  , 1 },
                { &Poacher   , 1 },
                { &Sentry    , 1 },
                { &Village   , 2 },
            };
            return m[this];
        }

        // Cards
        static card const
            Curse,

            Copper,
            Silver,
            Gold  ,

            Estate  ,
            Duchy   ,
            Province,
            Gardens ,

            Artisan     ,
            Bandit      ,
            Bureaucrat  ,
            Cellar      ,
            Chapel      ,
            Council_Room,
            Festival    ,
            Harbinger   ,
            Laboratory  ,
            Library     ,
            Market      ,
            Merchant    ,
            Militia     ,
            Mine        ,
            Moat        ,
            Moneylender ,
            Poacher     ,
            Remodel     ,
            Sentry      ,
            Smithy      ,
            Throne_Room ,
            Vassal      ,
            Village     ,
            Witch       ,
            Workshop    ,
            // Objects
            Card
            ;
            // object token, unused?
            // Deck
    };
}
