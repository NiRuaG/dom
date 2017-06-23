#include "domcard.h"

namespace dominion {
    /// possible to make a constructor with static assert that these are in same order as enum?
    /// or add methods to BitFlag to handle for range
    /// or free function 'range' on BitFlag<T>
    /*decltype(card::all_types) card::all_types = {
        type::Action  ,
        type::Treasure,
        type::Victory ,
        type::Curse   ,
        type::Attack  ,
        type::Reaction,
    };*/

    card const
        card::Curse{ 0, type::Curse },

        card::Copper{ 0, type::Treasure },
        card::Silver{ 3, type::Treasure },
        card::Gold  { 6, type::Treasure },

        card::Estate  { 2, type::Victory },
        card::Duchy   { 5, type::Victory },
        card::Province{ 8, type::Victory },
        card::Gardens { 4, type::Victory },

        card::Artisan     { 6, type::Action                  },
        card::Bandit      { 5, type::Action | type::Attack   },
        card::Bureaucrat  { 4, type::Action | type::Attack   },
        card::Cellar      { 2, type::Action                  },
        card::Chapel      { 2, type::Action                  },
        card::Council_Room{ 5, type::Action                  },
        card::Festival    { 5, type::Action                  },
        card::Harbinger   { 3, type::Action                  },
        card::Laboratory  { 5, type::Action                  },
        card::Library     { 5, type::Action                  },
        card::Market      { 5, type::Action                  },
        card::Merchant    { 3, type::Action                  },
        card::Militia     { 4, type::Action | type::Attack   },
        card::Mine        { 5, type::Action                  },
        card::Moat        { 2, type::Action | type::Reaction },
        card::Moneylender { 4, type::Action                  },
        card::Poacher     { 4, type::Action                  },
        card::Remodel     { 4, type::Action                  },
        card::Sentry      { 5, type::Action                  },
        card::Smithy      { 4, type::Action                  },
        card::Throne_Room { 4, type::Action                  },
        card::Vassal      { 3, type::Action                  },
        card::Village     { 3, type::Action                  },
        card::Witch       { 5, type::Action | type::Attack   },
        card::Workshop    { 3, type::Action                  },

        card::Card{ 0,{} }
    ;
}