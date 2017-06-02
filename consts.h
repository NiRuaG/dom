#pragma once

#include <map>
#include <string>
#include <boost\bimap.hpp>

namespace dominion {
    struct card {
        int cost;
    };
    // Cards
    extern const card Curse;

    extern const card Copper;
    extern const card Silver;
    extern const card Gold  ;

    extern const card Estate  ;
    extern const card Duchy   ;
    extern const card Province;
    extern const card Gardens ;

    extern const card Artisan     ;
    extern const card Bandit      ;
    extern const card Bureaucrat  ;
    extern const card Cellar      ;
    extern const card Chapel      ;
    extern const card Council_Room;
    extern const card Festival    ;
    extern const card Harbinger   ;
    extern const card Laboratory  ;
    extern const card Library     ;
    extern const card Market      ;
    extern const card Merchant    ;
    extern const card Militia     ;
    extern const card Mine        ;
    extern const card Moat        ;
    extern const card Moneylender ;
    extern const card Poacher     ;
    extern const card Remodel     ;
    extern const card Sentry      ;
    extern const card Smithy      ;
    extern const card Throne_Room ;
    extern const card Vassal      ;
    extern const card Village     ;
    extern const card Witch       ;
    extern const card Workshop    ;
    // Objects
    extern const card Card;

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
        Starts,
        Topdeck,
        Trash,
    };

    
    extern const std::map<std::string, std::string> singular;
    
    template <typename T>
    using bimapT = boost::bimap<const std::string, T>;

    extern const bimapT<card const*const> card_tokens_map;
    extern const bimapT<verb_tokens     > verb_tokens_map;
}
