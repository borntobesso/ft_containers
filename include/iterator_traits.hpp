/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:11:28 by sojung            #+#    #+#             */
/*   Updated: 2022/11/29 14:19:01 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef> // ptrdiff_t
#include <iterator>
#include <typeinfo>        // typeid
#include "is_integral.hpp" // integral_constant

// A traits class provides a way of associating information with a compile-time entity
// (a type, integral constant, or address).
// input iterator, output iterator, foward iterator, bidirectional iterator, randpom access iterator

namespace ft
{
    // primitive iterator tags
    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };
    struct contiguous_iterator_tag : public random_access_iterator_tag
    {
    };

    template <typename I>
    struct iterator_traits
    {
        typedef typename I::iterator_category iterator_category;
        typedef typename I::value_type value_type;
        typedef typename I::difference_type difference_type;
        typedef difference_type distance_type;
        typedef typename I::pointer pointer;
        typedef typename I::reference reference;
    };

    // partial specialization for pointer types
    template <typename _Tp>
    struct iterator_traits<_Tp *>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef _Tp value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::ptrdiff_t distance_type;
        typedef _Tp *pointer;
        typedef _Tp &reference;
    };

    // partial specialization for const pointer types
    template <typename _Tp>
    struct iterator_traits<const _Tp *>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef _Tp value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::ptrdiff_t distance_type;
        typedef const _Tp *pointer;
        typedef const _Tp &reference;
    };

    template <bool is_valid, typename T>
    struct valid_iterator_tag
    {
        typedef T type;
        const static bool value = is_valid;
    };

    template <typename T>
    struct is_valid_iterator_tagged : public valid_iterator_tag<false, T>
    {
    };

    template <>
    struct is_valid_iterator_tagged<std::random_access_iterator_tag>
        : public valid_iterator_tag<true, std::random_access_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<std::bidirectional_iterator_tag>
        : public valid_iterator_tag<true, std::bidirectional_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<std::forward_iterator_tag>
        : public valid_iterator_tag<true, std::forward_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<std::input_iterator_tag>
        : public valid_iterator_tag<true, std::input_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<ft::random_access_iterator_tag>
        : public valid_iterator_tag<true, std::random_access_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<ft::bidirectional_iterator_tag>
        : public valid_iterator_tag<true, std::bidirectional_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<ft::forward_iterator_tag>
        : public valid_iterator_tag<true, std::forward_iterator_tag>
    {
    };

    template <>
    struct is_valid_iterator_tagged<ft::input_iterator_tag>
        : public valid_iterator_tag<true, std::input_iterator_tag>
    {
    };

    // template <typename T>
    // bool is_input_iterator(T it) {
    //     if ((typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(input_iterator_tag)) ||
    //         (typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(std::input_iterator_tag)))
    //         return (true);
    //     else
    //         return (false);
    // }
    // template <typename T>
    // bool is_forward_iterator(T it) {
    //     if ((typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(forward_iterator_tag)) ||
    //         (typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(std::forward_iterator_tag)) ||
    //         (typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(bidirectional_iterator_tag)) ||
    //         (typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(std::bidirectional_iterator_tag)) ||
    //         (typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(random_access_iterator_tag)) ||
    //         (typeid(typename iterator_traits<T>::iterator_category)
    //                                 == typeid(std::random_access_iterator_tag)))
    //         return (true);
    //     else
    //         return (false);
    // }
} // namespace ft

#endif