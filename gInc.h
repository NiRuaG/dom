#pragma once

/// RETURN TYPE trait
template <typename T>
struct return_type;

template <typename R, typename... Args>
struct return_type<R(*)(Args...)> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...)> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) volatile> { using type = R; };
template <typename R, typename C, typename... Args>
struct return_type<R(C::*)(Args...) const volatile> { using type = R; };

template <typename T>
using return_type_of = typename return_type<T>::type;

/// RANGE class
template <typename T>
class range {
private:
    class iter {
        friend class range;
    private:
        T m_x;

    protected:
        iter(T x) : m_x(x) {}

    public:
        iter const&
            operator++()
        { ++m_x; return *this; }

        T const&
            operator*() const
        { return m_x; }

        bool
            operator!=(const iter &other) const
        { return m_x != other.m_x; }
    };

    T m_begin;
    T m_end;

public:
    iter begin() const { return iter(m_begin); }
    iter end  () const { return iter(m_end  ); }

    range(T&& b, T&& e)
        : m_begin(b), m_end(e)
    { }
};

/// ENUM ++ overload
template<typename T>
std::enable_if_t<std::is_enum<T>::value, T&>
operator++(T& t)
{
    t = static_cast<T>(
        static_cast<std::underlying_type_t<T>>(t)
        + 1);
    return t;
}