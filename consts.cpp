#include "consts.h"

namespace dominion {
    template <typename T>
    bimapT<T>
        makeBimap(std::initializer_list<typename bimapT<T>::value_type> list)
    { return bimapT<T>(list.begin(), list.end()); }

    decltype(card_tokens_map) card_tokens_map = makeBimap<card const*const>(
    {
        { "card", &card::Card },

        { "Copper", &card::Copper },
        { "Silver", &card::Silver },
        { "Gold"  , &card::Gold   },

        { "Estate"  , &card::Estate   },
        { "Duchy"   , &card::Duchy    },
        { "Province", &card::Province },
        { "Gardens" , &card::Gardens  },

        { "Bandit"     , &card::Bandit      },
        { "Bureaucrat" , &card::Bureaucrat  },
        { "Cellar"     , &card::Cellar      },
        { "Chapel"     , &card::Chapel      },
        { "Festival"   , &card::Festival    },
        { "Harbinger"  , &card::Harbinger   },
        { "Laboratory" , &card::Laboratory  },
        { "Library"    , &card::Library     },
        { "Market"     , &card::Market      },
        { "Merchant"   , &card::Merchant    },
        { "Militia"    , &card::Militia     },
        { "Moat"       , &card::Moat        },
        { "Moneylender", &card::Moneylender },
        { "Poacher"    , &card::Poacher     },
        { "Remodel"    , &card::Remodel     },
        { "Sentry"     , &card::Sentry      },
        { "Smithy"     , &card::Smithy      },
        { "Vassal"     , &card::Vassal      },
    });

    decltype(singular) singular
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

    decltype(verb_tokens_map) verb_tokens_map = makeBimap<verb_tokens>(
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
        { "starts"  , verb_tokens::Start   },
        { "topdecks", verb_tokens::Topdeck },
        { "trashes" , verb_tokens::Trash   },
    }) ;
}