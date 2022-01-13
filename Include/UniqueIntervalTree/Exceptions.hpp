// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALEXCEPTIONS_EXCEPTIONS_HPP_
#define _UNIQUEINTERVALEXCEPTIONS_EXCEPTIONS_HPP_

#include <exception>
#include <concepts>

namespace UIT
{
    template <class K>
    requires std::equality_comparable<K> && std::totally_ordered<K>
    class InvalidRangeException : public std::exception
    {
        private:
            K range_start;
            K range_end;

        public:
            InvalidRangeException(const K& range_start, const K& range_end)
            {
                this->range_start = range_start;
                this->range_end = range_end;
            }

            const char* what() const throw ()
            {
                if (this->range_end < this->range_start)
                {
                    return "Range end value cannot be lower than start value";
                }
                if (this->range_end == this->range_start)
                {
                    return "Range must start and end at different values: [{}, {})";
                }
            }
    };

    class PointNotFound : public std::exception
    {
        public:
            const char* what() const throw ()
            {
                return "Point was not found in the tree";
            }
    };

    class RangeNotFound : public std::exception
    {
        public:
            const char* what() const throw ()
            {
                return "Range was not found in the tree";
            }
    };

    class RangeExists : public std::exception
    {
        public:
            const char* what() const throw ()
            {
                return "Range overlaps with an existing range in the tree";
            }
    };
}

#endif // _UNIQUEINTERVALEXCEPTIONS_EXCEPTIONS_HPP_
