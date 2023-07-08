// Copyright(c) 2021-present, Mohammad Ewais & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef _UNIQUEINTERVALTREE_ITERATORS_HPP_
#define _UNIQUEINTERVALTREE_ITERATORS_HPP_

#include <iterator>
#include <cstddef>

namespace UIT
{
    // Very useful guide: https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
    template <class T>
    class Iterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;

        private:
            pointer ptr;
            pointer root;

        public:
            Iterator(pointer ptr, pointer root) : ptr(ptr), root(root) {}

            reference operator*() const
            {
                return *this->ptr;
            }
            pointer operator->() const
            {
                return this->ptr;
            }

            Iterator& operator++()
            {
                if (this->ptr->right_child)
                {
                    // From our location, incrementing means going to the leftmost child of the right child
                    this->ptr = this->ptr->right_child;
                    while (this->ptr->left_child)
                    {
                        this->ptr = this->ptr->left_child;
                    }
                }
                else
                {
                    // If the current location has no right child, we need to go up until we find a node that is
                    // the left child of its parent
                    while (this->ptr && this->ptr->IsRightChild())
                    {
                        this->ptr = this->ptr->parent;
                    }
                    if (!this->ptr)
                    {
                        return *this;
                    }
                    this->ptr = this->ptr->parent;
                }
                return *this;
            }

            Iterator& operator--()
            {
                if (!this->ptr)
                {
                    // Initially, this starts as null. We need to go to the rightmost node in the tree
                    this->ptr = this->root;
                    while (this->ptr->right_child)
                    {
                        this->ptr = this->ptr->right_child;
                    }
                }
                else if (this->ptr->left_child)
                {
                    // From our location, decrementing means going to the rightmost child of the left child
                    this->ptr = this->ptr->left_child;
                    while (this->ptr->right_child)
                    {
                        this->ptr = this->ptr->right_child;
                    }
                }
                else
                {
                    // If the current location has no left child, we need to go up until we find a node that is
                    // the right child of its parent
                    while (this->ptr && this->ptr->IsLeftChild())
                    {
                        this->ptr = this->ptr->parent;
                    }
                    if (!this->ptr)
                    {
                        return *this;
                    }
                    this->ptr = this->ptr->parent;
                }
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            Iterator operator--(int)
            {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const Iterator& a, const Iterator& b)
            {
                return a.ptr == b.ptr;
            }
            friend bool operator!=(const Iterator& a, const Iterator& b)
            {
                return a.ptr != b.ptr;
            }
    };
}

#endif // _UNIQUEINTERVALTREE_ITERATORS_HPP_
