// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_EXCEPTIONS_HPP_
#define _UNIQUEINTERVALTREE_EXCEPTIONS_HPP_

#include <sstream>
#include <string>
#include <exception>
#include <concepts>

#include "Concepts.hpp"

namespace UIT
{
    template <class K>
    requires std::equality_comparable<K> && std::totally_ordered<K> && Printable<K>
    class InvalidRangeException : public std::exception
    {
        private:
            K range_start;
            K range_end;
            std::stringstream ss;

        public:
            InvalidRangeException(const K& range_start, const K& range_end)
            {
                this->range_start = range_start;
                this->range_end = range_end;
            }

            const char* what() throw ()
            {
                if (this->range_end < this->range_start)
                {
                    this->ss << "Range end value cannot be lower than start value: [" << this->range_start << ", " <<
                                this->range_end << ")";
                    return this->ss.str().c_str();
                }
                if (this->range_end == this->range_start)
                {
                    this->ss << "Range must start and end at different values: [" << this->range_start << ", " <<
                                this->range_end << ")";
                    return this->ss.str().c_str();
                }
            }
    };

    template <class K>
    requires Printable<K>
    class PointNotFound : public std::exception
    {
        private:
            K point;
            std::stringstream ss;

        public:
            PointNotFound(const K& point)
            {
                this->point = point;
            }

            const char* what() throw ()
            {
                this->ss << "Point " << this->point << " was not found in the tree";
                return this->ss.str().c_str();
            }
    };

    template <class K>
    requires Printable<K>
    class RangeNotFound : public std::exception
    {
        private:
            K range_start;
            K range_end;
            std::stringstream ss;

        public:
            RangeNotFound(const K& range_start, const K& range_end)
            {
                this->range_start = range_start;
                this->range_end = range_end;
            }

            const char* what() throw ()
            {
                this->ss << "Range [" << this->range_start << ", " << this->range_end << ") was not found in the tree";
                return this->ss.str().c_str();
            }
    };

    template <class K>
    requires Printable<K>
    class RangeExists : public std::exception
    {
        private:
            K range_start;
            K range_end;
            std::stringstream ss;

        public:
            RangeExists(const K& range_start, const K& range_end)
            {
                this->range_start = range_start;
                this->range_end = range_end;
            }

            const char* what() throw ()
            {
                this->ss << "Range [" << this->range_start << ", " << this->range_end <<
                            ") overlaps with an existing range in the tree";
                return this->ss.str().c_str();
            }
    };
}

#endif // _UNIQUEINTERVALTREE_EXCEPTIONS_HPP_
