/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:04:18 by sojung            #+#    #+#             */
/*   Updated: 2022/12/13 10:18:44 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "is_integral.hpp"

namespace ft
{
    template <typename T>
    class vector_iterator
    {
    private:
        T *_current;

    public:
        typedef typename iterator_traits<T *>::difference_type difference_type;
        typedef typename iterator_traits<T *>::value_type value_type;
        typedef typename iterator_traits<T *>::pointer pointer;
        typedef typename iterator_traits<T *>::reference reference;
        typedef typename iterator_traits<T *>::iterator_category iterator_category;

        vector_iterator() : _current(NULL) {}
        vector_iterator(const vector_iterator<value_type> &rhs) : _current(rhs.base()) {}
        vector_iterator(pointer ptr) : _current(ptr) {}
        vector_iterator(const reference ref) { _current = &ref; }
        ~vector_iterator() {}
        vector_iterator &operator=(const vector_iterator<T> &rhs)
        {
            if (this != &rhs)
                _current = rhs.base();
            return (*this);
        }
        T *base() const { return (_current); }

        bool operator==(const vector_iterator<T> &rhs) { return (_current == rhs.base()); }
        bool operator==(const vector_iterator<const T> &rhs) const { return (_current == rhs.base()); }
        bool operator!=(const vector_iterator<T> &rhs) { return (_current != rhs.base()); }
        bool operator!=(const vector_iterator<const T> &rhs) const { return (_current != rhs.base()); }
        bool operator>=(const vector_iterator<T> &rhs) { return (_current >= rhs.base()); }
        bool operator>=(const vector_iterator<const T> &rhs) const { return (_current >= rhs.base()); }
        bool operator<=(const vector_iterator<T> &rhs) { return (_current <= rhs.base()); }
        bool operator<=(const vector_iterator<const T> &rhs) const { return (_current <= rhs.base()); }
        bool operator>(const vector_iterator<T> &rhs) { return (_current > rhs.base()); }
        bool operator>(const vector_iterator<const T> &rhs) const { return (_current > rhs.base()); }
        bool operator<(const vector_iterator<T> &rhs) { return (_current < rhs.base()); }
        bool operator<(const vector_iterator<const T> &rhs) const { return (_current < rhs.base()); }

        reference operator*() const { return (*_current); }
        pointer operator->() const { return (_current); }
        reference operator[](const std::size_t n) { return (*(_current + n)); }
        vector_iterator operator+(difference_type n) const { return (vector_iterator(_current + n)); }
        difference_type operator+(const vector_iterator &rhs) const { return (_current + rhs.base()); }
        vector_iterator &operator+=(const int n)
        {
            _current += n;
            return (*this);
        }
        friend vector_iterator operator+(difference_type n, vector_iterator &rhs) { return (vector_iterator(n + rhs.base())); }
        vector_iterator operator-(const int n) const { return (vector_iterator(_current - n)); }
        difference_type operator-(const vector_iterator &rhs) const { return (_current - rhs.base()); }
        vector_iterator &operator-=(const int n)
        {
            _current -= n;
            return (*this);
        }
        friend vector_iterator operator-(difference_type n, vector_iterator &rhs) { return (vector_iterator(n - rhs.base())); }

        vector_iterator &operator++()
        {
            ++_current;
            return (*this);
        }

        vector_iterator operator++(int)
        {
            vector_iterator tmp(*this);
            _current++;
            return (tmp);
        }

        vector_iterator &operator--()
        {
            --_current;
            return (*this);
        }

        vector_iterator operator--(int)
        {
            vector_iterator tmp(*this);
            _current--;
            return (tmp);
        }
    }; // vector_iterator

    template <typename T, typename node_pointer>
    class const_bidirectional_iterator;

    template <typename T, typename node_pointer>
    class bidirectional_iterator
    {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        node_pointer _ptr;

    public:
        bidirectional_iterator() : _ptr(NULL) {}
        bidirectional_iterator(node_pointer ptr) : _ptr(ptr) {}
        bidirectional_iterator(const bidirectional_iterator &rhs) : _ptr(rhs._ptr) {}
        bidirectional_iterator &operator=(const bidirectional_iterator &rhs)
        {
            this->_ptr = rhs._ptr;
            return (*this);
        }
        virtual ~bidirectional_iterator() {}

        operator bidirectional_iterator<const T, node_pointer>() const
        {
            return (bidirectional_iterator<const T, node_pointer>(this->_ptr));
        }

        bidirectional_iterator get_node() const { return (this->_ptr); }

        template <typename T1, typename T2>
        friend class bidirectional_iterator;

        friend bool operator==(const bidirectional_iterator &lhs, const bidirectional_iterator &rhs)
        {
            return (lhs._ptr == rhs._ptr);
        }

        friend bool operator!=(const bidirectional_iterator &lhs, const bidirectional_iterator &rhs)
        {
            return (lhs._ptr != rhs._ptr);
        }

        /*bool operator!=(const bidirectional_iterator &rhs) {
            return (!(*this == rhs));
        }*/

        bidirectional_iterator
        operator++(int)
        {
            bidirectional_iterator tmp = *this;
            ++(*this);
            return (tmp);
        }

        bidirectional_iterator &operator++()
        {
            if (_ptr->right != NULL)
            {
                _ptr = _ptr->right;
                while (_ptr->left != NULL)
                    _ptr = _ptr->left;
            }
            else
            {
                node_pointer tmp = _ptr;
                _ptr = _ptr->parent;
                while (_ptr->left != tmp)
                {
                    tmp = _ptr;
                    _ptr = _ptr->parent;
                }
            }
            return (*this);
        }

        bidirectional_iterator operator--(int)
        {
            bidirectional_iterator tmp = *this;
            --(*this);
            return (tmp);
        }

        bidirectional_iterator &operator--()
        {
            if (_ptr->left != NULL)
            {
                _ptr = _ptr->left;
                while (_ptr->right != NULL)
                    _ptr = _ptr->right;
            }
            else
            {
                node_pointer tmp = _ptr;
                _ptr = _ptr->parent;
                while (tmp != _ptr->right)
                {
                    tmp = _ptr;
                    _ptr = _ptr->parent;
                }
            }
            return (*this);
        }

        reference operator*()
        {
            return (this->_ptr->value);
        }
        reference operator*() const
        {
            return (this->_ptr->value);
        }

        pointer operator->()
        {
            return (&_ptr->value);
        }

        pointer operator->() const
        {
            return (&_ptr->value);
        }
    }; // bidirectional_iterator

    template <typename T, typename node_pointer>
    class const_bidirectional_iterator
    {
    public:
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

    private:
        node_pointer _ptr;

    public:
        const_bidirectional_iterator() : _ptr(NULL) {}
        const_bidirectional_iterator(node_pointer ptr) : _ptr(ptr) {}
        const_bidirectional_iterator(const const_bidirectional_iterator &rhs) : _ptr(rhs._ptr) {}
        const_bidirectional_iterator &operator=(const const_bidirectional_iterator &rhs)
        {
            this->_ptr = rhs._ptr;
            return (*this);
        }
        virtual ~const_bidirectional_iterator() {}

        operator const_bidirectional_iterator<const T, node_pointer>() const
        {
            return (const_bidirectional_iterator<const T, node_pointer>(this->_ptr));
        }

        const_bidirectional_iterator get_node() const { return (this->_ptr); }

        template <typename T1, typename T2>
        friend class bidirectional_iterator;

        friend bool operator==(const const_bidirectional_iterator &lhs, const const_bidirectional_iterator &rhs)
        {
            return (lhs._ptr == rhs._ptr);
        }

        friend bool operator!=(const const_bidirectional_iterator &lhs, const const_bidirectional_iterator &rhs)
        {
            return (lhs._ptr != rhs._ptr);
        }

        /*bool operator!=(const const_bidirectional_iterator &rhs) {
            return (!(*this == rhs));
        }*/

        const_bidirectional_iterator operator++(int)
        {
            const_bidirectional_iterator tmp = *this;
            ++(*this);
            return (tmp);
        }

        const_bidirectional_iterator &operator++()
        {
            if (_ptr->right != NULL)
            {
                _ptr = _ptr->right;
                while (_ptr->left != NULL)
                    _ptr = _ptr->left;
            }
            else
            {
                node_pointer tmp = _ptr;
                _ptr = _ptr->parent;
                while (_ptr->left != tmp)
                {
                    tmp = _ptr;
                    _ptr = _ptr->parent;
                }
            }
            return (*this);
        }

        const_bidirectional_iterator operator--(int)
        {
            const_bidirectional_iterator tmp = *this;
            --(*this);
            return (tmp);
        }

        const_bidirectional_iterator &operator--()
        {
            if (_ptr->left != NULL)
            {
                _ptr = _ptr->left;
                while (_ptr->right != NULL)
                    _ptr = _ptr->right;
            }
            else
            {
                node_pointer tmp = _ptr;
                _ptr = _ptr->parent;
                while (_ptr->right != tmp)
                {
                    tmp = _ptr;
                    _ptr = _ptr->parent;
                }
            }
            return (*this);
        }

        reference operator*() { return (this->_ptr->value); }
        reference operator*() const { return (this->_ptr->value); }
        pointer operator->() { return (&_ptr->value); }
        pointer operator->() const { return (&_ptr->value); }

    }; // const_bidirectional_iterator
} // namespace ft
#endif
