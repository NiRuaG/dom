#pragma once
#include <iostream>
#include <bitset>
#include <cassert>

  ////////////////////////////////////////////////////
 /// https://codereview.stackexchange.com/q/96146 ///
////////////////////////////////////////////////////
/**
* BitFlag implements a bitset usable with `enum` and `enum class`.
*
* It provide a typesafe interface for manipulating the bitset. This helps
* prevents mistake as the various operator and function will refuse a
* parameter that doesn't match the expected enum type.
*
* A flagset supports one user-defined enumeration. The number of flags
* (ie the member of the user enumeration) is not limited, as the underlying
* bitset (std::bitset) can have an arbitrary large size.
*
* REQUIREMENTS:
*      * The user enumeration shall not explicitely set any value.
*      * The last enumeration member shall be: "_END"
*/
template<typename T>
struct BitFlag
{
private:
    using utype = std::underlying_type_t<T>;
    std::bitset<static_cast<utype>(T::_END)> bitset;

public:
    BitFlag() = default;
    BitFlag(BitFlag const& o) = default;
    BitFlag(T const& t) : bitset(1i64 << static_cast<utype>(t)) {} /// explicit?

    auto test(const T& t) const -> decltype(bitset.test(static_cast<utype>(t)))
    { return bitset.test(static_cast<utype>(t)); }

    BitFlag& operator|=(T const& val) {
        bitset.set(static_cast<utype>(val));
        return *this;
    }

    BitFlag& operator&=(T const& val) {
        auto tmp = bitset.test(static_cast<utype>(val));
        bitset.reset();
        bitset.set(static_cast<utype>(val)) = tmp;
        return *this;
    }

    BitFlag& operator|=(const BitFlag &o) {
        bitset |= o.bitset;
        return *this;
    }

    BitFlag& operator&=(const BitFlag &o) {
        bitset &= o.bitset;
        return *this;
    }

    BitFlag& operator=(const BitFlag &o) = default;

    /**
    * Return a bitset containing the result of the
    * bitwise AND between *this and val.
    *
    * The resulting bitset can contain at most 1 bit.
    */
    BitFlag operator&(T const& val) {
        BitFlag ret(*this);
        ret &= val;

        assert(ret.bitset.count() <= 1);
        return ret;
    }

    /**
    * Perform a AND binary operation between *this and
    * `val` and return the result as a copy.
    */
    BitFlag operator&(BitFlag const& val) {
        BitFlag ret(*this);
        ret.bitset &= val.bitset;

        return ret;
    }

    /**
    * Return a bitset containing the result of the
    * bitwise OR between *this and val.
    *
    * The resulting bitset contains at least 1 bit.
    */
    BitFlag operator|(T const& val)
    {
        BitFlag ret(*this);
        ret |= val;

        assert(ret.bitset.count() >= 1);
        return ret;
    }

    /**
    * Perform a OR binary operation between *this and
    * `val` and return the result as a copy.
    */
    BitFlag operator|(const BitFlag &val)
    {
        BitFlag ret(*this);
        ret.bitset |= val.bitset;

        return ret;
    }

    BitFlag operator~()
    {
        BitFlag cp(*this);
        cp.bitset.flip();

        return cp;
    }

    /**
    * The bitset evaluates to true if any bit is set.
    */
    explicit operator bool() const
    {
        return bitset.any();
    }

    /**
    * Below are the method from std::bitset that we expose.
    */

    bool operator==(const BitFlag &o) const
    {
        return bitset == o.bitset;
    }

    std::size_t size() const
    {
        return bitset.size();
    }

    std::size_t count() const
    {
        return bitset.count();
    }

    BitFlag &set()
    {
        bitset.set();
        return *this;
    }

    BitFlag &reset()
    {
        bitset.reset();
        return *this;
    }

    BitFlag &flip()
    {
        bitset.flip();
        return *this;
    }

    BitFlag &set(const T &val, bool value = true)
    {
        bitset.set(static_cast<utype>(val), value);
        return *this;
    }

    BitFlag &reset(const T&val)
    {
        bitset.reset(static_cast<utype>(val));
        return *this;
    }

    BitFlag &flip(const T &val)
    {
        bitset.flip(static_cast<utype>(val));
        return *this;
    }

    bool operator[](const T&val)
    {
        return bitset[static_cast<utype>(val)];
    }

    /**
    * Overload for std::ostream
    */
    friend std::ostream& operator<<(std::ostream& stream, const BitFlag& me)
    {
        return stream << me.bitset;
    }
};

/**
* Provide a free operator allowing to combine two enumeration
* member into a BitFlag.
*/
template<typename T>
std::enable_if_t<std::is_enum<T>::value, BitFlag<T>>
operator|(const T &lhs, const T &rhs)
{
    BitFlag<T> bs;
    bs |= lhs;
    bs |= rhs;

    return bs;
}