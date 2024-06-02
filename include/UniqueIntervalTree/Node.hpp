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

    template <typename K, typename V>
    class Node
    {
        static_assert(is_equality_comparable<K>::value, "Key type must be totally ordered");
        static_assert(is_printable<K>::value, "Key type must be printable");
        static_assert(std::is_move_constructible<V>::value || std::is_copy_constructible<V>::value ||
                      std::is_default_constructible<V>::value || std::is_fundamental<V>::value, 
                      "Value type must be fundamental, or default constructible, or copy or move constructible");

        public:
            K range_start;
            K range_end;
            V range_value;
            K max;
            Node* parent;
            Color color;
            Node* left_child;
            Node* right_child;

            // Constructor for fundamental types
            template <typename T = V>
            Node(const K& range_start, const K& range_end, T& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr,
                 typename std::enable_if<std::is_fundamental<T>::value, int>::type = 0)
                : range_start(range_start), range_end(range_end), range_value(range_value), max(max), parent(parent), color(color),
                  left_child(left_child), right_child(right_child)
            {
            }

            // Constructor for moveable types
            template <typename T = V>
            Node(const K& range_start, const K& range_end, T& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr,
                 typename std::enable_if<std::is_move_constructible<T>::value && !std::is_fundamental<T>::value, int>::type = 0)
                : range_start(range_start), range_end(range_end), range_value(std::move(range_value)), max(max), parent(parent), color(color),
                  left_child(left_child), right_child(right_child)
            {
            }

            // Constructor for copyable types (but not moveable)
            template <typename T = V>
            Node(const K& range_start, const K& range_end, const T& range_value, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr,
                 typename std::enable_if<std::is_copy_constructible<T>::value && !std::is_move_constructible<T>::value, int>::type = 0)
                : range_start(range_start), range_end(range_end), range_value(range_value), max(max), parent(parent), color(color),
                  left_child(left_child), right_child(right_child)
            {
            }

            // Constructor for default constructible types
            template <typename T = V>
            Node(const K& range_start, const K& range_end, const K& max, Node<K, V>* parent = nullptr,
                 Color color = Color::RED, Node<K, V>* left_child = nullptr, Node<K, V>* right_child = nullptr,
                 typename std::enable_if<std::is_default_constructible<T>::value, int>::type = 0)
                : range_start(range_start), range_end(range_end), max(max), parent(parent), color(color),
                  left_child(left_child), right_child(right_child)
            {
            }

            // Delete move and copy constructors and assignment operators
            Node(const Node<K, V>&) = delete;
            Node(Node<K, V>&&) = delete;
            Node<K, V>& operator=(const Node<K, V>&) = delete;
            Node<K, V>& operator=(Node<K, V>&&) = delete;

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
