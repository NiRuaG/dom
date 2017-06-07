#include "consts.h"

namespace dominion {
    template <typename T>
    bimapT<T>
        makeBimap(std::initializer_list<typename bimapT<T>::value_type> list){
        return bimapT<T>(list.begin(), list.end());}
    
    
    constexpr auto   ActionFlag = 1 << (int)card::types::Action;
    // mix-in card types
    constexpr auto   AttackFlag = 1 << (int)card::types::Attack  ;
    constexpr auto ReactionFlag = 1 << (int)card::types::Reaction;

    card const
        Curse{ 0, 1 << (int)card::types::Curse },

        Copper{ 0, 1 << (int)card::types::Treasure },
        Silver{ 3, 1 << (int)card::types::Treasure },
        Gold  { 6, 1 << (int)card::types::Treasure },

        Estate  { 2, 1 << (int)card::types::Victory },
        Duchy   { 5, 1 << (int)card::types::Victory },
        Province{ 8, 1 << (int)card::types::Victory },
        Gardens { 4, 1 << (int)card::types::Victory },

        Artisan     { 6, ActionFlag },
        Bandit      { 5, ActionFlag | AttackFlag },
        Bureaucrat  { 4, ActionFlag | AttackFlag },
        Cellar      { 2, ActionFlag },
        Chapel      { 2, ActionFlag },
        Council_Room{ 5, ActionFlag },
        Festival    { 5, ActionFlag },
        Harbinger   { 3, ActionFlag },
        Laboratory  { 5, ActionFlag },
        Library     { 5, ActionFlag },
        Market      { 5, ActionFlag },
        Merchant    { 3, ActionFlag },
        Militia     { 4, ActionFlag | AttackFlag },
        Mine        { 5, ActionFlag },
        Moat        { 2, ActionFlag | ReactionFlag },
        Moneylender { 4, ActionFlag },
        Poacher     { 4, ActionFlag },
        Remodel     { 4, ActionFlag },
        Sentry      { 5, ActionFlag },
        Smithy      { 4, ActionFlag },
        Throne_Room { 4, ActionFlag },
        Vassal      { 3, ActionFlag },
        Village     { 3, ActionFlag },
        Witch       { 5, ActionFlag | AttackFlag },
        Workshop    { 3, ActionFlag },

        Card{ 0, 0 };

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