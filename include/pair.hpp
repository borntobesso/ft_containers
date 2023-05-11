/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:28:04 by sojung            #+#    #+#             */
/*   Updated: 2022/10/20 16:05:06 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
    template<typename T1, typename T2>
    struct pair {
        // member types
        typedef T1  first_type;
        typedef T2  second_type;

        // member variables
        first_type  first;
        second_type second;

        // constructor
        pair() : first(), second() {}
        template<typename U1, typename U2>
        pair(const pair<U1, U2>  &rhs)
            : first(rhs.first), second(rhs.second) {}
        pair(const T1 &t1, const T2 &t2) : first(t1), second(t2) {}

        // assign operator
        pair &operator = (pair const &rhs) {
            first = rhs.first;
            second = rhs.second;
            return *this;
        }
    };

    // non-member functions
    // operator overloads
    template<typename T1, typename T2>
    bool operator == (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template<typename T1, typename T2>
    bool operator != (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs == rhs));
    }
    // compares the first elements and only if they are equivalent, compares the second elements
    template<typename T1, typename T2>
    bool operator < (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

    template<typename T1, typename T2>
    bool operator > (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first > rhs.first || (!(rhs.first > lhs.first) && lhs.second > rhs.second));
    }

    template<typename T1, typename T2>
    bool operator <= (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs > rhs));
    }

    template<typename T1, typename T2>
    bool operator >= (const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs < rhs));
    }
    // make pair : Creates a pair object, deducing the target type from the types of arguments
    template<typename T1, typename T2>
    inline pair<T1, T2> make_pair(T1 t, T2 u) {
        return (pair<T1, T2>(t, u));
    }
} // namepace ft

#endif