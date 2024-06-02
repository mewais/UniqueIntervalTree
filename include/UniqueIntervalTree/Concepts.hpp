// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_CONCEPTS_HPP_
#define _UNIQUEINTERVALTREE_CONCEPTS_HPP_

#include <sstream>
#include <utility>
#include <type_traits>

namespace UIT
{
    template <class T, class EqualTo>
    struct is_comparable_impl 
    {
        template <class U, class V>
        static auto test(U*) -> decltype(
                std::declval<U>() == std::declval<V>() &&
                std::declval<U>() != std::declval<V>() &&
                std::declval<U>() < std::declval<V>() &&
                std::declval<U>() > std::declval<V>() &&
                std::declval<U>() <= std::declval<V>() &&
                std::declval<U>() >= std::declval<V>());

        template <class, class>
        static auto test(...) -> std::false_type;

        using type = typename std::is_same<bool, decltype(test<T, EqualTo>(0))>::type;
    };

    template <class T, class EqualTo = T>
    struct is_equality_comparable : is_comparable_impl<T, EqualTo>::type {};

    template <class T>
    struct is_printable_impl
    {
        template <class U>
        static auto test(U*) -> decltype(std::declval<std::stringstream&>() << std::declval<U>(), std::true_type());

        template <class>
        static auto test(...) -> std::false_type;

        using type = decltype(test<T>(0));
    };

    template <class T>
    struct is_printable : is_printable_impl<T>::type {};
}

#endif // _UNIQUEINTERVALTREE_CONCEPTS_HPP_
