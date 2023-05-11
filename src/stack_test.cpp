/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soyoungjung <soyoungjung@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:33:03 by soyoungjung       #+#    #+#             */
/*   Updated: 2022/11/17 17:40:32 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/stack.hpp"
#include <iostream>
#include <string>
#include <iomanip> // std::boolalpha

void stack_test(void)
{
	std::cout << "##############################" << std::endl;
	std::cout << "#                            #" << std::endl;
	std::cout << "#       FT::STACK TEST       #" << std::endl;
	std::cout << "#                            #" << std::endl;
	std::cout << "##############################" << std::endl
			  << std::endl;

	ft::stack<int> int_stack1;
	int_stack1.push(1);
	ft::stack<int> int_stack2(int_stack1);
	std::cout << int_stack2.top() << std::endl;
	int_stack1.push(2);
	int_stack2 = int_stack1;
	std::cout << int_stack2.top() << std::endl;

	ft::stack<char> empty;
	std::cout << std::boolalpha << int_stack1.empty() << std::endl;
	std::cout << int_stack2.empty() << std::endl;
	std::cout << empty.empty() << std::endl;

	std::cout << int_stack1.size() << std::endl;
	std::cout << int_stack2.size() << std::endl;
	std::cout << empty.size() << std::endl;

	for (int i = 0; i < 100; i++)
		int_stack1.push(i + 3);
	std::cout << int_stack1.top() << std::endl;
	std::cout << int_stack1.size() << std::endl;

	for (int i = 0; i < 102; i++)
		int_stack1.pop();
	std::cout << int_stack1.size() << std::endl;
	// error test
//	std::cout << int_stack1.top() << std::endl;
//	int_stack1.pop();

	// operators test
	std::cout << (int_stack1 == int_stack2) << std::endl;
	std::cout << (int_stack2 == int_stack2) << std::endl;
	std::cout << (int_stack1 != int_stack2) << std::endl;
	std::cout << (int_stack2 != int_stack2) << std::endl;
	std::cout << (int_stack1 < int_stack2) << std::endl;
	std::cout << (int_stack2 < int_stack2) << std::endl;
	std::cout << (int_stack1 > int_stack2) << std::endl;
	std::cout << (int_stack2 > int_stack2) << std::endl;
	std::cout << (int_stack1 <= int_stack2) << std::endl;
	std::cout << (int_stack2 <= int_stack2) << std::endl;
	std::cout << (int_stack1 >= int_stack2) << std::endl;
	std::cout << (int_stack2 >= int_stack2) << std::endl;
}
