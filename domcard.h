#pragma once

#include <vector>
#include "lib\BitFlag.h"

namespace dominion {
    using VP = short;

    struct card {
        enum class type : uint8_t {
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

        VP VP() const;

        /// STATICS
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
