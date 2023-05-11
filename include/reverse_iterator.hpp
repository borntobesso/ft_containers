/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:58:38 by sojung            #+#    #+#             */
/*   Updated: 2022/11/29 17:28:53 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
    template <typename _Iterator>
    class reverse_iterator
    {
    protected:
        _Iterator current;

        typedef ft::iterator_traits<_Iterator> _traits_type;

    public:
        typedef _Iterator iterator_type;
        typedef typename _traits_type::iterator_category iterator_category;
        typedef typename _traits_type::value_type value_type;
        typedef typename _traits_type::difference_type difference_type;
        typedef typename _traits_type::pointer pointer;
        typedef typename _traits_type::reference reference;

        reverse_iterator() : current() {}
        explicit reverse_iterator(iterator_type _x) : current(_x) {}
        reverse_iterator(const reverse_iterator &_x) : current(_x.current) {}
        // copy constructor with different type of reverse iterator
        template <typename _Iter>
        reverse_iterator(const reverse_iterator<_Iter> &_x) : current(_x.base()) {}
        // virtual ~reverse_iterator();
        template <typename U>
        reverse_iterator &operator=(const reverse_iterator<U> &rhs)
        {
            current = rhs.base();
            return *this;
        }
        // the base iterator is an iterator of the same type as the one used to construct the reverse_iterator,
        // but refers to the element that is next to the element the reverse_iterator is currently pointing to.
        // (a reverse_iterator has always an offset of -1 with respect to its base iterator)
        // That is
        // std::reverse_iterator(it).base() == std::next(it).
        iterator_type base() const { return current; }

        reference operator*() const
        {
            _Iterator _tmp = current;
            return (*--_tmp);
        }

        pointer operator->() const { return &(operator*()); }

        // pre-increment
        reverse_iterator &operator++()
        {
            --current;
            return (*this);
        }

        // post-increment
        reverse_iterator operator++(int)
        {
            reverse_iterator _tmp = *this;
            --current;
            return (_tmp);
        }

        // pre-decrement
        reverse_iterator &operator--()
        {
            ++current;
            return (*this);
        }

        // post-decrement
        reverse_iterator operator--(int)
        {
            reverse_iterator _tmp = *this;
            ++current;
            return (_tmp);
        }

        reverse_iterator operator+(difference_type _n) const
        {
            return (reverse_iterator(current - _n));
        }

        reverse_iterator &operator+=(difference_type _n)
        {
            current -= _n;
            return (*this);
        }

        reverse_iterator operator-(difference_type _n) const
        {
            return (reverse_iterator(current + _n));
        }

        reverse_iterator &operator-=(difference_type _n)
        {
            current += _n;
            return (*this);
        }

        reference operator[](difference_type _n) const { return (*(*this + _n)); }
    };

    // reverse iterators forward many operations to their underlying base() iterators.
    template <typename _Iterator>
    inline bool operator==(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<_Iterator> &_y) { return (_x.base() == _y.base()); }

    template <typename _Iterator>
    inline bool operator<(const reverse_iterator<_Iterator> &_x,
                          const reverse_iterator<_Iterator> &_y) { return (_y.base() < _x.base()); }

    template <typename _Iterator>
    inline bool operator!=(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<_Iterator> &_y) { return (!(_x == _y)); }

    template <typename _Iterator>
    inline bool operator>(const reverse_iterator<_Iterator> &_x,
                          const reverse_iterator<_Iterator> &_y) { return (_y < _x); }

    template <typename _Iterator>
    inline bool operator<=(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<_Iterator> &_y) { return (!(_y < _x)); }

    template <typename _Iterator>
    inline bool operator>=(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<_Iterator> &_y) { return (!(_x < _y)); }

    template <typename _Iterator>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator> &_x, const reverse_iterator<_Iterator> &_y)
    {
        return (_y.base() - _x.base());
    }

    template <typename _Iterator>
    inline reverse_iterator<_Iterator>
    operator+(typename reverse_iterator<_Iterator>::difference_type _n,
              const reverse_iterator<_Iterator> &_x)
    {
        return (reverse_iterator<_Iterator>(_x.base() - _n));
    }

    //////////////
    template <typename _Iterator, typename T>
    inline bool operator==(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<T> &_y)
    { return (_x.base() == _y.base()); }

    template <typename _Iterator, typename T>
    inline bool operator!=(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<T> &_y)
    { return (!(_x == _y)); }

    template <typename _Iterator, typename T>
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator> &_x, const reverse_iterator<T> &_y)
    {
        reverse_iterator<_Iterator> tmp(_y);
        return (tmp.base() - _x.base());
    }

    template <typename _Iterator, typename T>
    inline bool operator<(const reverse_iterator<_Iterator> &_x,
                          const reverse_iterator<T> &_y) { return (_y.base() < _x.base()); }

    template <typename _Iterator, typename T>
    inline bool operator>(const reverse_iterator<_Iterator> &_x,
                          const reverse_iterator<T> &_y) { return (_y < _x); }

    template <typename _Iterator, typename T>
    inline bool operator<=(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<T> &_y) { return (!(_y < _x)); }

    template <typename _Iterator, typename T>
    inline bool operator>=(const reverse_iterator<_Iterator> &_x,
                           const reverse_iterator<T> &_y) { return (!(_x < _y)); }

} // namespace ft

#endif