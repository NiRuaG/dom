#pragma once

#include <map>
#include <boost\bimap.hpp>


namespace dominion {
    enum class card_tokens {
        // Cards
        Copper,
        Silver,
        Gold,

        Estate,
        Duchy,
        Province,
        Gardens,

        Bandit,
        Bureaucrat,
        Cellar,
        Chapel,
        Festival,
        Harbinger,
        Laboratory,
        Library,
        Market,
        Merchant,
        Militia,
        Moat,
        Moneylender,
        Poacher,
        Remodel,
        Sentry,
        Smithy,
        Vassal,

        // Objects
        Card
    };

    enum class verb_tokens {
        // Verbs
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

    // object token, unused?
    // Deck


    static const std::map<std::string, std::string> singular
    {
        { "Coppers"     , "Copper"     },
        { "Silvers"     , "Silver"     },
        { "Golds"       , "Gold"       },
        { "Estates"     , "Estate"     },
        { "Duchies"     , "Duchy"      },
        { "Provinces"   , "Province"   },
        //{ "Gardens"     , "Gardens"    },
        { "Bandits"     , "Bandit"     },
        { "Bureaucrats" , "Bureaucrat" },
        { "Cellars"     , "Cellar"     },
        { "Chapels"     , "Chapel"     },
        { "Festivals"   , "Festival"   },
        { "Harbingers"  , "Harbinger"  },
        { "Laboratories", "Laboratory" },
        { "Libraries"   , "Library"    },
        { "Markets"     , "Market"     },
        { "Merchants"   , "Merchant"   },
        { "Militias"    , "Militia"    },
        { "Moats"       , "Moat"       },
        { "Moneylenders", "Moneylender"},
        { "Poachers"    , "Poacher"    },
        { "Remodels"    , "Remodel"    },
        { "Sentries"    , "Sentry"     },
        { "Smithies"    , "Smithy"     },
        { "Vassals"     , "Vassal"     },
        { "cards"       , "card"       },
    };

    template <typename T>
    using token_bimap = boost::bimap<std::string, T>;

    template <typename T>
    token_bimap<T> makeBimap(std::initializer_list<typename token_bimap<T>::value_type>);


    static const auto card_tokens_map = makeBimap<card_tokens>(
    {
        { "card", card_tokens::Card },

        { "Copper", card_tokens::Copper },
        { "Silver", card_tokens::Silver },
        { "Gold"  , card_tokens::Gold   },

        { "Estate"  , card_tokens::Estate   },
        { "Duchy"   , card_tokens::Duchy    },
        { "Province", card_tokens::Province },
        { "Gardens" , card_tokens::Gardens  },

        { "Bandit"     , card_tokens::Bandit      },
        { "Bureaucrat" , card_tokens::Bureaucrat  },
        { "Cellar"     , card_tokens::Cellar      },
        { "Chapel"     , card_tokens::Chapel      },
        { "Festival"   , card_tokens::Festival    },
        { "Harbinger"  , card_tokens::Harbinger   },
        { "Laboratory" , card_tokens::Laboratory  },
        { "Library"    , card_tokens::Library     },
        { "Market"     , card_tokens::Market      },
        { "Merchant"   , card_tokens::Merchant    },
        { "Militia"    , card_tokens::Militia     },
        { "Moat"       , card_tokens::Moat        },
        { "Moneylender", card_tokens::Moneylender },
        { "Poacher"    , card_tokens::Poacher     },
        { "Remodel"    , card_tokens::Remodel     },
        { "Sentry"     , card_tokens::Sentry      },
        { "Smithy"     , card_tokens::Smithy      },
        { "Vassal"     , card_tokens::Vassal      },
    });

    static const auto verb_tokens_map = makeBimap<verb_tokens>(
    {
        // Verbs
        { "buys"    , verb_tokens::Buy     },
        { "discards", verb_tokens::Discard },
        { "draws"   , verb_tokens::Draw    },
        { "gains"   , verb_tokens::Gain    },
        { "looks"   , verb_tokens::Look    },
        { "plays"   , verb_tokens::Play    },
        { "reacts"  , verb_tokens::React   },
        { "reveals" , verb_tokens::Reveal  },
        { "shuffles", verb_tokens::Shuffle },
        { "starts"  , verb_tokens::Starts  },
        { "topdecks", verb_tokens::Topdeck },
        { "trashes" , verb_tokens::Trash   },
    });
    // Objects
    //{ "deck", tokens::Deck },
}
