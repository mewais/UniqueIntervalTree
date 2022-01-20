// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_TREE_HPP_
#define _UNIQUEINTERVALTREE_TREE_HPP_

#include <memory>
#include <string>

#include "Utils.hpp"
#include "Node.hpp"
#include "Exceptions.hpp"

namespace UIT
{
    template <class K, class V, class Allocator = std::allocator<Node<K, V>>>
    requires std::equality_comparable<K> && std::totally_ordered<K>
    class Tree
    {
        public:
            Allocator node_allocator;
            Node<K, V>* root;

            Tree(const Allocator& node_allocator = Allocator()) : node_allocator(node_allocator), root(nullptr) {}

        private:
            static void OrderCheck(const K& range_start, const K& range_end)
            {
                if (uit_unlikely(range_end < range_start) || uit_unlikely(range_end == range_start))
                {
                    throw InvalidRangeException(range_start, range_end);
                }
            }

            static void UpdateAllMax(Node<K, V>* leaf)
            {
                leaf->UpdateMax();
                UpdateAllMax(leaf->GetParent());
            }

            // Recursive functions
            bool Overlapping(const K& range_start, const K& range_end, const Node<K, V>* node)
            {
                if (node == nullptr)
                {
                    return false;
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    return true;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Overlapping(range_start, range_end, node->left_child);
                }
                return this->Overlapping(range_start, range_end, node->right_child);
            }

            bool Has(const K& point, const Node<K, V>* node) const
            {
                if (node == nullptr)
                {
                    return false;
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    return true;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Has(point, node->left_child);
                }
                return this->Has(point, node->right_child);
            }

            bool Has(const K& range_start, const K& range_end, const Node<K, V>* node) const
            {
                if (node == nullptr)
                {
                    return false;
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    return true;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Has(range_start, range_end, node->left_child);
                }
                return this->Has(range_start, range_end, node->right_child);
            }

