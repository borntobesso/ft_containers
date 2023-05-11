/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyoungjung <soyoungjung@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:08:11 by soyoungjung       #+#    #+#             */
/*   Updated: 2022/11/17 17:35:39 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template <typename _T, typename Container = vector<_T> >
	class stack
	{
	protected:
		Container c;

	public:
		typedef Container 							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference 		reference;
		typedef typename Container::const_reference const_reference;

		// constructor
		explicit stack(const Container &rhs = Container()) : c(rhs) {}
		// capacity
		bool empty() const { return (c.empty()); }
		size_type size() const { return (c.size()); }
		// modifiers
		void push(const value_type &value) { return (c.push_back(value)); }
		void pop() { c.pop_back(); }
		// element access
		reference top() { return (c.back()); }
		const_reference top() const { return (c.back()); }

		// relational operator
		// Use friend to compare protected member variable
		template <typename T, typename C>
		friend bool operator==(const stack<T, C> &lhs, const stack<T, C> &rhs);
		template <typename T, typename C>
		friend bool operator<(const stack<T, C> &lhs, const stack<T, C> &rhs);
	};

	template <typename T, typename C>
	inline bool operator==(const stack<T, C> &lhs, const stack<T, C> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <typename T, typename C>
	inline bool operator!=(const stack<T, C> &lhs, const stack<T, C> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename T, typename C>
	inline bool operator<(const stack<T, C> &lhs, const stack<T, C> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <typename T, typename C>
	inline bool operator<=(const stack<T, C> &lhs, const stack<T, C> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, typename C>
	inline bool operator>(const stack<T, C> &lhs, const stack<T, C> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename C>
	inline bool operator>=(const stack<T, C> &lhs, const stack<T, C> &rhs)
	{
		return (!(lhs < rhs));
	}

} // namespace ft
#endif
