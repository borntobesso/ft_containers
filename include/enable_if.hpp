/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:07:16 by sojung            #+#    #+#             */
/*   Updated: 2022/10/13 13:01:10 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
    template<bool, typename T = void>
    struct enable_if
    {};

    template<typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

} // namespace ft

#endif