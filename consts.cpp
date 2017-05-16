#include "consts.h"

namespace dominion {
    token_bimapT
        makeBimap(std::initializer_list<token_bimapT::value_type> list)
    {
        return token_bimapT(list.begin(), list.end());
    }
}
