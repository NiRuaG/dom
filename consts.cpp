#include "consts.h"

namespace dominion {
    template <typename T>
    token_bimap<T>
        makeBimap(std::initializer_list<typename token_bimap<T>::value_type> list)
    {
        return token_bimap<T>(list.begin(), list.end());
    }
}