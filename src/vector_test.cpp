/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:46:14 by sojung            #+#    #+#             */
/*   Updated: 2022/12/12 15:56:05 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.hpp"
#include <iostream>
#include <string>
#include <map>
#include <iomanip> // std::boolalpha
#include <sys/time.h> // gettimeofday()
#include <ios> // std::ios_base
#include <bits/stdc++.h>

template <typename V>
void print_vector(V &v)
{
    for (typename V::iterator i = v.begin(); i != v.end(); ++i)
        std::cout << *i << " " << std::endl;
    std::cout << "size :\t\t" << v.size() << std::endl;
    std::cout << "capacity :\t" << v.capacity() << std::endl
              << std::endl;
}

void vector_test(void)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);

    std::cout << "##############################" << std::endl;
    std::cout << "#                            #" << std::endl;
    std::cout << "#      FT::VECTOR TEST       #" << std::endl;
    std::cout << "#                            #" << std::endl;
    std::cout << "##############################" << std::endl
              << std::endl;

    std::cout << "## Constructor & assignment test ##" << std::endl
              << std::endl;
    std::cout << ">> Default constructor" << std::endl;
    ft::vector<int> default_int;
    print_vector(default_int);
    ft::vector<char> default_char;
    print_vector(default_char);
    ft::vector<std::string> default_str;
    print_vector(default_str);
    std::cout << ">> Fill constructor" << std::endl;
    ft::vector<int> fill_int(5, 42);
    print_vector(fill_int);
    ft::vector<char> fill_char(10, 'c');
    print_vector(fill_char);
    try
    {
        ft::vector<char> fill_char_err(-5, 'c');
        print_vector(fill_char_err);
    }
    catch (std::exception &e)
    {
        std::cout << "cannot create ft::vector" << std::endl;
    }
    
    ft::vector<std::string> fill_str(42, "42");
    print_vector(fill_str);
    ft::vector<std::string> fill_str_zero(0, "42");
    print_vector(fill_str_zero);
    std::cout << ">> Range constructor" << std::endl;
    ft::vector<int> ref_int_vec(20, 100);
    ft::vector<int> range_int(ref_int_vec.begin(), ref_int_vec.end());
    print_vector(range_int);
    ft::vector<int> range_int_err(ref_int_vec.begin(), ref_int_vec.begin() + 10);
    print_vector(range_int_err);
    std::cout << ">> Copy constructor" << std::endl;
    ft::vector<int> copy_int(range_int);
    print_vector(copy_int);
    ft::vector<char> copy_char(ft::vector<char>(5, 'a'));
    print_vector(copy_char);
    std::cout << ">> Assignment operator" << std::endl;
    ft::vector<int> assign_int;
    assign_int = copy_int;
    print_vector(assign_int);
    range_int = assign_int;
    print_vector(range_int);

    std::cout << "## Iterator & reverse iterator test ##" << std::endl;
    std::cout << *copy_char.begin() << std::endl;
    std::cout << *(copy_char.begin() + 1) << std::endl;
    std::cout << *(copy_char.end() - 1) << std::endl;
    std::cout << *(copy_char.end() - 2) << std::endl;
    std::cout << *(copy_char.rbegin()) << std::endl;
    std::cout << *(copy_char.rend() - 1) << std::endl;
    const ft::vector<int> const_vec(assign_int);
    std::cout << *const_vec.begin() << std::endl;
    std::cout << *(const_vec.begin() + 1) << std::endl;
    std::cout << *(const_vec.end() - 1) << std::endl;
    std::cout << *(const_vec.end() - 3) << std::endl;
    std::cout << *(const_vec.rbegin()) << std::endl;
    std::cout << *(const_vec.rend() - 1) << std::endl;

    std::cout << "## Capacity test ##" << std::endl;
    ft::vector<char> empty_char;
    std::cout << "capacity : " << empty_char.capacity() << std::endl;
    std::cout << "max size : " << empty_char.max_size() << std::endl;
    std::cout << "size : " << empty_char.size() << std::endl;
    std::cout << "is empty : " << std::boolalpha << empty_char.empty() << std::endl;
    empty_char.reserve(100);
    std::cout << "capacity after reserve : " << empty_char.capacity() << std::endl;
    empty_char.resize(10, 'z');
    std::cout << "after resize : " << std::endl;
    std::cout << "is empty : " << std::boolalpha << empty_char.empty() << std::endl;
    print_vector(empty_char);
    ft::vector<int> empty_int;
    std::cout << "max_size of vector<int> : " << empty_int.max_size() << std::endl;
    ft::vector<std::string> empty_str;
    std::cout << "max_size of vector<std::string> : " << empty_str.max_size() << std::endl;

    std::cout << "## Element access test ##" << std::endl;
    ft::vector<char> alpha_vec;
    for (size_t i = 0; i < 5; i++)
        alpha_vec.push_back('A' + i);
    const ft::vector<char> const_alpha_vec(alpha_vec.begin(), alpha_vec.end());
    for (size_t i = 0; i < 5; i++)
        std::cout << alpha_vec[i] << alpha_vec.at(i) << " ";
    std::cout << std::endl;
    for (size_t i = 0; i < 5; i++)
        std::cout << const_alpha_vec[i] << const_alpha_vec.at(i) << " ";
    std::cout << std::endl;
    std::cout << alpha_vec.front() << " " << alpha_vec.back() << " " << *alpha_vec.data() << std::endl;
    std::cout << const_alpha_vec.front() << " " << const_alpha_vec.back() << " " << *const_alpha_vec.data() << std::endl;

    std::cout << "## Modifiers test ##" << std::endl;
    std::cout << "assign() test" << std::endl;
    alpha_vec.assign(3, 'B');
    print_vector(alpha_vec);
    alpha_vec.assign(10, 'C');
    print_vector(alpha_vec);
    ft::vector<char> alpha_vec2;
    alpha_vec2.assign(alpha_vec.begin(), alpha_vec.end());
    print_vector(alpha_vec2);
    alpha_vec2.assign(alpha_vec.begin(), alpha_vec.begin() + 3);
    print_vector(alpha_vec2);

    std::cout << "push_back(), pop_back() test" << std::endl;
    alpha_vec.push_back('D');
    print_vector(alpha_vec);
    alpha_vec.pop_back();
    print_vector(alpha_vec);

    std::cout << "insert() test" << std::endl;
    alpha_vec.insert(alpha_vec.begin(), 'A');
    print_vector(alpha_vec);
    alpha_vec.insert(alpha_vec.end(), 3, 'Z');
    print_vector(alpha_vec);
    alpha_vec.insert(alpha_vec.end(), alpha_vec2.begin(), alpha_vec2.begin() + 3);
    print_vector(alpha_vec);

    std::cout << "erase() test" << std::endl;
    alpha_vec.erase(alpha_vec.begin());
    print_vector(alpha_vec);
    alpha_vec.erase(alpha_vec.end() - 1);
    print_vector(alpha_vec);
    alpha_vec.erase(alpha_vec.begin() + 1, alpha_vec.end() - 1);
    print_vector(alpha_vec);
    alpha_vec.erase(alpha_vec.end() - 1, alpha_vec.begin() + 1);
    print_vector(alpha_vec);

    std::cout << "## Operators test ##" << std::endl;
    std::cout << std::boolalpha << (alpha_vec == alpha_vec2) << std::endl;
    std::cout << std::boolalpha << (alpha_vec != alpha_vec2) << std::endl;
    std::cout << std::boolalpha << (alpha_vec < alpha_vec2) << std::endl;
    std::cout << std::boolalpha << (alpha_vec > alpha_vec2) << std::endl;
    std::cout << std::boolalpha << (alpha_vec <= alpha_vec2) << std::endl;
    std::cout << std::boolalpha << (alpha_vec >= alpha_vec2) << std::endl;
    std::cout << std::boolalpha << (alpha_vec == alpha_vec) << std::endl;

    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    std::cout << "Time taken by ft::vector is : "
    << std::fixed << time_taken << std::setprecision(6);
    std::cout << " sec " << std::endl;
}