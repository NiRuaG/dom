#pragma once
#include <map>

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
        Topdeck,
        Trash,

        // Objects
        Deck,
        Card,
    };

    using token_mapT = std::map<std::string, tokens>;

    static const token_mapT tokens_map =
    {
        { "Copper"      , tokens::Copper },
        { "Coppers"     , tokens::Copper },
        { "Silver"      , tokens::Silver },
        { "Silvers"     , tokens::Silver },
        { "Gold"        , tokens::Gold   },
        { "Golds"       , tokens::Gold   },
        
        { "Estate"      , tokens::Estate   },
        { "Estates"     , tokens::Estate   },
        { "Duchy"       , tokens::Duchy    },
        { "Duchies"     , tokens::Duchy    },
        { "Province"    , tokens::Province },
        { "Provinces"   , tokens::Province },
        { "Gardens"     , tokens::Gardens  },
        //{ "Gardens"     , tokens::Gardens    },
        
        { "Bandit"      , tokens::Bandit      },
        { "Bandits"     , tokens::Bandit      },
        { "Bureaucrat"  , tokens::Bureaucrat  },
        { "Bureaucrats" , tokens::Bureaucrat  },
        { "Cellar"      , tokens::Cellar      },
        { "Cellars"     , tokens::Cellar      },
        { "Chapel"      , tokens::Chapel      },
        { "Chapels"     , tokens::Chapel      },
        { "Festival"    , tokens::Festival    },
        { "Festivals"   , tokens::Festival    },
        { "Laboratory"  , tokens::Laboratory  },
        { "Laboratories", tokens::Laboratory  },
        { "Library"     , tokens::Library     },
        { "Libraries"   , tokens::Library     },
        { "Market"      , tokens::Market      },
        { "Markets"     , tokens::Market      },
        { "Merchant"    , tokens::Merchant    },
        { "Merchants"   , tokens::Merchant    },
        { "Militia"     , tokens::Militia     },
        { "Militias"    , tokens::Militia     },
        { "Moat"        , tokens::Moat        },
        { "Moats"       , tokens::Moat        },
        { "Moneylender" , tokens::Moneylender },
        { "Moneylenders", tokens::Moneylender },
        { "Poacher"     , tokens::Poacher     },
        { "Poachers"    , tokens::Poacher     },
        { "Remodel"     , tokens::Remodel     },
        { "Remodels"    , tokens::Remodel     },
        { "Sentry"      , tokens::Sentry      },
        { "Sentries"    , tokens::Sentry      },
        { "Smithy"      , tokens::Smithy      },
        { "Smithies"    , tokens::Smithy      },
        
        // Verbs
        { "buys"    , tokens::Buy     },
        { "discards", tokens::Discard },
        { "draws"   , tokens::Draw    },
        { "gains"   , tokens::Gain    },
        { "plays"   , tokens::Play    },
        { "reacts"  , tokens::React   },
        { "reveals" , tokens::Reveal  },
        { "shuffles", tokens::Shuffle },
        { "topdecks", tokens::Topdeck },
        { "trashes" , tokens::Trash   },
        
        // Objects
        { "deck" , tokens::Deck },
        { "card" , tokens::Card },
        { "cards", tokens::Card },
    };


}
