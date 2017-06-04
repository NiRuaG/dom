#include "consts.h"

namespace dominion {
    template <typename T>
    bimapT<T>
        makeBimap(std::initializer_list<typename bimapT<T>::value_type> list){
        return bimapT<T>(list.begin(), list.end());}

    card const
        Curse{ 0 },

        Copper{ 0 },
        Silver{ 3 },
        Gold  { 6 },

        Estate  { 2 },
        Duchy   { 5 },
        Province{ 8 },
        Gardens { 4 },

        Artisan     { 6 },
        Bandit      { 5 },
        Bureaucrat  { 4 },
        Cellar      { 2 },
        Chapel      { 2 },
        Council_Room{ 5 },
        Festival    { 5 },
        Harbinger   { 3 },
        Laboratory  { 5 },
        Library     { 5 },
        Market      { 5 },
        Merchant    { 3 },
        Militia     { 4 },
        Mine        { 5 },
        Moat        { 2 },
        Moneylender { 4 },
        Poacher     { 4 },
        Remodel     { 4 },
        Sentry      { 5 },
        Smithy      { 4 },
        Throne_Room { 4 },
        Vassal      { 3 },
        Village     { 3 },
        Witch       { 5 },
        Workshop    { 3 },

        Card{ 0 };

    decltype(card_tokens_map) card_tokens_map = makeBimap<card const*const>(
    {
        { "card", &Card },

        { "Copper", &Copper },
        { "Silver", &Silver },
        { "Gold"  , &Gold   },

        { "Estate"  , &Estate   },
        { "Duchy"   , &Duchy    },
        { "Province", &Province },
        { "Gardens" , &Gardens  },

        { "Bandit"     , &Bandit      },
        { "Bureaucrat" , &Bureaucrat  },
        { "Cellar"     , &Cellar      },
        { "Chapel"     , &Chapel      },
        { "Festival"   , &Festival    },
        { "Harbinger"  , &Harbinger   },
        { "Laboratory" , &Laboratory  },
        { "Library"    , &Library     },
        { "Market"     , &Market      },
        { "Merchant"   , &Merchant    },
        { "Militia"    , &Militia     },
        { "Moat"       , &Moat        },
        { "Moneylender", &Moneylender },
        { "Poacher"    , &Poacher     },
        { "Remodel"    , &Remodel     },
        { "Sentry"     , &Sentry      },
        { "Smithy"     , &Smithy      },
        { "Vassal"     , &Vassal      },
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