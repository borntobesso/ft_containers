/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:06:55 by sojung            #+#    #+#             */
/*   Updated: 2022/11/29 17:28:45 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"
#include "lexicographical_compare.hpp"
#include "equal.hpp"
#include <memory>    // std::allocator
#include <iterator>  // std::distance
#include <limits>    // std::numeric_limits
#include <algorithm> // std::min

namespace ft
{

    template <typename _T, typename _Allocator = std::allocator<_T>()>
    class _vector_base
    {
    public:
        typedef _Allocator allocator_type;

    protected:
        typedef _T value_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        pointer _begin;
        pointer _end;
        pointer _end_cap;
        allocator_type _a;

        _vector_base() throw();
        _vector_base(const allocator_type &a) throw();
        _vector_base(size_type n);
        _vector_base(size_type n, const allocator_type &a);
        // ~_vector_base() throw()
        // {
        //     if (_begin != NULL)
        //         _a.deallocate(_begin, _capacity());
        // }
        virtual ~_vector_base() {}

        size_type _capacity() const throw()
        {
            return (static_cast<size_type>(_end_cap - _begin));
        }

        size_type _check_length(size_type _n)
        {
            if (_n > _a.max_size())
                _throw_length_error("vector: size is too big");
            return (_n);
        }

        void _destruct_storage() throw();
        pointer _construct_storage(size_type _n)
        {
            return (_n == 0 ? pointer() : _a.allocate(_n));
        }

        void _copy_data(const _vector_base &_rhs) throw();
        void _copy_data(const pointer &_new_begin, const pointer &_new_end,
                        const pointer &_new_end_cap) throw();
        void _swap_data(_vector_base &_rhs) throw();

        void _throw_length_error(const char *msg) const
        {
            throw(std::length_error(msg));
        }
        void _throw_out_of_range(const char *msg) const
        {
            throw(std::out_of_range(msg));
        }

    private:
        _vector_base(const _vector_base &rhs) { (void)rhs; }
        _vector_base &operator=(const _vector_base &rhs) { (void)rhs; }
    };

    // vector_base class constructors
    template <typename _T, typename _Allocator>
    _vector_base<_T, _Allocator>::_vector_base() throw()
        : _begin(NULL),
          _end(NULL),
          _end_cap(NULL),
          _a(std::allocator<_T>()) {}

    template <typename _T, typename _Allocator>
    _vector_base<_T, _Allocator>::_vector_base(const allocator_type &a) throw()
        : _begin(NULL),
          _end(NULL),
          _end_cap(NULL),
          _a(a) {}

    template <typename _T, typename _Allocator>
    _vector_base<_T, _Allocator>::_vector_base(size_type _n)
        : _a(std::allocator<_T>())
    {
        _begin = _construct_storage(_n);
        _end = _begin;
        _end_cap = _begin + _n;
    }

    template <typename _T, typename _Allocator>
    _vector_base<_T, _Allocator>::_vector_base(size_type _n, const allocator_type &a)
        : _a(a)
    {
        _begin = _construct_storage(_n);
        _end = _begin;
        _end_cap = _begin + _n;
    }

    // vector_base class private member functions
    template <typename _T, typename _Allocator>
    void _vector_base<_T, _Allocator>::_copy_data(const _vector_base &_rhs) throw()
    {
        _begin = _rhs._begin;
        _end = _rhs._end;
        _end_cap = _rhs._end_cap;
    }

    template <typename _T, typename _Allocator>
    void _vector_base<_T, _Allocator>::_copy_data(
        const pointer &_new_begin, const pointer &_new_end,
        const pointer &_new_end_cap) throw()
    {
        _begin = _new_begin;
        _end = _new_end;
        _end_cap = _new_end_cap;
    }

    template <typename _T, typename _Allocator>
    void _vector_base<_T, _Allocator>::_swap_data(_vector_base &_rhs) throw()
    {
        pointer _tmp_begin(_begin);
        pointer _tmp_end(_end);
        pointer _tmp_end_cap(_end_cap);
        allocator_type _tmp_a(_a);
        this->_copy_data(_rhs);
        this->_a = _rhs._a;
        _rhs._copy_data(_tmp_begin, _tmp_end, _tmp_end_cap);
        _rhs._a = _tmp_a;
    }

    template <typename _T, typename _Allocator>
    void _vector_base<_T, _Allocator>::_destruct_storage() throw()
    {
        if (this->_begin != NULL)
        {
            _a.deallocate(_begin, _capacity());
            _end = _begin = _end_cap = NULL;
        }
    }

    // vector class
    template <typename T, typename Allocator = std::allocator<T> >
    class vector : private _vector_base<T, Allocator>
    {
    private:
        typedef _vector_base<T, Allocator> _base;

    public:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename _base::reference reference;
        typedef typename _base::const_reference const_reference;
        typedef typename _base::size_type size_type;
        typedef typename _base::difference_type difference_type;
        typedef typename _base::pointer pointer;
        typedef typename _base::const_pointer const_pointer;

        // typedef ft::random_access_iterator<value_type> iterator;
        // typedef ft::random_access_iterator<const value_type> const_iterator;
        typedef ft::vector_iterator<value_type> iterator;
        typedef ft::vector_iterator<const value_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        // constructors
        explicit vector(const allocator_type &Alloc = allocator_type());
        explicit vector(size_type n);
        explicit vector(size_type n, const value_type &val);
        vector(size_type n, const value_type &val, const allocator_type &Alloc);
        

        template <typename InputIterator>
        vector(InputIterator first,
               typename enable_if<!is_integral<InputIterator>::value,
                                  InputIterator>::type last,
               const allocator_type &Alloc = allocator_type());

        vector(const vector<T, Allocator> &rhs);

        // assign operator
        vector &operator=(const vector &rhs);

        // iterators
        iterator begin() { return (this->_begin); }
        const_iterator begin() const { return (this->_begin); }
        iterator end() { return (this->_end); }
        const_iterator end() const { return (this->_end); }
        reverse_iterator rbegin() { return (reverse_iterator(end())); }
        const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
        reverse_iterator rend() { return (reverse_iterator(begin())); }
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

        // capacity
        size_type size() const { return (std::distance(this->_begin, this->_end)); }
        size_type max_size() const
        {
            return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()),
                             this->_a.max_size()));
        }
        void resize(size_type n, const value_type &val = value_type());
        size_type capacity() const { return (this->_capacity()); }
        bool empty() const { return (this->_begin == this->_end); }
        void reserve(size_type n);

        // element access
        reference operator[](size_type n) { return (reference(*(this->_begin + n))); }
        const_reference operator[](size_type n) const
        {
            return (const_reference(*(this->_begin + n)));
        }
        reference at(size_type n)
        {
            if (n >= this->size())
                this->_throw_out_of_range("vector: out of range");
            return (*(this->_begin + n));
        }
        const_reference at(size_type n) const
        {
            if (n >= this->size())
                this->_throw_out_of_range("vector: out of range");
            return (*(this->_begin + n));
        }
        reference front() { return (*this->_begin); }
        const_reference front() const { return (*this->_begin); }
        reference back() { return (*(this->_end - 1)); }
        const_reference back() const { return (*(this->_end - 1)); }
        value_type *data() { return (&(this->front())); }
        const value_type *data() const { return (&(this->front())); }

        template <typename Iter, typename IterType>
        void doAssign(Iter first, Iter last, IterType type);
        template <typename Iter>
        void doAssign(Iter first, Iter last, std::input_iterator_tag);
        template <typename InputIterator>
        void assign(InputIterator first,
                    typename enable_if<!is_integral<InputIterator>::value,
                                       InputIterator>::type last);
        void assign(size_type n, const value_type &val);
        void push_back(const value_type &val);
        void pop_back();
        iterator insert(const_iterator pos, const value_type &val);
        void insert(const_iterator pos, size_type n, const value_type &val);
        template <typename Iter, typename IterType>
        void doInsert(const_iterator position, Iter first, Iter last, IterType);
        template <typename Iter>
        void doInsert(const_iterator position, Iter first, Iter last, std::input_iterator_tag);
        template <typename InputIterator>
        void insert(const_iterator position, InputIterator first,
                    typename enable_if<!is_integral<InputIterator>::value,
                                       InputIterator>::type last);
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);
        void swap(vector &rhs) { this->_swap_data(rhs); }
        void clear() throw()
        {
            if (this->_begin)
                _destroy_from_end(this->_begin);
        }

        // allocator
        allocator_type get_allocator() const throw() { return (this->_a); }

        // destructor
        ~vector() throw()
        {
            if (this->_begin)
            {
                clear();
                this->_destruct_storage();
            }
        }

    private:
        void _reconstruct_push_back(const value_type &val);
        void _reallocate(size_type _n);
        void _destroy_from_end(pointer _new_end);
    };

    // constructor
    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(const allocator_type &Alloc)
        : _vector_base<T, Allocator>(size_type(), Alloc) {}

    // std::uninitializd_fill : fill block of memory -
    // CONSTRUCTS all the elements in the range[first, last)] initializing them to a value of x
    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type n)
        : _vector_base<T, Allocator>(n, allocator_type())
    {
        std::uninitialized_fill(this->_begin, this->_begin + n, value_type());
        this->_end += n;
    }

    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type &val)
        : _vector_base<T, Allocator>(n, allocator_type())
    {
        std::uninitialized_fill(this->_begin, this->_begin + n, val);
        this->_end += n;
    }

    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(size_type n, const value_type &val,
                                 const allocator_type &Alloc)
        : _vector_base<T, Allocator>(n, Alloc)
    {
        std::uninitialized_fill(this->_begin, this->_begin + n, val);
        this->_end += n;
    }

    // template <typename T, typename Allocator>
    // template <typename InputIterator>
    // vector<T, Allocator>::vector(InputIterator first,
    //                              typename enable_if<!is_integral<InputIterator>::value,
    //                                                 InputIterator>::type last,
    //                              const allocator_type &Alloc)
    //     : _vector_base<T, Allocator>(size_type(), Alloc)
    // {
    //     for (; first != last; ++first)
    //         push_back(*first);
    // }

    template <typename T, typename Allocator>
    template <typename InputIterator>
    vector<T, Allocator>::vector(InputIterator first,
                                 typename enable_if<!is_integral<InputIterator>::value,
                                                    InputIterator>::type last,
                                 const allocator_type &Alloc)
        : _vector_base<T, Allocator>(
              static_cast<size_type>(std::distance(first, last)), Alloc)
    {
        this->_end = std::uninitialized_copy(first, last, this->_begin);
    }

    template <typename T, typename Allocator>
    vector<T, Allocator>::vector(const vector<T, Allocator> &rhs)
        : _vector_base<T, Allocator>(rhs.capacity())
    {
        clear();
        this->_end = std::uninitialized_copy(rhs._begin, rhs._end, this->_begin);
    }

    template <typename T, typename Allocator>
    vector<T, Allocator> &vector<T, Allocator>::operator=(
        const vector<T, Allocator> &rhs)
    {
        if (this != &rhs)
        {
            if (this->_a != rhs._a)
            {
                clear();
                this->_a.deallocate(this->_begin, capacity());
                this->_begin = this->_end = this->_end_cap = NULL;
                this->_a = rhs._a;
            }
            assign(rhs._begin, rhs._end);
        }
        return (*this);
    }

    // private member fuction
    template <typename T, typename Allocator>
    void vector<T, Allocator>::_reconstruct_push_back(const value_type &val)
    {
        size_type _cap = this->_capacity();
        size_type _max_size = max_size();
        size_type _new_size = _cap > (_max_size >> 1) ? _max_size : _cap << 1;
        if (_new_size == 0)
            _new_size = 1;
        reserve(_new_size);
        this->_a.construct(this->_end, val);
        ++this->_end;
    }
    // copy-swap idiom for the exception-safety
    template <typename T, typename Allocator>
    void vector<T, Allocator>::_reallocate(size_type _n)
    {
        vector<T, Allocator> tmp(_n);
        //std::uninitialized_copy(this->_begin, this->_end, tmp._begin);
        pointer tmp_start = this->_begin;
        pointer tmp_it = tmp._begin;
        while (tmp_start != this->_end)
        {
            this->_a.construct(tmp_it, *tmp_start);
            tmp_start++;
            tmp_it++;
        }
        tmp._end = tmp._begin + size();
        this->_swap_data(tmp);
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::_destroy_from_end(pointer _new_end)
    {
        pointer _tmp_end = this->_end;
        while (_new_end != _tmp_end)
        {
            --_tmp_end;
            this->_a.destroy(_tmp_end);
        }
        this->_end = _new_end;
    }

    // public member functions

    // capacity
    template <typename T, typename Allocator>
    void vector<T, Allocator>::reserve(size_type n)
    {
        try
        {
            size_type _new_size = this->_check_length(n);
            if (_new_size > capacity())
            {
                _reallocate(_new_size);
            }
        }
        catch (std::length_error &)
        {
            throw (std::length_error("vector::reserve"));
        }
    }

    /* If n is smaller than the current container size, the content is reduced to its first n elements,
    removing those beyond (and destroying them).
    If n is greater than the current container size, the content is expanded by inserting at the end
    as many elements as needed to reach a size of n. If val is specified, the new elements
    are initialized as copies of val, otherwise, they are value-initialized.*/
    template <typename T, typename Allocator>
    void vector<T, Allocator>::resize(size_type n, const value_type &val)
    {
        size_type prev_size = size();
        if (n < prev_size)
        {
            _destroy_from_end(this->_begin + n);
            return;
        }
        else if (n > capacity())
        {
            _reallocate(n);
        }
        insert(end(), n - prev_size, val);
    }

    // modifiers

    // assign : replaces the contents of the container
    template <typename T, typename Allocator>
    void vector<T, Allocator>::assign(size_type n, const value_type &val)
    {
        if (n < this->capacity())
        {
            this->clear();
            std::uninitialized_fill(this->_begin, this->_begin + n, val);
            this->_end += n;
            //this->insert(this->_begin, n, val);
        }
        else
        {
            vector<T, Allocator> tmp(n, val);
            this->_swap_data(tmp);
        }
    }

    template <typename T, typename Allocator>
    template <typename Iter, typename IterType>
    void vector<T, Allocator>::doAssign(Iter first, Iter last, IterType)
    {
        size_type _new_n = std::distance(first, last);
        if (_new_n < this->capacity())
        {
            this->clear();
            this->_end = std::uninitialized_copy(first, last, this->_begin);
        }
        else
        {
            vector<T, Allocator> tmp(first, last);
            this->_swap_data(tmp);
        }
    }

    // specialization for input iterators
    template <typename T, typename Allocator>
    template <typename Iter>
    void vector<T, Allocator>::doAssign(Iter first, Iter last, std::input_iterator_tag)
    {
        this->clear();
        for (; first != last; ++first)
            push_back(*first);
    }

    template <typename T, typename Allocator>
    template <typename InputIterator>
    void vector<T, Allocator>::assign(InputIterator first,
                                      typename enable_if<!is_integral<InputIterator>::value,
                                                         InputIterator>::type last)
    {
        doAssign(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::push_back(const value_type &val)
    {
        if (this->_end != this->_end_cap)
            this->_a.construct(this->_end++, val);
        else
            _reconstruct_push_back(val);
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::pop_back()
    {
        if (!empty())
            _destroy_from_end(this->_end - 1);
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(
        const_iterator position, const value_type &val)
    {
        difference_type _diff = position - this->begin();
        if (this->_end == this->_end_cap)
            reserve(size_type(capacity() + 1));
        pointer _p = this->_begin + _diff;
        pointer _old_end = this->_end;
        while (_old_end != _p)
        {
            --_old_end;
            this->_a.construct(_old_end + 1, *_old_end);
            this->_a.destroy(_old_end);
        }
        this->_a.construct(_p, val);
        this->_end++;
        return (iterator(this->_begin + _diff));
    }

    template <typename T, typename Allocator>
    void vector<T, Allocator>::insert(const_iterator position, size_type n,
                                      const value_type &val)
    {
        difference_type _diff = position - const_iterator(this->_begin);
        if (size() + n > capacity())
            reserve(size() + n);
        pointer _p = this->_begin + _diff;
        pointer _old_end = this->_end;
        while (_old_end != _p)
        {
            --_old_end;
            this->_a.construct(_old_end + n, *(_old_end));
            this->_a.destroy(_old_end);
        }
        std::uninitialized_fill(_p, _p + n, val);
        this->_end += n;
    }

    template <typename T, typename Allocator>
    template <typename Iter, typename IterType>
    void vector<T, Allocator>::doInsert(const_iterator position, Iter first, Iter last, IterType)
    {
        difference_type _in_size = std::distance(first, last);
        difference_type _diff = position - begin();
        if (_in_size <= 0)
            return;
        if (_in_size + size() > capacity())
            reserve(_in_size + size());
        pointer _p = this->_begin + _diff;
        pointer _old_end = this->_end;
        while (_old_end != _p)
        {
            --_old_end;
            this->_a.construct(_old_end + _in_size, *(_old_end));
            this->_a.destroy(_old_end);
        }
        std::uninitialized_copy(first, last, _p);
        this->_end += _in_size;
    }

    // specialization for input_iterators
    template <typename T, typename Allocator>
    template <typename Iter>
    void vector<T, Allocator>::doInsert(const_iterator position, Iter first, Iter last, std::input_iterator_tag)
    {
        for (int i = 0; first != last; ++first, ++i)
            insert(position + i, *first);
    }

    template <typename T, typename Allocator>
    template <typename InputIterator>
    void vector<T, Allocator>::insert(const_iterator position, InputIterator first,
                                      typename enable_if<!is_integral<InputIterator>::value,
                                                         InputIterator>::type last)
    {
        doInsert(position, first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator position)
    {
        difference_type    marker = position - this->begin();
        pointer    p_pos = this->_begin + marker;
        pointer    tmp_start = p_pos;
        pointer    tmp_end = this->_end;

        while (tmp_end != this->_begin)
        {
            tmp_end--;
            if (tmp_end == p_pos)
            {
                this->_a.destroy(p_pos);
                while (tmp_end != this->_end)
                {
                    tmp_end++;
                    if (tmp_end != this->_end)
                        this->_a.construct(tmp_start, *tmp_end);
                    if (tmp_end != this->_end)
                        this->_a.destroy(tmp_end);
                    tmp_start++;
                }
                this->_end--;
                return (iterator(p_pos));
            }
        }
        return (iterator(p_pos));

        // difference_type _diff = position - begin();
        // pointer _p = this->_begin + _diff;
        // pointer tmp_start = _p;
        // pointer tmp_end = this->_end;

        // while (tmp_end != this->_begin)
        // {
        //     tmp_end--;
        //     if (tmp_end == _p)
        //     {
        //         this->_a.destroy(_p);
        //         while (tmp_end != this->_end)
        //         {
        //             tmp_end++;
        //             if (tmp_end != this->_end)
        //                 this->_a.construct(tmp_start, *tmp_end);
        //             if (tmp_end != this->_end)
        //                 this->_a.destroy(tmp_end);
        //             tmp_start++;
        //         }
        //         this->_end--;
        //         return (iterator(_p));
        //     }
        // }
        // return (iterator(_p));

        // // this->_a.destroy(_p);
        // // this->_a.destroy(std::uninitialized_copy(_p + 1, this->_end--, _p));
        // // //std::uninitialized_copy(_p + 1, this->_end, _p);
        // // //this->_a.destroy(this->_end - 1);
        // // //this->_end--;
        // // return (iterator(this->_begin + _diff));
    }

    template <typename T, typename Allocator>
    typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
    {
        if (first == last)
            return (first);
        difference_type _diff = first - begin();
        difference_type range = last - first;
        pointer _p = this->_begin + _diff;
        pointer tmp_end = this->_end;
        pointer tmp_last = _p + range;
        for (pointer tmp_first = _p; tmp_first != tmp_last && tmp_first != tmp_end; tmp_first++)
            this->_a.destroy(tmp_first);
        pointer    tmp_first = _p;
        while (tmp_first + range != tmp_end)
        {
            this->_a.construct(tmp_first, *(tmp_first + range));
            this->_a.destroy(tmp_first + range);
            tmp_first++;
        }
        this->_end -= range;
        return (first);
        
        // difference_type _diff = first - begin();
        // pointer _p = this->_begin + _diff;

        // if (last == end())
        // {
        //     _destroy_from_end(_p);
        //     return (iterator(this->_begin + _diff));
        // }

        // difference_type _range = last - first;
        // pointer _p_last = _p + _range;
        // pointer _new_end = this->_end - _range;

        // for (difference_type i = 0; i <= _range; ++i)
        // {
        //     this->_a.destroy(_p + i);
        //     if (i <= this->_end - _p_last)
        //         this->_a.construct(_p + i, *(_p_last + i));
        // }
        // // for (difference_type i = 0; i < _range; ++i)
        // //     this->_a.destroy(_p + i);
        // // std::uninitialized_copy(_p + _range, this->_end, _p);
        // _destroy_from_end(_new_end);
        // return (iterator(this->_begin + _diff));
    }

    // comparison operators
    template <typename T, typename Allocator>
    inline bool operator==(const vector<T, Allocator> &lhs,
                           const vector<T, Allocator> &rhs)
    {
        return (lhs.size() == rhs.size() &&
                ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <typename T, typename Allocator>
    inline bool operator!=(const vector<T, Allocator> &lhs,
                           const vector<T, Allocator> &rhs)
    {
        return (!(lhs == rhs));
    }

    template <typename T, typename Allocator>
    inline bool operator<(const vector<T, Allocator> &lhs,
                          const vector<T, Allocator> &rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <typename T, typename Allocator>
    inline bool operator>(const vector<T, Allocator> &lhs,
                          const vector<T, Allocator> &rhs)
    {
        return (rhs < lhs);
    }

    template <typename T, typename Allocator>
    inline bool operator<=(const vector<T, Allocator> &lhs,
                           const vector<T, Allocator> &rhs)
    {
        return (!(lhs > rhs));
    }

    template <typename T, typename Allocator>
    inline bool operator>=(const vector<T, Allocator> &lhs,
                           const vector<T, Allocator> &rhs)
    {
        return (!(rhs > lhs));
    }

    // swap overload
    template <typename T, typename Allocator>
    inline void swap(ft::vector<T, Allocator> &x, ft::vector<T, Allocator> &y)
    {
        x.swap(y);
    }

} // namespace ft

#endif
