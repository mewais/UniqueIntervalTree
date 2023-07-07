// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_CONCEPTS_HPP_
#define _UNIQUEINTERVALTREE_CONCEPTS_HPP_

#include <sstream>
#include <concepts>
#include <type_traits>

namespace UIT
{
    template <class T>
    concept Printable = requires(std::stringstream& os, T a)
    {
        os << a;
    };

    template <class T>
    concept Buildable = std::is_move_constructible_v<T> || std::is_copy_constructible_v<T> ||
                        std::is_move_assignable_v<T> || std::is_copy_assignable_v<T>;

    template <class T>
    concept KeyType = std::equality_comparable<T> && std::totally_ordered<T> && Printable<T>;

    template <class T>
    concept ValueType = Buildable<T> || std::is_default_constructible_v<T>;
}

#endif // _UNIQUEINTERVALTREE_CONCEPTS_HPP_