#pragma once

#include <map>
#include <boost\bimap.hpp>


namespace dominion {
    enum class tokens {
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
    
        // Verbs
        Buy,
        Discard,
        Draw,
        Gain,
        Play,
        React,
        Reveal,
        Shuffle,
        Starts,
        Topdeck,
        Trash,

        // Objects
        Deck,
        Card,
    };


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
        { "cards"       , "card"       },
    };

    using token_bimapT = boost::bimap<std::string, tokens>;
    token_bimapT makeBimap(std::initializer_list<token_bimapT::value_type>);

    static const token_bimapT tokens_map = makeBimap(
    {
        { "Copper", tokens::Copper },
        { "Silver", tokens::Silver },
        { "Gold"  , tokens::Gold   },

        { "Estate"  , tokens::Estate   },
        { "Duchy"   , tokens::Duchy    },
        { "Province", tokens::Province },
        { "Gardens" , tokens::Gardens  },

        { "Bandit"     , tokens::Bandit      },
        { "Bureaucrat" , tokens::Bureaucrat  },
        { "Cellar"     , tokens::Cellar      },
        { "Chapel"     , tokens::Chapel      },
        { "Festival"   , tokens::Festival    },
        { "Laboratory" , tokens::Laboratory  },
        { "Library"    , tokens::Library     },
        { "Market"     , tokens::Market      },
        { "Merchant"   , tokens::Merchant    },
        { "Militia"    , tokens::Militia     },
        { "Moat"       , tokens::Moat        },
        { "Moneylender", tokens::Moneylender },
        { "Poacher"    , tokens::Poacher     },
        { "Remodel"    , tokens::Remodel     },
        { "Sentry"     , tokens::Sentry      },
        { "Smithy"     , tokens::Smithy      },

        // Verbs
        { "buys"    , tokens::Buy     },
        { "discards", tokens::Discard },
        { "draws"   , tokens::Draw    },
        { "gains"   , tokens::Gain    },
        { "plays"   , tokens::Play    },
        { "reacts"  , tokens::React   },
        { "reveals" , tokens::Reveal  },
        { "shuffles", tokens::Shuffle },
        { "starts"  , tokens::Starts  },
        { "topdecks", tokens::Topdeck },
        { "trashes" , tokens::Trash   },

        // Objects
        { "deck", tokens::Deck },
        { "card", tokens::Card },
    });
}
