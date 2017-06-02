#include "consts.h"

namespace dominion {
    template <typename T>
    bimapT<T>
        makeBimap(std::initializer_list<typename bimapT<T>::value_type> list) 
    {
        return bimapT<T>(list.begin() , list.end() ) ;
    }

    decltype(Curse) Curse{ 0 };

    decltype(Copper) Copper{ 0 };
    decltype(Silver) Silver{ 3 };
    decltype(Gold  ) Gold  { 6 };

    decltype(Estate  ) Estate  { 2 };
    decltype(Duchy   ) Duchy   { 5 };
    decltype(Province) Province{ 8 };
    decltype(Gardens ) Gardens { 4 };

    decltype(Artisan     ) Artisan     { 6 };
    decltype(Bandit      ) Bandit      { 5 };
    decltype(Bureaucrat  ) Bureaucrat  { 4 };
    decltype(Cellar      ) Cellar      { 2 };
    decltype(Chapel      ) Chapel      { 2 };
    decltype(Council_Room) Council_Room{ 5 };
    decltype(Festival    ) Festival    { 5 };
    decltype(Harbinger   ) Harbinger   { 3 };
    decltype(Laboratory  ) Laboratory  { 5 };
    decltype(Library     ) Library     { 5 };
    decltype(Market      ) Market      { 5 };
    decltype(Merchant    ) Merchant    { 3 };
    decltype(Militia     ) Militia     { 4 };
    decltype(Mine        ) Mine        { 5 };
    decltype(Moat        ) Moat        { 2 };
    decltype(Moneylender ) Moneylender { 4 };
    decltype(Poacher     ) Poacher     { 4 };
    decltype(Remodel     ) Remodel     { 4 };
    decltype(Sentry      ) Sentry      { 5 };
    decltype(Smithy      ) Smithy      { 4 };
    decltype(Throne_Room ) Throne_Room { 4 };
    decltype(Vassal      ) Vassal      { 3 };
    decltype(Village     ) Village     { 3 };
    decltype(Witch       ) Witch       { 5 };
    decltype(Workshop    ) Workshop    { 3 };

    decltype(Card) Card{ 0 };

    decltype(card_tokens_map)  card_tokens_map = makeBimap<card const*const>(
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
    }) ;

    decltype(singular)  singular
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

    decltype(verb_tokens_map)  verb_tokens_map = makeBimap<verb_tokens>(
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
    }) ;
}