#pragma once

#include <functional>
#include <set>

template <class T>
class Enum {
private:
    // Constructors
    // explicit Enum(int Value);
    // Predicate for finding the corresponding instance
    /*struct Enum_Predicate_Corresponds :
        public std::unary_function<const Enum<T>*, bool> {
        Enum_Predicate_Corresponds(int Value) : m_value(Value) { }
        bool operator()(const Enum<T>* E)
        {
            return E->Get_Value() == m_value;
        }
    private:
        const int m_value;
    };*/
    // Comparison functor for the set of instances
    struct Enum_Ptr_Less :
        public std::binary_function<const Enum<T>*, const Enum<T>*, bool> {
        bool operator()(const Enum<T>* E_1, const Enum<T>* E_2)
        {
            return E_1->Get_Value() < E_2->Get_Value();
        }
    };

    ////////////////////////////////////////////////////////////////////////////////////////
    /// http://www.drdobbs.com/when-enum-just-isnt-enough-enumeration-c/184403955?pgno=1 ///
    ////////////////////////////////////////////////////////////////////////////////////////
    /*
    What may not be so intuitive are the two structs in the private section, Enum_Predicate_Corresponds and Enum_Ptr_Less. 
    The first is a predicate for use with find_if in the Corresponding_Enum method. 
    It's not strictly necessary, since I could have used an explicit loop comparing the members of the set with the sought value, 
    but find_if is better style. 
    The second struct, Enum_Ptr_Less, is absolutely necessary to keep your set sorted in the order you want. 
    As Scott Meyer points out in [2], you have to be careful when dealing with associative containers of pointers. 
    The containers will by default be sorted by comparing the pointer values, which is almost never what you want. 
    So you have to give the set a comparison object whose operator(), when given two members of the set, 
    will return whether the first one is less than the other according to the appropriate criterion. 
    In our example, you need to compare the results of the Get_Value function.
    */

public:
    explicit Enum();

    // Compiler-generated copy constructor and operator= are OK.
    using instances_list_T = std::set<Enum<T> const*, Enum_Ptr_Less>;
    using const_iterator = instances_list_T::const_iterator;
    // Access to int value
    int Get_Value() const { return m_value; }
    //static int Min(void) { return (*s_instances.begin())->m_value; }
    //static int Max(void) { return (*s_instances.rbegin())->m_value; }
    /*static const Enum<T>* Corresponding_Enum(int Value)
    {
        const_iterator it = find_if(s_instances.begin(), s_instances.end(),
            Enum_Predicate_Corresponds(Value));
        return (it != s_instances.end()) ? *it : nullptr;
    }
    static bool Is_Valid_Value(int Value) { return Corresponding_Enum(Value) != nullptr; }*/
    // Number of elements
    static instances_list_T::size_type size(void) {
        return s_instances.size();
    }
    // Iteration
    static const_iterator begin()  
    { return s_instances.begin(); }
    static const_iterator end  ()  
    { return s_instances.end  (); }
    
    /// AG edits for c++ range-based for loop
    bool operator!= (const Enum<T>& other) const {
        return m_value != other.m_value(); }

    ///int operator* () const;*

private:
    int m_value;
    static int next_value;
    static instances_list_T s_instances;
};

template<class T>
Enum<T>::next_value = 0;
/*
template <class T>
inline Enum<T>::Enum(int Value) :
    m_value(Value)
{
    s_instances.insert(this);
}*/

/// AG edits
/// for auto value
template <class T>
inline Enum<T>::Enum() :
    m_value(Enum<T>::next_value++)
{
    s_instances.insert(this);
}

