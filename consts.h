#pragma once

#include <map>
#include <string>
#include <boost\bimap.hpp>
#include <bitset>

#include "domcard.h"

namespace dominion {

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
