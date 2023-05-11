/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:13:13 by sojung            #+#    #+#             */
/*   Updated: 2022/10/20 12:43:05 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft {
template<typename InputIt1, typename InputIt2>
bool equal(InputIt1 first1, InputIt1 last1,
            InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2))
            return (false);
    }
    return (true);
}

template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1,
            InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!p(*first1, *first2))
            return (false);
    }
    return (true);
}
} // namespace ft
#endif