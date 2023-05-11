/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyoungjung <soyoungjung@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:47:51 by sojung            #+#    #+#             */
/*   Updated: 2022/12/09 12:59:27 by soyoungjung      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
    /* Checks if the first range [first1, last1)
     is lexicographically less than the second range [first2, last2) */
    template <typename InputIt1, typename InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return (true);
            if (*first2 < *first1)
                return (false);
        }
        return ((first1 == last1) && (first2 != last2));
    }

    template <typename InputIt1, typename InputIt2, typename Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (comp(*first1, *first2))
                return (true);
            if (comp(*first2, *first1))
                return (false);
        }
        return ((first1 == last1) && (first2 != last2));
    }
} // namespace ft
#endif