            V& Access(const K& point, Node<K, V>* node)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw PointNotFound(point);
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    return node->value;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child);
                }
                return this->Access(point, node->right_child);
            }

            V& Access(const K& range_start, const K& range_end, Node<K, V>* node)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    return node->value;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child);
                }
                return this->Access(range_start, range_end, node->right_child);
            }

            V& Access(const K& point, Node<K, V>* node, K& found_range_start, K& found_range_end)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw PointNotFound(point);
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    return node->value;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child, found_range_start, found_range_end);
                }
                return this->Access(point, node->right_child, found_range_start, found_range_end);
            }

            V& Access(const K& range_start, const K& range_end, Node<K, V>* node, K& found_range_start,
                      K& found_range_end)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    return node->value;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child, found_range_start, found_range_end);
                }
                return this->Access(range_start, range_end, node->right_child, found_range_start, found_range_end);
            }

            const V& Access(const K& point, Node<K, V>* node) const
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw PointNotFound(point);
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    return node->value;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child);
                }
                return this->Access(point, node->right_child);
            }

            const V& Access(const K& range_start, const K& range_end, Node<K, V>* node) const
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    return node->value;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child);
                }
                return this->Access(range_start, range_end, node->right_child);
            }

            const V& Access(const K& point, Node<K, V>* node, K& found_range_start, K& found_range_end) const
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw PointNotFound(point);
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    return node->value;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child, found_range_start, found_range_end);
                }
                return this->Access(point, node->right_child, found_range_start, found_range_end);
            }

            const V& Access(const K& range_start, const K& range_end, Node<K, V>* node, K& found_range_start,
                            K& found_range_end) const
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    return node->value;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child, found_range_start, found_range_end);
                }
                return this->Access(range_start, range_end, node->right_child, found_range_start, found_range_end);
            }

            bool Access(const K& point, Node<K, V>* node, V*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child, ret);
                }
                return this->Access(point, node->right_child, ret);
            }

            bool Access(const K& range_start, const K& range_end, Node<K, V>* node, V*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child, ret);
                }
                return this->Access(range_start, range_end, node->right_child, ret);
            }

            bool Access(const K& point, Node<K, V>* node, K& found_range_start, K& found_range_end, V*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child, found_range_start, found_range_end, ret);
                }
                return this->Access(point, node->right_child, found_range_start, found_range_end, ret);
            }

            bool Access(const K& range_start, const K& range_end, Node<K, V>* node, K& found_range_start,
                        K& found_range_end, V*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child, found_range_start, found_range_end, ret);
                }
                return this->Access(range_start, range_end, node->right_child, found_range_start, found_range_end, ret);
            }

            bool Access(const K& point, Node<K, V>* node, V const*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child, ret);
                }
                return this->Access(point, node->right_child, ret);
            }

            bool Access(const K& range_start, const K& range_end, Node<K, V>* node, V const*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child, ret);
                }
                return this->Access(range_start, range_end, node->right_child, ret);
            }

            bool Access(const K& point, Node<K, V>* node, K& found_range_start, K& found_range_end, V const*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (point >= node->range_start && point < node->range_end)
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > point)
                {
                    return this->Access(point, node->left_child, found_range_start, found_range_end, ret);
                }
                return this->Access(point, node->right_child, found_range_start, found_range_end, ret);
            }

            bool Access(const K& range_start, const K& range_end, Node<K, V>* node, K& found_range_start,
                        K& found_range_end, V const*& ret)
            {
                if (uit_unlikely(node == nullptr))
                {
                    return false;
                }
                if (node->IsOverlapping(range_start, range_end))
                {
                    found_range_start = node->range_start;
                    found_range_end = node->range_end;
                    ret = &node->value;
                    return true;
                }
                if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Access(range_start, range_end, node->left_child, found_range_start, found_range_end, ret);
                }
                return this->Access(range_start, range_end, node->right_child, found_range_start, found_range_end, ret);
            }

            Node<K, V>* Insert(const K& range_start, const K& range_end, V& value, Node<K, V>*& node, Node<K, V>* parent = nullptr)
            {
                bool conflict = false;
                static bool left_left = false;
                static bool left_right = false;
                static bool right_right = false;
                static bool right_left = false;

                // Insert somewhere
                if (node == nullptr)
                {
                    if (uit_unlikely(this->root == nullptr))
                    {
                        node = std::allocator_traits<Allocator>::allocate(this->node_allocator, 1);
                        std::allocator_traits<Allocator>::construct(this->node_allocator, node, range_start, range_end,
                                                                    value, range_end, parent, Color::BLACK);
                    }
                    else
                    {
                        node = std::allocator_traits<Allocator>::allocate(this->node_allocator, 1);
                        std::allocator_traits<Allocator>::construct(this->node_allocator, node, range_start, range_end,
                                                                    value, range_end, parent);
                    }
                    return node;
                }

                if (uit_unlikely(node->IsOverlapping(range_start, range_end)))
                {
                    throw RangeExists(range_start, range_end);
                }
                if (range_start < node->range_start)
                {
                    node->left_child = this->Insert(range_start, range_end, value, node->left_child, node);
                    node->left_child->parent = node;
                    if (node != this->root && node->color == Color::RED && node->left_child->color == Color::RED)
                    {
                        conflict = true;
                    }
                }
                else
                {
                    node->right_child = this->Insert(range_start, range_end, value, node->right_child, node);
                    node->right_child->parent = node;
                    if (node != this->root && node->color == Color::RED && node->right_child->color == Color::RED)
                    {
                        conflict = true;
                    }
                }

                if (left_left)
                {
                    node = node->RotateLeft();
                    node->color = Color::BLACK;
                    node->left_child->color = Color::RED;
                    left_left = false;
                }
                else if (right_right)
                {
                    node = node->RotateRight();
                    node->color = Color::BLACK;
                    node->right_child->color = Color::RED;
                    right_right = false;
                }
                else if (right_left)
                {
                    node->right_child = node->right_child->RotateRight();
                    node->right_child->parent = node;
                    node = node->RotateLeft();
                    node->color = Color::BLACK;
                    node->left_child->color = Color::RED;
                    right_left = false;
                }
                else if (left_right)
                {
                    node->left_child = node->left_child->RotateLeft();
                    node->left_child->parent = node;
                    node = node->RotateRight();
                    node->color = Color::BLACK;
                    node->right_child->color = Color::RED;
                    left_right = false;
                }

                if (conflict)
                {
                    if(node->IsRightChild())
                    {
                        if(node->GetSibling() == nullptr || node->GetSibling()->color == Color::BLACK)
                        {
                            if(node->left_child != nullptr && node->left_child->color == Color::RED)
                            {
                                right_left = true;
                            }
                            else if(node->right_child != nullptr && node->right_child->color == Color::RED)
                            {
                                left_left = true;
                            }
                        }
                        else
                        {
                            node->GetSibling()->color = Color::BLACK;
                            node->color = Color::BLACK;
                            if(node->parent != this->root)
                            {
                                node->parent->color = Color::RED;
                            }
                        }
                    }
                    else
                    {
                        if(node->GetSibling() == nullptr || node->GetSibling()->color == Color::BLACK)
                        {
                            if(node->left_child != nullptr && node->left_child->color == Color::RED)
                            {
                                right_right = true;
                            }
                            else if(node->right_child != nullptr && node->right_child->color == Color::RED)
                            {
                                left_right = true;
                            }
                        }
                        else
                        {
                            node->GetSibling()->color = Color::BLACK;
                            node->color = Color::BLACK;
                            if(node->parent != this->root)
                            {
                                node->parent->color = Color::RED;
                            }
                        }
                    }
                }

                // Update max
                node->UpdateMax();

                return node;
            }

            Node<K, V>* Insert(Node<K, V>* insert_node, Node<K, V>*& node, Node<K, V>* parent = nullptr)
            {
                bool conflict = false;
                static bool left_left = false;
                static bool left_right = false;
                static bool right_right = false;
                static bool right_left = false;

                // Insert somewhere
                if (node == nullptr)
                {
                    insert_node->parent = parent;
                    if (uit_unlikely(this->root == nullptr))
                    {
                        insert_node->color = Color::BLACK;
                    }
                    else
                    {
                        insert_node->color = Color::RED;
                    }
                    node = insert_node;
                    return node;
                }

                if (uit_unlikely(node->IsOverlapping(insert_node->range_start, insert_node->range_end)))
                {
                    throw RangeExists(insert_node->range_start, insert_node->range_end);
                }
                if (insert_node->range_start < node->range_start)
                {
                    node->left_child = this->Insert(insert_node, node->left_child, node);
                    node->left_child->parent = node;
                    if (node != this->root && node->color == Color::RED && node->left_child->color == Color::RED)
                    {
                        conflict = true;
                    }
                }
                else
                {
                    node->right_child = this->Insert(insert_node, node->right_child, node);
                    node->right_child->parent = node;
                    if (node != this->root && node->color == Color::RED && node->right_child->color == Color::RED)
                    {
                        conflict = true;
                    }
                }

                if (left_left)
                {
                    node = node->RotateLeft();
                    node->color = Color::BLACK;
                    node->left_child->color = Color::RED;
                    left_left = false;
                }
                else if (right_right)
                {
                    node = node->RotateRight();
                    node->color = Color::BLACK;
                    node->right_child->color = Color::RED;
                    right_right = false;
                }
                else if (right_left)
                {
                    node->right_child = node->right_child->RotateRight();
                    node->right_child->parent = node;
                    node = node->RotateLeft();
                    node->color = Color::BLACK;
                    node->left_child->color = Color::RED;
                    right_left = false;
                }
                else if (left_right)
                {
                    node->left_child = node->left_child->RotateLeft();
                    node->left_child->parent = node;
                    node = node->RotateRight();
                    node->color = Color::BLACK;
                    node->right_child->color = Color::RED;
                    left_right = false;
                }

                if (conflict)
                {
                    if(node->IsRightChild())
                    {
                        if(node->GetSibling() == nullptr || node->GetSibling()->color == Color::BLACK)
                        {
                            if(node->left_child != nullptr && node->left_child->color == Color::RED)
                            {
                                right_left = true;
                            }
                            else if(node->right_child != nullptr && node->right_child->color == Color::RED)
                            {
                                left_left = true;
                            }
                        }
                        else
                        {
                            node->GetSibling()->color = Color::BLACK;
                            node->color = Color::BLACK;
                            if(node->parent != this->root)
                            {
                                node->parent->color = Color::RED;
                            }
                        }
                    }
                    else
                    {
                        if(node->GetSibling() == nullptr || node->GetSibling()->color == Color::BLACK)
                        {
                            if(node->left_child != nullptr && node->left_child->color == Color::RED)
                            {
                                right_right = true;
                            }
                            else if(node->right_child != nullptr && node->right_child->color == Color::RED)
                            {
                                left_right = true;
                            }
                        }
                        else
                        {
                            node->GetSibling()->color = Color::BLACK;
                            node->color = Color::BLACK;
                            if(node->parent != this->root)
                            {
                                node->parent->color = Color::RED;
                            }
                        }
                    }
                }

                // Update max
                node->UpdateMax();

                return node;
            }

            void GrowEnd(const K& range_start, const K& range_end, const K& new_range_end, Node<K, V>* node)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->Same(range_start, range_end))
                {
                    node->range_end = new_range_end;
                }
                else if (node->left_child && node->max > range_start)
                {
                    this->GrowEnd(range_start, range_end, new_range_end, node->left_child);
                }
                else
                {
                    this->GrowEnd(range_start, range_end, new_range_end, node->right_child);
                }
                node->UpdateMax();
            }

            void RemoveRecolor(Node<K, V>* node)
            {
                if (node == this->root)
                {
                    return;
                }

                Node<K, V>* sibling = node->Sibling();
                Node<K, V>* parent = node->parent;

                if (sibling == nullptr)
                {
                    this->RemoveRecolor(parent);
                }
                else
                {
                    if (sibling->color == Color::RED)
                    {
                        // Sibling red
                        parent->color = Color::RED;
                        sibling->color = Color::BLACK;
                        if (sibling->IsLeftChild())
                        {
                            parent = parent->RotateRight();
                        }
                        else
                        {
                            parent = parent->RotateLeft();
                        }
                        this->RemoveRecolor(parent);
                    }
                    else
                    {
                        // Sibling black
                        if (sibling->right_child->color == Color::RED || sibling->left_child->color == Color::RED)
                        {
                            // at least 1 red children
                            if (sibling->left_child != nullptr and sibling->left_child->color == Color::RED)
                            {
                                if (sibling->IsLeftChild())
                                {
                                    sibling->left_child->color = sibling->color;
                                    sibling->color = parent->color;
                                    parent = parent->RotateRight();
                                } else {
                                    sibling->left_child->color = parent->color;
                                    sibling = sibling->RotateRight();
                                    parent = parent->RotateLeft();
                                }
                            }
                            else
                            {
                                if (sibling->IsLeftChild())
                                {
                                    sibling->right_child->color = parent->color;
                                    sibling = sibling->RotateLeft();
                                    parent = parent->RotateRight();
                                }
                                else
                                {
                                    sibling->right_child->color = sibling->color;
                                    sibling->color = parent->color;
                                    parent = parent->RotateLeft();
                                }
                            }
                            parent->color = Color::BLACK;
                        }
                        else
                        {
                            // 2 black children
                            sibling->color = Color::RED;
                            if (parent->color == Color::BLACK)
                            {
                                this->RemoveRecolor(parent);
                            }
                            else
                            {
                                parent->color = Color::BLACK;
                            }
                        }
                    }
                }
            }

            void Delete(Node<K, V>* node)
            {
                Node<K, V>* parent = node->parent;
                Node<K, V>* sibling = node->Sibling();
                Node<K, V>* replacement;
                if (node->left_child == nullptr && node->right_child == nullptr)
                {
                    replacement = nullptr;
                }
                else if (node->right_child == nullptr)
                {
                    replacement = node->left_child;
                }
                else if (node->left_child == nullptr)
                {
                    replacement = node->right_child;
                }
                else
                {
                    // 1. Deleting a node with two children
                    // 1.1. Get the min leaf node
                    replacement = node;
                    while (replacement->left_child)
                    {
                        replacement = replacement->left_child;
                    }
                }

                bool double_black = ((replacement == nullptr || replacement->color == Color::BLACK) &&
                                     (node->color == Color::BLACK));

                if (node->left_child == nullptr && node->right_child == nullptr)
                {
                    // Leaf node, no children
                    if (node == this->root)
                    {
                        this->root = nullptr;
                    }
                    else
                    {
                        if (double_black)
                        {
                            this->RemoveRecolor(node);
                        }
                        else
                        {
                            if (sibling != nullptr)
                            {
                                sibling->color = Color::RED;
                            }
                        }

                        // Delete node from parent
                        if (node->IsLeftChild())
                        {
                            parent->left_child = nullptr;
                        }
                        else
                        {
                            parent->right_child = nullptr;
                        }
                        UpdateAllMax(parent);
                    }
                    // Delete node
                    std::allocator_traits<Allocator>::destroy(this->node_allocator, node);
                    std::allocator_traits<Allocator>::deallocate(this->node_allocator, node, 1);
                }
                else if (node->right_child == nullptr || node->left_child == nullptr)
                {
                    // 1 child only
                    // Connect replacement and parent
                    if (node != this->root)
                    {
                        if (node->IsLeftChild())
                        {
                            parent->left_child = replacement;
                        }
                        else
                        {
                            parent->right_child = replacement;
                        }
                        UpdateAllMax(parent);
                    }
                    else
                    {
                        this->root = replacement;
                    }
                    replacement->parent = parent;
                    // Delete node
                    std::allocator_traits<Allocator>::destroy(this->node_allocator, node);
                    std::allocator_traits<Allocator>::deallocate(this->node_allocator, node, 1);
                    // Recolor
                    if (double_black)
                    {
                        this->RemoveRecolor(replacement);
                    }
                    else
                    {
                        replacement->color = Color::BLACK;
                    }
                }
                else
                {
                    // 2 Children
                    if (node != this->root)
                    {
                        if (node->IsLeftChild())
                        {
                            parent->left_child = replacement;
                        }
                        else
                        {
                            parent->right_child = replacement;
                        }
                    }
                    else
                    {
                        this->root = replacement;
                    }
                    Node<K, V>* tmp_left_child = replacement->left_child;
                    Node<K, V>* tmp_right_child = replacement->right_child;
                    Node<K, V>* tmp_parent = replacement->parent;
                    replacement->left_child = node->left_child;
                    replacement->right_child = node->right_child;
                    replacement->parent = parent;
                    UpdateAllMax(replacement);
                    node->left_child = tmp_left_child;
                    node->right_child = tmp_right_child;
                    node->left_child = tmp_parent;
                    // Delete node
                    this->Delete(node);
                }
            }

            void Delete(const K& range_start, const K& range_end, Node<K, V>* node)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->Same(range_start, range_end))
                {
                    this->Delete(node);
                }
                else if (node->left_child && node->left_child->max > range_start)
                {
                    this->Delete(range_start, range_end, node->left_child);
                }
                else
                {
                    this->Delete(range_start, range_end, node->right_child);
                }
            }

            void Remove(Node<K, V>* node)
            {
                Node<K, V>* parent = node->parent;
                Node<K, V>* sibling = node->Sibling();
                Node<K, V>* replacement;
                if (node->left_child == nullptr && node->right_child == nullptr)
                {
                    replacement = nullptr;
                }
                else if (node->right_child == nullptr)
                {
                    replacement = node->left_child;
                }
                else if (node->left_child == nullptr)
                {
                    replacement = node->right_child;
                }
                else
                {
                    // 1. Deleting a node with two children
                    // 1.1. Get the min leaf node
                    replacement = node;
                    while (replacement->left_child)
                    {
                        replacement = replacement->left_child;
                    }
                }

                bool double_black = ((replacement == nullptr || replacement->color == Color::BLACK) &&
                                     (node->color == Color::BLACK));

                if (node->left_child == nullptr && node->right_child == nullptr)
                {
                    // Leaf node, no children
                    if (node == this->root)
                    {
                        this->root = nullptr;
                    }
                    else
                    {
                        if (double_black)
                        {
                            this->RemoveRecolor(node);
                        }
                        else
                        {
                            if (sibling != nullptr)
                            {
                                sibling->color = Color::RED;
                            }
                        }

                        // Remove node from parent
                        if (node->IsLeftChild())
                        {
                            parent->left_child = nullptr;
                        }
                        else
                        {
                            parent->right_child = nullptr;
                        }
                        UpdateAllMax(parent);
                    }
                    // Remove node
                    node->parent = nullptr;
                    node->right_child = nullptr;
                    node->left_child = nullptr;
                }
                else if (node->right_child == nullptr || node->left_child == nullptr)
                {
                    // 1 child only
                    // Connect replacement and parent
                    if (node != this->root)
                    {
                        if (node->IsLeftChild())
                        {
                            parent->left_child = replacement;
                        }
                        else
                        {
                            parent->right_child = replacement;
                        }
                        UpdateAllMax(parent);
                    }
                    else
                    {
                        this->root = replacement;
                    }
                    replacement->parent = parent;
                    // Remove node
                    node->parent = nullptr;
                    node->right_child = nullptr;
                    node->left_child = nullptr;
                    // Recolor
                    if (double_black)
                    {
                        this->RemoveRecolor(replacement);
                    }
                    else
                    {
                        replacement->color = Color::BLACK;
                    }
                }
                else
                {
                    // 2 Children
                    if (node != this->root)
                    {
                        if (node->IsLeftChild())
                        {
                            parent->left_child = replacement;
                        }
                        else
                        {
                            parent->right_child = replacement;
                        }
                    }
                    else
                    {
                        this->root = replacement;
                    }
                    Node<K, V>* tmp_left_child = replacement->left_child;
                    Node<K, V>* tmp_right_child = replacement->right_child;
                    Node<K, V>* tmp_parent = replacement->parent;
                    replacement->left_child = node->left_child;
                    replacement->right_child = node->right_child;
                    replacement->parent = parent;
                    UpdateAllMax(replacement);
                    node->left_child = tmp_left_child;
                    node->right_child = tmp_right_child;
                    node->left_child = tmp_parent;
                    // Remove node
                    this->Remove(node);
                }
            }

            Node<K, V>* Remove(const K& range_start, const K& range_end, Node<K, V>* node)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->Same(range_start, range_end))
                {
                    this->Remove(node);
                    return node;
                }
                else if (node->left_child && node->left_child->max > range_start)
                {
                    return this->Remove(range_start, range_end, node->left_child);
                }
                else
                {
                    return this->Remove(range_start, range_end, node->right_child);
                }
            }

            void ShrinkEnd(const K& range_start, const K& range_end, const K& new_range_end, Node<K, V>* node)
            {
                if (uit_unlikely(node == nullptr))
                {
                    throw RangeNotFound(range_start, range_end);
                }
                if (node->Same(range_start, range_end))
                {
                    node->range_end = new_range_end;
                }
                else if (node->left_child && node->max > range_start)
                {
                    this->ShrinkEnd(range_start, range_end, new_range_end, node->left_child);
                }
                else
                {
                    this->ShrinkEnd(range_start, range_end, new_range_end, node->right_child);
                }
                node->UpdateMax();
            }

            std::string ToString(const std::string& prefix, Node<K, V>* node, bool left) const
            {
                std::string tree = "";
                if (node)
                {
                    tree = prefix;
                    tree += left? "├──" : "└──";
                    tree += node->color == Color::BLACK? "B: " : "R: ";
                    tree += node->ToString();
                    tree += "\n";

                    std::string new_prefix = prefix;
                    new_prefix += left? "│   " : "    ";
                    tree += this->ToString(new_prefix, node->left_child, true);
                    tree += this->ToString(new_prefix, node->right_child, false);
                }
                return tree;
            }

        public:
            V& Access(const K& point)
            {
                return this->Access(point, this->root);
            }

            V& Access(const K& range_start, const K& range_end)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                return this->Access(range_start, range_end, this->root);
            }

            V& Access(const K& point, K& found_range_start, K& found_range_end)
            {
                return this->Access(point, this->root, found_range_start, found_range_end);
            }

            V& Access(const K& range_start, const K& range_end, K& found_range_start, K& found_range_end)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                return this->Access(range_start, range_end, this->root, found_range_start, found_range_end);
            }

            const V& Access(const K& point) const
            {
                return this->Access(point, this->root);
            }

            const V& Access(const K& range_start, const K& range_end) const
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                return this->Access(range_start, range_end, this->root);
            }

            const V& Access(const K& point, K& found_range_start, K& found_range_end) const
            {
                return this->Access(point, this->root, found_range_start, found_range_end);
            }

            const V& Access(const K& range_start, const K& range_end, K& found_range_start, K& found_range_end) const
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                return this->Access(range_start, range_end, this->root, found_range_start, found_range_end);
            }

            bool Access(const K& point, V*& ret)
            {
                return this->Access(point, this->root, ret);
            }

            bool Access(const K& range_start, const K& range_end, V*& ret)
            {
                return this->Access(range_start, range_end, this->root, ret);
            }

            bool Access(const K& point, K& found_range_start, K& found_range_end, V*& ret)
            {
                return this->Access(point, this->root, found_range_start, found_range_end, ret);
            }

            bool Access(const K& range_start, const K& range_end, K& found_range_start, K& found_range_end, V*& ret)
            {
                return this->Access(range_start, range_end, this->root, found_range_start, found_range_end, ret);
            }

            bool Access(const K& point, V const*& ret)
            {
                return this->Access(point, this->root, ret);
            }

            bool Access(const K& range_start, const K& range_end, V const*& ret)
            {
                return this->Access(range_start, range_end, this->root, ret);
            }

            bool Access(const K& point, K& found_range_start, K& found_range_end, V const*& ret)
            {
                return this->Access(point, this->root, found_range_start, found_range_end, ret);
            }

            bool Access(const K& range_start, const K& range_end, K& found_range_start, K& found_range_end, V const*& ret)
            {
                return this->Access(range_start, range_end, this->root, found_range_start, found_range_end, ret);
            }

            bool Has(const K& point) const
            {
                return this->Has(point, this->root);
            }

            bool Has(const K& range_start, const K& range_end) const
            {
                return this->Has(range_start, range_end, this->root);
            }

            void Insert(const K& range_start, const K& range_end, V& value)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                this->Insert(range_start, range_end, value, this->root);
            }

            void GrowEnd(const K& range_start, const K& range_end, const K& new_range_end)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                Tree<K, V, Allocator>::OrderCheck(range_end, new_range_end);
                if (uit_unlikely(this->Overlapping(range_end, new_range_end, this->root)))
                {
                    throw RangeExists(range_start, range_end);
                }
                this->GrowEnd(range_start, range_end, new_range_end, this->root);
            }

            void GrowStart(const K& range_start, const K& range_end, const K& new_range_start)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                Tree<K, V, Allocator>::OrderCheck(new_range_start, range_end);
                Node<K, V>* to_modify_node = this->Remove(range_start, range_end, this->root);
                to_modify_node->range_start = new_range_start;
                this->Insert(to_modify_node, this->root);
            }

            void Delete(const K& range_start, const K& range_end)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                this->Delete(range_start, range_end, this->root);
            }

            void ShrinkEnd(const K& range_start, const K& range_end, const K& new_range_end)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                Tree<K, V, Allocator>::OrderCheck(new_range_end, range_end);
                this->ShrinkEnd(range_start, range_end, new_range_end, this->root);
            }

            void ShrinkStart(const K& range_start, const K& range_end, const K& new_range_start)
            {
                Tree<K, V, Allocator>::OrderCheck(range_start, range_end);
                Tree<K, V, Allocator>::OrderCheck(new_range_start, range_end);
                Node<K, V>* to_modify_node = this->Remove(range_start, range_end, this->root);
                to_modify_node->range_start = new_range_start;
                this->Insert(to_modify_node, this->root);
            }

            std::string ToString() const
            {
                return this->ToString("", this->root, false);
            }
    };
}

#endif // _UNIQUEINTERVALTREE_TREE_HPP_
