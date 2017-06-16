#include "consts.h"

namespace dominion {
    template <typename T>
    bimapT<T>
        makeBimap(std::initializer_list<typename bimapT<T>::value_type> list){
        return bimapT<T>(list.begin(), list.end());}

    //constexpr auto   ct::Action = 1 << (int)card::type::Action;
    // mix-in card types
    //constexpr auto   AttackFlag = 1 << (int)card::type::Attack  ;
    //constexpr auto Rect::Action = 1 << (int)card::type::Reaction;

    using ct = card::types;

    decltype(card::types_vec) card::types_vec = {
        ct::NONE,
        ct::Action,
        ct::Treasure,
        ct::Victory,
        ct::Curse,
        ct::Attack,
        ct::Reaction,
    };

    card const
        card::Curse{ 0, ct::Curse },

        card::Copper{ 0, ct::Treasure },
        card::Silver{ 3, ct::Treasure },
        card::Gold  { 6, ct::Treasure },

        card::Estate  { 2, ct::Victory },
        card::Duchy   { 5, ct::Victory },
        card::Province{ 8, ct::Victory },
        card::Gardens { 4, ct::Victory },

        card::Artisan     { 6, ct::Action                },
        card::Bandit      { 5, ct::Action | ct::Attack   },
        card::Bureaucrat  { 4, ct::Action | ct::Attack   },
        card::Cellar      { 2, ct::Action                },
        card::Chapel      { 2, ct::Action                },
        card::Council_Room{ 5, ct::Action                },
        card::Festival    { 5, ct::Action                },
        card::Harbinger   { 3, ct::Action                },
        card::Laboratory  { 5, ct::Action                },
        card::Library     { 5, ct::Action                },
        card::Market      { 5, ct::Action                },
        card::Merchant    { 3, ct::Action                },
        card::Militia     { 4, ct::Action | ct::Attack   },
        card::Mine        { 5, ct::Action                },
        card::Moat        { 2, ct::Action | ct::Reaction },
        card::Moneylender { 4, ct::Action                },
        card::Poacher     { 4, ct::Action                },
        card::Remodel     { 4, ct::Action                },
        card::Sentry      { 5, ct::Action                },
        card::Smithy      { 4, ct::Action                },
        card::Throne_Room { 4, ct::Action                },
        card::Vassal      { 3, ct::Action                },
        card::Village     { 3, ct::Action                },
        card::Witch       { 5, ct::Action | ct::Attack   },
        card::Workshop    { 3, ct::Action                },

        card::Card{ 0, ct::NONE } /// hacky
        ;

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