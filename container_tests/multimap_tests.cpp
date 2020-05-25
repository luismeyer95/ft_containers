/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multimultimap_tests.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 21:11:51 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/19 21:11:59 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "../Multimap.hpp"
#include "Containers.hpp"
#include <fstream>
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <class C>
int	multimap_tester()
{
	typedef typename C::value_type T;
	typedef typename C::iterator iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;

	C multimap;
	cout << "* creating multimap of size 0 *" << endl;
	c_info(multimap);
	cout << "Map empty() = " << (multimap.empty() ? "true" : "false") << ENDLL;
	cout << "Map max_size() = " << multimap.max_size() << std::endl;


	multimap.insert(T('c', 3));
	multimap.insert(T('e', 7));
	multimap.insert(T('b', 2));
	multimap.insert(T('b', 9));
	multimap.insert(T('a', 4));
	multimap.insert(T('d', 4));
	multimap.insert(T('k', 1));

	cout << "* inserted {c, e, b, b, a, d, k} consecutively *" << endl;
	c_info(multimap);

	{
		cout << "* checking return values / changes when inserting * :\n";
		iterator ret0 = multimap.insert(T('g', 10));
		iterator ret1 = multimap.insert(T('d', 0));
		bool ok = (ret0->first == 'g') && (ret1->first == 'd');
		cout << (ok ? "success" : "fail") << endl << endl;
		c_info(multimap);
		iterator it = multimap.insert(ft::fwd(multimap.begin(), 2), T('b', 4));
		cout << (it->first == 'b' ? "success" : "fail") << endl;

		c_info(multimap);
	}
	{
		cout << "* checking range-inserting * :\n";
		T arr[4] = {T('p', 4), T('m', 5), T('z', 6), T('o', 7)};
		multimap.insert(arr, arr + sizeof(arr) / sizeof(arr[0]));
		c_info(multimap);
	}
	

	cout << "Map size() = " << multimap.size() << std::endl;
	cout << "Map empty() = " << (multimap.empty() ? "true" : "false") << ENDLL;

	cout << "* iterators: begin() to end() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (iterator it = multimap.begin(); it != multimap.end(); ++it, ++i)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
			if (i != multimap.size() -1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << "* const iterators: begin() to end() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (const_iterator it = multimap.begin(); it != multimap.end(); ++it, ++i)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
			if (i != multimap.size() -1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << "* iterators: rbegin() to rend() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (reverse_iterator it = multimap.rbegin(); it != multimap.rend(); ++it, ++i)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
			if (i != multimap.size() -1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << endl;
	cout << " * erase() *" << endl;
	cout << "-> key parameter: erasing 'o', 'd', 'b'\n";
	multimap.erase('o');
	multimap.erase('d');
	multimap.erase('b');
	c_info(multimap);
	cout << "-> iterator parameter: erasing 'e' and 'k'\n";
	multimap.erase(ft::fwd(multimap.begin(), 2));
	multimap.erase(ft::fwd(multimap.begin(), 4));
	c_info(multimap);
	cout << "-> iterator range: erasing ['c', 'm'[\n";
	multimap.insert(T('c', 5));
	multimap.erase(ft::fwd(multimap.begin(), 2), ft::fwd(multimap.begin(), 4));
	c_info(multimap);

	{
		cout << "* constructors/assignment op *" << std::endl;
		cout << "-> construct from iterators [first + 1, last - 1]" << std::endl;
		C bis(ft::fwd(multimap.begin(), 1), ft::fwd(multimap.end(), -1));
		c_info(bis);
		cout << "-> copy construction" << std::endl;
		C ter(bis);
		c_info(ter);
		cout << "-> assignment (operator=)" << std::endl;
		ter = multimap;
		c_info(ter);
	}

	{
		cout << "* swap() *" << std::endl;
		cout << "-> printing multimap then multimap_bis" << std::endl;
		c_info(multimap);
		C bis(ft::fwd(multimap.begin(), 2), ft::fwd(multimap.end(), -1));
		c_info(bis);
		cout << "-> printing multimap then multimap_bis" << std::endl;
		multimap.swap(bis);
		c_info(multimap);
		c_info(bis);
		multimap.swap(bis);

		cout << "* clear() *" << std::endl;
		cout << "-> before clear()" << std::endl;
		c_info(bis);
		cout << "-> after clear()" << std::endl;
		bis.clear();
		c_info(bis);
	}

	cout << "* key_comp() *\n";
	bool valid = true;
	for (iterator it = multimap.begin(); it != ft::fwd(multimap.end(), -1); ++it)
		valid = valid && multimap.key_comp()(it->first, ft::fwd(it, 1)->first);
	cout << "-> " << (valid ? "success\n" : "fail\n");

	cout << "* value_comp() *\n";
	valid = true;
	for (iterator it = multimap.begin(); it != ft::fwd(multimap.end(), -1); ++it)
		valid = valid && multimap.value_comp()(*it, *ft::fwd(it, 1));
	cout << "-> " << (valid ? "success\n" : "fail\n");
	c_info(multimap);

	cout << "* find(), count() *\n";
	iterator find = multimap.find('b');
	if (find != multimap.end())
		cout << "-> 'b' found, multimapped = " << find->second << ", count = " << multimap.count('b') << endl;
	else
		cout << "-> 'b' not found, count = " << multimap.count('b') << endl;
	
	find = multimap.find('z');
	if (find != multimap.end())
		cout << "-> 'z' found, multimapped = " << find->second << ", count = " << multimap.count('z') << endl;
	else
		cout << "-> 'z' not found, count = " << multimap.count('z') << endl;

	find = multimap.find('y');
	if (find != multimap.end())
		cout << "-> 'y' found, multimapped = " << find->second << ", count = " << multimap.count('y') << endl;
	else
		cout << "-> 'y' not found, count = " << multimap.count('y') << endl;
	cout << endl;

	cout << "* lower_bound(), upper_bound() *\n";

	multimap.insert(T('q', 9));
	multimap.insert(T('w', 3));
	c_info(multimap);
	iterator low = multimap.lower_bound('c');
	cout << " -> lower_bound('c') = ";
	if (low != multimap.end())
		cout << low->first << endl;
	iterator high = multimap.upper_bound('p');
	cout << " -> upper_bound('p') = ";
	if (high != multimap.end())
		cout << high->first << endl;
	cout << " -> equal_range('m') = ";
	std::pair<iterator, iterator> range = multimap.equal_range('m');
	C bis(range.first, range.second);
	c_info(bis);
	cout << " -> equal_range('c') = ";
	range = multimap.equal_range('c');
	C ter(range.first, range.second);
	c_info(ter);

	cout << "* const multimap member access *\n--> ";
	const C bmultimap(multimap);
	bmultimap.begin();
	bmultimap.end();
	bmultimap.count('a');
	bmultimap.empty();
	bmultimap.equal_range('c');
	bmultimap.find('a');
	bmultimap.key_comp();
	bmultimap.value_comp();
	bmultimap.upper_bound('d');
	bmultimap.lower_bound('c');
	bmultimap.max_size();
	bmultimap.size();
	cout << "success" << endl;

	cout << "* iterators and constness *\n";
	C nc;
	nc.insert(T('c', 7));
	const_reverse_iterator crit = nc.rbegin();
	reverse_iterator rit = nc.rbegin();
	const_iterator cit = nc.begin();
	iterator it = nc.begin();
	bool types[4];
	types[0] = !ft::is_const(*it);
	types[1] = ft::is_const(*cit);
	types[2] = !ft::is_const(*rit);
	types[3] = ft::is_const(*crit);
	for (int i = 0; i < 4; ++i)
		cout << (types[i] ? "-> success" : "-> fail") << endl;
	cout << endl;
	
	return (0);
}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();
	
	std::ofstream real("./diffs/real_multimap.txt");
	std::cout.rdbuf(real.rdbuf());
	multimap_tester<std::multimap<char, int, std::less<char>, std::allocator<std::pair<const char, int> > > >();

	std::ofstream mine("./diffs/my_multimap.txt");
	std::cout.rdbuf(mine.rdbuf());
	multimap_tester<ft::multimap<char, int, std::less<char>, ft::allocator<std::pair<const char, int> > > >();
	
	std::cout.rdbuf(coutbuf);
}
