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

            // Fundamentals
            Node(const K& range_start, const K& range_end, V& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr)
                 requires std::is_fundamental_v<V> : range_start(range_start), range_end(range_end),
                 range_value(range_value), max(max), parent(parent), color(color), left_child(left_child),
                 right_child(right_child)
            {
            }

            // Moveables
            Node(const K& range_start, const K& range_end, V& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr)
                 requires MoveConstructible<V> && (!std::is_fundamental_v<V>) : range_start(range_start),
                 range_end(range_end), range_value(std::move(range_value)), max(max), parent(parent), color(color),
                 left_child(left_child), right_child(right_child)
            {
            }

            // Copyables
            Node(const K& range_start, const K& range_end, const V& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr)
                 requires OnlyCopyConstructible<V> : range_start(range_start), range_end(range_end),
                 range_value(range_value), max(max), parent(parent), color(color), left_child(left_child),
                 right_child(right_child)
            {
            }

            // Default constructibles
            Node(const K& range_start, const K& range_end, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr)
                 requires std::is_default_constructible_v<V> : range_start(range_start), range_end(range_end), max(max),
                 parent(parent), color(color), left_child(left_child), right_child(right_child)
            {
            }

            // Move assignment
            Node& operator=(Node&& other) noexcept requires std::is_fundamental_v<V>
            {
                this->range_start = other.range_start;
                this->range_end = other.range_end;
                this->range_value = other.range_value;
                this->max = other.max;
                this->parent = other.parent;
                this->color = other.color;
                this->left_child = other.left_child;
                this->right_child = other.right_child;
                return *this;
            }

            Node& operator=(Node&& other) noexcept requires MoveAssignable<V>
            {
                this->range_start = other.range_start;
                this->range_end = other.range_end;
                this->range_value = std::move(other.range_value);
                this->max = other.max;
                this->parent = other.parent;
                this->color = other.color;
                this->left_child = other.left_child;
                this->right_child = other.right_child;
                return *this;
            }

            Node& operator=(Node&& other) noexcept requires OnlyCopyAssignable<V>
            {
                this->range_start = other.range_start;
                this->range_end = other.range_end;
                this->range_value = other.range_value;
                this->max = other.max;
                this->parent = other.parent;
                this->color = other.color;
                this->left_child = other.left_child;
                this->right_child = other.right_child;
                return *this;
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
                if (this->parent == nullptr)
                {
                    return false;
                }
                return this == this->parent->left_child;
            }

            bool IsRightChild() const
            {
                if (this->parent == nullptr)
                {
                    return false;
                }
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
