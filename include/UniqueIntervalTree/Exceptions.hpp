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
    class InvalidRangeException : public std::exception
    {
        static_assert(is_equality_comparable<K>::value, "Key type must be totally ordered");
        static_assert(is_printable<K>::value, "Key type must be printable");

        private:
            K range_start;
            K range_end;
            std::string str;

        public:
            InvalidRangeException(const K& range_start, const K& range_end)
            {
                std::stringstream ss;
                this->range_start = range_start;
                this->range_end = range_end;
                if (this->range_end < this->range_start)
                {
                    ss << "Range end value cannot be lower than start value: [" << this->range_start << ", " <<
                          this->range_end << ")";
                }
                if (this->range_end == this->range_start)
                {
                    ss << "Range must start and end at different values: [" << this->range_start << ", " <<
                          this->range_end << ")";
                }
                this->str = ss.str();
            }

            const char* what() const noexcept override
            {
                return this->str.c_str();
            }
    };

    template <class K>
    class PointNotFound : public std::exception
    {
        static_assert(is_printable<K>::value, "Key type must be printable");

        private:
            K point;
            std::string str;

        public:
            explicit PointNotFound(const K& point)
            {
                std::stringstream ss;
                this->point = point;
                ss << "Point " << this->point << " was not found in the tree";
                this->str = ss.str();
            }

            const char* what() const noexcept override
            {
                return this->str.c_str();
            }
    };

    template <class K>
    class RangeNotFound : public std::exception
    {
        static_assert(is_printable<K>::value, "Key type must be printable");

        private:
            K range_start;
            K range_end;
            std::string str;

        public:
            RangeNotFound(const K& range_start, const K& range_end)
            {
                std::stringstream ss;
                this->range_start = range_start;
                this->range_end = range_end;
                ss << "Range [" << this->range_start << ", " << this->range_end << ") was not found in the tree";
                this->str = ss.str();
            }

            const char* what() const noexcept override
            {
                return this->str.c_str();
            }
    };

    template <class K>
    class RangeExists : public std::exception
    {
        static_assert(is_printable<K>::value, "Key type must be printable");

        private:
            K range_start;
            K range_end;
            K existing_range_start;
            K existing_range_end;
            std::string str;

        public:
            RangeExists(const K& range_start, const K& range_end, const K& existing_range_start = 0,
                        const K& existing_range_end = 0)
            {
                std::stringstream ss;
                this->range_start = range_start;
                this->range_end = range_end;
                this->existing_range_start = existing_range_start;
                this->existing_range_end = existing_range_end;
                if (this->existing_range_start)
                {
                    ss << "Range [" << this->range_start << ", " << this->range_end <<
                          ") overlaps with existing range [" << this->existing_range_start << ", " <<
                          this->existing_range_end << ") in the tree";
                }
                else
                {
                    ss << "Range [" << this->range_start << ", " << this->range_end <<
                          ") overlaps with an existing range in the tree";
                }
                this->str = ss.str();
            }

            const char* what() const noexcept override
            {
                return this->str.c_str();
            }
    };

    class InternalError : public std::exception
    {
        private:
            std::string error;

        public:
            explicit InternalError(const std::string& error)
            {
                this->error = error;
                this->error += "\n\tPlease submit an issue on: https://github.com/mewais/UniqueIntervalTree/issues";
            }

            const char* what() const noexcept override
            {
                return this->error.c_str();
            }
    };
}

#endif // _UNIQUEINTERVALTREE_EXCEPTIONS_HPP_
