#pragma once

#include <map>
#include <string>
#include <boost\bimap.hpp>
#include <bitset>
#include <vector>
#include "lib\BitFlag.h"

namespace dominion {
    struct card {
        enum class types : uint8_t {
            NONE = 0,
            Action,
            Treasure,
            Victory,
            Curse,
            Attack,
            Reaction,
            _END,
        };

        int cost;
        BitFlag<types> type;

        static std::vector<types> const types_vec;

        // Cards
        static card const
            Curse,

            Copper,
            Silver,
            Gold,

            Estate,
            Duchy,
            Province,
            Gardens,

            Artisan,
            Bandit,
            Bureaucrat,
            Cellar,
            Chapel,
            Council_Room,
            Festival,
            Harbinger,
            Laboratory,
            Library,
            Market,
            Merchant,
            Militia,
            Mine,
            Moat,
            Moneylender,
            Poacher,
            Remodel,
            Sentry,
            Smithy,
            Throne_Room,
            Vassal,
            Village,
            Witch,
            Workshop,
            // Objects
            Card
            ;

        // object token, unused?
        // Deck
    };

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
