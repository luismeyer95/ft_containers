/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:34:49 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 13:12:26 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Containers.hpp"
#include "../Set.hpp"
#include <set>
#include <fstream>
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <class C>
void set_tester()
{
	typedef typename C::value_type T;
	typedef typename C::iterator iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;

	C set;
	cout << "* creating set of size 0 *" << endl;
	c_info(set);
	cout << "Map empty() = " << (set.empty() ? "true" : "false") << ENDLL;
	cout << "Map max_size() = " << set.max_size() << std::endl;

	set.insert(3);
	set.insert(7);
	set.insert(2);
	set.insert(4);
	set.insert(4);

	cout << "* inserted {3, 7, 2, 4, 4, 5} consecutively *" << endl;
	c_info(set);

	{
		cout << "* checking return values / changes when inserting * :\n";
		std::pair<iterator, bool> ret0 = set.insert(4);
		std::pair<iterator, bool> ret1 = set.insert(8);
		bool ok = (*ret0.first == 4 && !ret0.second) && (*ret1.first == 8 && ret1.second);
		cout << (ok ? "success" : "fail") << endl;
		iterator it = set.insert(ret1.first, 5);
		cout << (*it == 5 ? "success" : "fail") << endl;

		c_info(set);
	}
	{
		cout << "* checking range-inserting * :\n";
		T arr[5] = {19, 2, 76, 34, 23};
		set.insert(arr, arr + sizeof(arr) / sizeof(arr[0]));
		c_info(set);
	}
	

	cout << "Map size() = " << set.size() << std::endl;
	cout << "Map empty() = " << (set.empty() ? "true" : "false") << ENDLL;

	cout << "* iterators: begin() to end() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (iterator it = set.begin(); it != set.end(); ++it, ++i)
		{
			std::cout << "(" << *it << ")";
			if (i != set.size() - 1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << "* const iterators: begin() to end() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (const_iterator it = set.begin(); it != set.end(); ++it, ++i)
		{
			std::cout << "(" << *it << ")";
			if (i != set.size() - 1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << "* iterators: rbegin() to rend() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (reverse_iterator it = set.rbegin(); it != set.rend(); ++it, ++i)
		{
			std::cout << "(" << *it << ")";
			if (i != set.size() - 1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << endl;
	cout << " * erase() *" << endl;
	cout << "-> key parameter: erasing 5 and 19\n";
	set.erase(5);
	set.erase(19);
	c_info(set);
	cout << "-> iterator parameter: erasing 7\n";
	set.erase(ft::fwd(set.begin(), 3));
	c_info(set);
	cout << "-> iterator range: erasing [8, 34[\n";
	set.erase(ft::fwd(set.begin(), 3), ft::fwd(set.begin(), 5));
	c_info(set);

	{
		cout << "* constructors/assignment op *" << std::endl;
		cout << "-> construct from iterators [first + 1, last - 1]" << std::endl;
		C bis(ft::fwd(set.begin(), 1), ft::fwd(set.end(), -1));
		c_info(bis);
		cout << "-> copy construction" << std::endl;
		C ter(bis);
		c_info(ter);
		cout << "-> assignment (operator=)" << std::endl;
		ter = set;
		c_info(ter);
	}

	{
		cout << "* swap() *" << std::endl;
		cout << "-> printing set then set_bis" << std::endl;
		c_info(set);
		C bis(ft::fwd(set.begin(), 2), ft::fwd(set.end(), -1));
		c_info(bis);
		cout << "-> printing set then set_bis" << std::endl;
		set.swap(bis);
		c_info(set);
		c_info(bis);
		set.swap(bis);

		cout << "* clear() *" << std::endl;
		cout << "-> before clear()" << std::endl;
		c_info(bis);
		cout << "-> after clear()" << std::endl;
		bis.clear();
		c_info(bis);
	}

	cout << "* key_comp() *\n";
	bool valid = true;
	for (iterator it = set.begin(); it != ft::fwd(set.end(), -1); ++it)
		valid = valid && set.key_comp()(*it, *ft::fwd(it, 1));
	cout << "-> " << (valid ? "success\n" : "fail\n");

	cout << "* value_comp() *\n";
	valid = true;
	for (iterator it = set.begin(); it != ft::fwd(set.end(), -1); ++it)
		valid = valid && set.value_comp()(*it, *ft::fwd(it, 1));
	cout << "-> " << (valid ? "success\n" : "fail\n");
	c_info(set);

	cout << "* find(), count() *\n";
	iterator find = set.find(3);
	if (find != set.end())
		cout << "-> 3 found, count = " << set.count(3) << endl;
	else
		cout << "fail\n";

	cout << "* lower_bound(), upper_bound() *\n";
	set.insert(7);
	set.insert(9);
	set.insert(17);
	c_info(set);
	iterator low = set.lower_bound(7);
	cout << " -> lower_bound(7) = ";
	if (low != set.end())
		cout << *low << endl;
	iterator high = set.upper_bound(32);
	cout << " -> upper_bound(32) = ";
	if (high != set.end())
		cout << *high << endl;
	cout << " -> equal_range(3) = ";
	std::pair<iterator, iterator> range = set.equal_range(3);
	C bis(range.first, range.second);
	c_info(bis);
	cout << " -> equal_range(76) = ";
	range = set.equal_range(76);
	C ter(range.first, range.second);
	c_info(ter);


	cout << "* const set member access *\n--> ";
	const C bset(set);
	bset.begin();
	bset.end();
	bset.count('a');
	bset.empty();
	bset.equal_range('c');
	bset.find('a');
	bset.key_comp();
	bset.value_comp();
	bset.upper_bound('d');
	bset.lower_bound('c');
	bset.max_size();
	bset.size();
	cout << "success" << endl;

	cout << "* iterators and constness *\n";
	C nc;
	nc.insert(8);
	const_reverse_iterator crit = nc.rbegin();
	reverse_iterator rit = nc.rbegin();
	const_iterator cit = nc.begin();
	iterator it = nc.begin();
	bool types[4];
	types[0] = ft::is_const(*it);
	types[1] = ft::is_const(*cit);
	types[2] = ft::is_const(*rit);
	types[3] = ft::is_const(*crit);
	for (int i = 0; i < 4; ++i)
		cout << (types[i] ? "-> success" : "-> fail") << endl;
	cout << endl;
}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();
	
	std::ofstream real("./diffs/real_set.txt");
	std::cout.rdbuf(real.rdbuf());
	set_tester< std::set<int> >();

	std::ofstream mine("./diffs/my_set.txt");
	std::cout.rdbuf(mine.rdbuf());
	set_tester< ft::set<int> >();

	std::cout.rdbuf(coutbuf);
}
