/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:11:45 by soyoungjung       #+#    #+#             */
/*   Updated: 2022/12/12 15:30:01 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sys/time.h> // gettimeofday()
#include <ios> // std::ios_base
#include <bits/stdc++.h>

template <typename M>
void print_map(M &map)
{
	for (typename M::iterator i = map.begin(); i != map.end(); ++i)
		std::cout << "Key : " << i->first << "\tValue : " << i->second << std::endl;
	std::cout << "Size :\t\t" << map.size() << std::endl
			  << std::endl;
}

void map_test(void)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);

	std::cout << "##############################" << std::endl;
	std::cout << "#                            #" << std::endl;
	std::cout << "#        FT::MAP TEST        #" << std::endl;
	std::cout << "#                            #" << std::endl;
	std::cout << "##############################" << std::endl
			  << std::endl;

	std::cout << "## Constructor & assignment test ##" << std::endl
			  << std::endl;
	std::cout << ">> Default constructor" << std::endl;
	ft::map<char, int> default_char;
	print_map(default_char);
	ft::map<int, int> default_int;
	print_map(default_int);
	ft::map<std::string, char> default_str;
	print_map(default_str);
	std::cout << ">> Range constructor" << std::endl;
	default_char.insert(ft::pair<char, int>('Q', 1));
	default_char.insert(ft::pair<char, int>('W', 2));
	default_char.insert(ft::pair<char, int>('E', 3));
	default_char.insert(ft::pair<char, int>('R', 4));
	default_char.insert(ft::pair<char, int>('T', 5));
	default_char.insert(ft::pair<char, int>('Y', 6));
	ft::map<char, int> range_char(default_char.begin(), default_char.end());
	print_map(range_char);
	ft::map<char, int> range_char2(default_char.rbegin(), default_char.rend());
	print_map(range_char2);
	std::cout << ">> Copy constructor" << std::endl;
	default_str.insert(ft::pair<std::string, char>("hi", 'a'));
	default_str.insert(ft::pair<std::string, char>("coffee", 'b'));
	default_str.insert(ft::pair<std::string, char>("hello", 'c'));
	default_str.insert(ft::pair<std::string, char>("good", 'd'));
	default_str.insert(ft::pair<std::string, char>("abc", 'e'));
	ft::map<std::string, char> range_str(default_str);
	print_map(range_str);
	std::cout << ">> Assignment operator" << std::endl;
	default_int.insert(ft::pair<int, int>(12, 1));
	default_int.insert(ft::pair<int, int>(3, 2));
	default_int.insert(ft::pair<int, int>(4, 3));
	default_int.insert(ft::pair<int, int>(56, 4));
	default_int.insert(ft::pair<int, int>(7, 5));
	default_int.insert(ft::pair<int, int>(89, 6));
	default_int.insert(ft::pair<int, int>(0, 7));
	ft::map<int, int> assign_int;
	assign_int = default_int;
	print_map(assign_int);

	std::cout << "## Iterator & reverse iterator test ##" << std::endl;
	ft::map<std::string, char>::iterator it1 = default_str.begin();
	ft::map<std::string, char>::iterator it2 = default_str.end();

	std::cout << it1->first << std::endl;
	std::cout << it1->second << std::endl;
	std::cout << (++it1)->first << std::endl;
	std::cout << (++it1)->second << std::endl;
	std::cout << (--it2)->first << std::endl;
	std::cout << (--it2)->second << std::endl;

	ft::map<char, int>::reverse_iterator rit1 = default_char.rbegin();
	ft::map<char, int>::reverse_iterator rit2 = default_char.rend();
	std::cout << rit1->first << std::endl;
	std::cout << rit1->second << std::endl;
	std::cout << (++rit1)->first << std::endl;
	std::cout << (++rit1)->second << std::endl;
	std::cout << (--rit2)->first << std::endl;
	std::cout << (--rit2)->second << std::endl;

	it1++;
	std::cout << it1->first << " " << it1->second << std::endl;
	rit1++;
	std::cout << rit1->first << " " << rit1->second << std::endl;
	rit2--;
	std::cout << rit2->first << " " << rit2->second << std::endl;

	std::cout << "## Allocator test ##" << std::endl;
	ft::map<int, int>::value_type *alloc1 = default_int.get_allocator().allocate(1);
	std::cout << sizeof(alloc1) << std::endl;
	ft::map<char, int>::value_type *alloc2 = default_char.get_allocator().allocate(1);
	std::cout << sizeof(alloc2) << std::endl;
	default_int.get_allocator().deallocate(alloc1, 1);
	default_char.get_allocator().deallocate(alloc2, 1);

	std::cout << "## Capacity test ##" << std::endl;
	ft::map<char, int> empty_char;
	std::cout << "is empty : " << std::boolalpha << empty_char.empty() << std::endl;
	std::cout << "size : " << empty_char.size() << std::endl;
	std::cout << "max size : " << empty_char.max_size() << std::endl;
	empty_char = default_char;
	std::cout << "is empty after assignment : " << std::boolalpha << empty_char.empty() << std::endl;
	std::cout << "size after assignment : " << empty_char.size() << std::endl;
	std::cout << "max size after assignment : " << empty_char.max_size() << std::endl;

	std::cout << "## Element access test ##" << std::endl;
	std::cout << ">> Operator[]" << std::endl;
	std::cout << "existing key : " << default_char['Q'] << std::endl;
	std::cout << "non existing key :" << default_char['S'] << std::endl;
	std::cout << "existing key : " << default_str["coffee"] << std::endl;
	std::cout << "non existing key :" << sizeof(default_str["42"]) << std::endl;
	std::cout << "existing key : " << default_int[7] << std::endl;
	std::cout << "non existing key :" << default_int[-5] << std::endl;

	std::cout << ">> At" << std::endl;
	try
	{
		std::cout << "existing key : " << default_char.at('W') << std::endl;
		std::cout << "non existing key : " << default_char.at('U') << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "existing key : " << default_str.at("good") << std::endl;
		std::cout << "non existing key : " << default_str.at("bad") << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}
	try
	{
		std::cout << "existing key : " << default_int.at(0) << std::endl;
		std::cout << "non existing key : " << default_int.at(1000) << std::endl;
	}
	catch (std::out_of_range &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "## Observers test ##" << std::endl;
	ft::map<char, int>::key_compare key_cmp1 = default_char.key_comp();
	ft::map<char, int>::value_compare val_cmp1 = default_char.value_comp();
	std::cout << "is 'Q' less than 'W' : " << key_cmp1('Q', 'W') << std::endl;
	std::cout << "is 'W' less than 'E' : " << val_cmp1(*(default_char.find('W')), *(default_char.find('E'))) << std::endl;
	ft::map<std::string, char>::key_compare key_cmp2 = default_str.key_comp();
	ft::map<std::string, char>::value_compare val_cmp2 = default_str.value_comp();
	std::cout << "is \"hello\" less than \"abc\" : " << key_cmp2("hello", "abc") << std::endl;
	std::cout << "is \"coffee\" less than \"hi\" : " << val_cmp2(*(default_str.find("coffee")), *(default_str.find("hi"))) << std::endl;

	std::cout << "## Lookup test ##" << std::endl;
	std::cout << ">> Count" << std::endl;
	std::cout << "non existing : " << default_char.count('A') << std::endl;
	std::cout << "existing : " << default_char.count('T') << std::endl;
	std::cout << "non existing : " << default_int.count(55) << std::endl;
	std::cout << "existing : " << default_int.count(7) << std::endl;
	std::cout << ">> Find" << std::endl;
	ft::map<char, int>::iterator char_ptr = default_char.find('Q');
	if (char_ptr == default_char.end())
		std::cout << "element not found" << std::endl;
	else
		std::cout << "key : " << (*char_ptr).first << " value : " << (*char_ptr).second << std::endl;
	char_ptr = default_char.find('G');
	if (char_ptr == default_char.end())
		std::cout << "element not found" << std::endl;
	else
		std::cout << "key : " << (*char_ptr).first << " value : " << (*char_ptr).second << std::endl;
	ft::map<std::string, char>::iterator str_ptr = default_str.find("abc");
	if (str_ptr == default_str.end())
		std::cout << "element not found" << std::endl;
	else
		std::cout << "key : " << (*str_ptr).first << " value : " << (*str_ptr).second << std::endl;
	str_ptr = default_str.find("nice");
	if (str_ptr == default_str.end())
		std::cout << "element not found" << std::endl;
	else
		std::cout << "key : " << (*str_ptr).first << " value : " << (*str_ptr).second << std::endl;

	std::cout << ">> Lower bound" << std::endl;
	char_ptr = default_char.lower_bound('R');
	if (char_ptr != default_char.end())
		std::cout << "key : " << char_ptr->first << " value : " << char_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;
	char_ptr = default_char.lower_bound('Z');
	if (char_ptr != default_char.end())
		std::cout << "key : " << char_ptr->first << " value : " << char_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;
	str_ptr = default_str.lower_bound("abc");
	if (str_ptr != default_str.end())
		std::cout << "key : " << str_ptr->first << " value : " << str_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;
	str_ptr = default_str.lower_bound("hi");
	if (str_ptr != default_str.end())
		std::cout << "key : " << str_ptr->first << " value : " << str_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;

	std::cout << ">> Upper bound" << std::endl;
	char_ptr = default_char.upper_bound('R');
	if (char_ptr != default_char.end())
		std::cout << "key : " << char_ptr->first << " value : " << char_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;
	char_ptr = default_char.upper_bound('Z');
	if (char_ptr != default_char.end())
		std::cout << "key : " << char_ptr->first << " value : " << char_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;
	str_ptr = default_str.upper_bound("abc");
	if (str_ptr != default_str.end())
		std::cout << "key : " << str_ptr->first << " value : " << str_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;
	str_ptr = default_str.upper_bound("hi");
	if (str_ptr != default_str.end())
		std::cout << "key : " << str_ptr->first << " value : " << str_ptr->second << std::endl;
	else
		std::cout << "key is upper than all the elements" << std::endl;

	std::cout << ">> Equal range" << std::endl;
	ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> char_pair;
	char_pair = default_char.equal_range('E');
	std::cout << (char_pair.first)->first << " is not less than 'E'"
			  << " and " << (char_pair.second)->first << " is greater than 'E'" << std::endl;
	ft::pair<ft::map<std::string, char>::iterator, ft::map<std::string, char>::iterator> str_pair;
	str_pair = default_str.equal_range("hello");
	std::cout << (str_pair.first)->first << " is not less than \"hello\""
			  << " and " << (str_pair.second)->first << " is greater than \"hello\"" << std::endl;

	std::cout << "## Modifier test ##" << std::endl;
	std::cout << ">> Unique insert" << std::endl;
	ft::pair<ft::map<char, int>::iterator, bool> res;
	res = default_char.insert(ft::pair<char, int>('A', 6));
	std::cout << "inserted element key : " << res.first->first << std::endl;
	std::cout << "is insert successful : " << res.second << std::endl;
	res = default_char.insert(ft::pair<char, int>('S', 7));
	std::cout << "inserted element key : " << res.first->first << std::endl;
	std::cout << "is insert successful : " << res.second << std::endl;
	res = default_char.insert(ft::pair<char, int>('D', 8));
	std::cout << "inserted element key : " << res.first->first << std::endl;
	std::cout << "is insert successful : " << res.second << std::endl;
	res = default_char.insert(ft::pair<char, int>('F', 9));
	std::cout << "inserted element key : " << res.first->first << std::endl;
	std::cout << "is insert successful : " << res.second << std::endl;
	res = default_char.insert(ft::pair<char, int>('Q', 1));
	std::cout << "inserted element key : " << res.first->first << std::endl;
	std::cout << "is insert successful : " << res.second << std::endl;
	res = default_char.insert(ft::pair<char, int>('W', 1));
	std::cout << "inserted element key : " << res.first->first << std::endl;
	std::cout << "is insert successful : " << res.second << std::endl;
	print_map(default_char);

	std::cout << ">> Unique insert with hint" << std::endl;
	ft::map<std::string, char>::iterator res2;
	res2 = default_str.insert(++(default_str.begin()), ft::pair<std::string, char>("cheer", 33));
	std::cout << "inserted element key : " << res2->first << std::endl;
	res2 = default_str.insert(default_str.begin(), ft::pair<std::string, char>("up!", 13));
	std::cout << "inserted element key : " << res2->first << std::endl;
	res2 = default_str.insert(--(default_str.end()), ft::pair<std::string, char>("friend", 42));
	std::cout << "inserted element key : " << res2->first << std::endl;
	print_map(default_str);

	std::cout << ">> Range insert" << std::endl;
	ft::map<std::string, char> new_str;
	ft::map<std::string, char>::iterator median_pos = default_str.find("good");
	new_str.insert(median_pos, default_str.end());
	print_map(new_str);
	new_str.insert(default_str.begin(), median_pos);
	print_map(new_str);
	new_str.insert(default_str.begin(), default_str.end());
	print_map(new_str);

	std::cout << ">> Unique erase with position" << std::endl;
	new_str.erase(new_str.find("hi"));
	print_map(new_str);
	new_str.erase(new_str.begin());
	print_map(new_str);
	default_char.erase(default_char.begin());
	print_map(default_char);
	default_char.erase(--(default_char.end()));
	print_map(default_char);

	std::cout << ">> Unique erase with key" << std::endl;
	ft::map<std::string, char>::size_type res_erase = new_str.erase("hello");
	std::cout << "number of erased element : " << res_erase << std::endl;
	print_map(new_str);
	res_erase = new_str.erase("NON-EXISTING_KEY");
	std::cout << "number of erased element : " << res_erase << std::endl;
	print_map(new_str);

	std::cout << ">> Range erase" << std::endl;
	new_str.erase(++(new_str.begin()), --(new_str.end()));
	print_map(new_str);
	new_str.erase(new_str.begin(), new_str.end());
	print_map(new_str);
	
	std::cout << ">> Swap test" << std::endl;
	default_str.swap(new_str);
	print_map(default_str);
	print_map(new_str);
	ft::map<std::string, char> empty_str;
	empty_str.swap(new_str);
	print_map(empty_str);
	print_map(new_str);

	std::cout << ">> Clear test" << std::endl;
	default_str.clear();
	std::cout << "is empty : " << default_str.empty() << std::endl;
	print_map(default_str);
	new_str.clear();
	print_map(new_str);

    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    std::cout << "Time taken by ft::map is : "
    << std::fixed << time_taken << std::setprecision(6);
    std::cout << " sec " << std::endl;
}
