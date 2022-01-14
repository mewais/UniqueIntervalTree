// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_CONCEPTS_HPP_
#define _UNIQUEINTERVALTREE_CONCEPTS_HPP_

#include <sstream>

namespace UIT
{
    template <class T>
    concept Printable = requires(std::stringstream& os, T a)
    {
        os << a;
    };
}

#endif // _UNIQUEINTERVALTREE_CONCEPTS_HPP_