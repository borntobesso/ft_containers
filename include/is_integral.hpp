/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:41:56 by sojung            #+#    #+#             */
/*   Updated: 2022/10/13 15:49:02 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
    // type_traits
    
    //integral_constant
    template<typename T, T _v>
    struct integral_constant
    {
        static const T                      value = _v;
        typedef T                           value_type;
        typedef integral_constant<T, _v>    type;
        operator value_type() { return (value); }
    };

    // typedef for true_type
    typedef integral_constant<bool, true>   true_type;
    typedef integral_constant<bool, false>  false_type;

    // remove_const
    template<typename T>
    struct remove_const
    { typedef T type; };

    template<typename T>
    struct remove_const<T const>
    { typedef T type; };

    // remove_volatile
    template<typename T>
    struct remove_volatile
    { typedef T type; };

    template<typename T>
    struct remove_volatile<T volatile>
    { typedef T type; };
    
    // remove cv
    template<typename T>
    struct remove_cv
    {
        typedef typename
        remove_const<typename remove_volatile<T>::type>::type   type;
    };

    template<typename>
    struct is_integral_helper : public false_type {};

    template<>
    struct is_integral_helper<bool> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<char> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<signed char> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<wchar_t> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<short> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<unsigned short> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<int> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<unsigned int> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<long> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<unsigned long> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<long long> : public integral_constant<bool, true> {};
    template<>
    struct is_integral_helper<unsigned long long> : public integral_constant<bool, true> {};
    
    // is_integral
    template<typename T>
    struct is_integral
    : public integral_constant<bool, (is_integral_helper<typename remove_cv<T>::type>::value)> {};
    
} // namespace ft

#endif