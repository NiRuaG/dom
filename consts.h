#pragma once

#include <map>
#include <string>
#include <boost\bimap.hpp>

namespace dominion {
    struct card {
        int cost;
    };

    // Cards
    extern card const
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
        Card;

    // object token, unused?
    // Deck

    enum class verb_tokens {
        Buy,
        Discard,
        Draw,
        Gain,
        Look,
        Play,
        React,
        Reveal,
        Shuffle,
        Start,
        Topdeck,
        Trash,
    };

    
    extern const std::map<std::string, std::string> singular;
    
    template <typename T>
    using bimapT = boost::bimap<const std::string, T>;

    extern const bimapT<card const*const> card_tokens_map;
    extern const bimapT<verb_tokens     > verb_tokens_map;
}
