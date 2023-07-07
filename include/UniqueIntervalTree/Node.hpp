// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_NODE_HPP_
#define _UNIQUEINTERVALTREE_NODE_HPP_

#include <cstdint>
#include <algorithm>
#include <sstream>

#include "Concepts.hpp"

namespace UIT
{
    enum class Color : uint8_t
    {
        RED,
        BLACK,
    };

    template <KeyType K, ValueType V>
    class Node
    {
        public:
            K range_start;
            K range_end;
            V range_value;
            K max;
            Node* parent;
            Color color;
            Node* left_child;
            Node* right_child;

            Node(const K& range_start, const K& range_end, V& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr)
                 requires Buildable<V> : range_start(range_start), range_end(range_end), max(max), parent(parent),
                 color(color), left_child(left_child), right_child(right_child)
            {
                if (std::is_move_constructible_v<V>)
                {
                    this->range_value(std::move(range_value));
                }
                else if (std::is_copy_constructible_v<V>)
                {
                    this->range_value(range_value);
                }
                else if (std::is_move_assignable_v<V>)
                {
                    this->range_value = std::move(range_value);
                }
                else if (std::is_copy_assignable_v<V>)
                {
                    this->range_value = range_value;
                }
            }

            Node(const K& range_start, const K& range_end, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr)
                 requires std::is_default_constructible_v<V> : range_start(range_start), range_end(range_end), max(max),
                 parent(parent), color(color), left_child(left_child), right_child(right_child)
            {
            }

            bool IsOverlapping(const K& range_start, const K& range_end) const
            {
                if (range_start < this->range_end && this->range_start < range_end)
                {
                    return true;
                }
                return false;
            }

            bool IsSame(const K& range_start, const K& range_end) const
            {
                if (range_start == this->range_start && range_end == this->range_end)
                {
                    return true;
                }
                return false;
            }

            bool IsLeftChild() const
            {
                return this == this->parent->left_child;
            }

            bool IsRightChild() const
            {
                return this == this->parent->right_child;
            }

            Node<K, V>* GetSibling() const
            {
                if (this->IsLeftChild())
                {
                    return this->parent->right_child;
                }
                return this->parent->left_child;
            }

            void UpdateMax()
            {
                if (this->left_child && this->right_child)
                {
                    this->max = std::max({this->left_child->max, this->right_child->max, this->range_end});
                }
                else if (this->left_child)
                {
                    this->max = std::max(this->left_child->max, this->range_end);
                }
                else if (this->right_child)
                {
                    this->max = std::max(this->right_child->max, this->range_end);
                }
                else
                {
                    this->max = this->range_end;
                }
            }

            std::string ToString(bool addresses) const
            {
                std::stringstream ss;
                ss << (this->color == Color::BLACK? "B: " : "R: ");
                ss << '[' << this->range_start << ", " << this->range_end << ")";
                ss << ", Max: " << this->max;
                if (addresses)
                {
                    ss << ", Parent: " << this->parent;
                    ss << ", LeftChild: " << this->left_child;
                    ss << ", RightChild: " << this->right_child;
                }
                return ss.str();
            }

            // Statics
            static bool IsOverlapping(const K& range1_start, const K& range1_end, const K& range2_start, const K& range2_end)
            {
                if (range1_start < range2_end && range2_start < range1_end)
                {
                    return true;
                }
                return false;
            }

            static bool IsSame(const K& range1_start, const K& range1_end, const K& range2_start, const K& range2_end)
            {
                if (range1_start == range2_start && range1_end == range2_end)
                {
                    return true;
                }
                return false;
            }
    };
}

#endif // _UNIQUEINTERVALTREE_NODE_HPP_
