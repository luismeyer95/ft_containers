/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 13:42:26 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/26 21:26:08 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include "../Containers.hpp"
#include <fstream>
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <class C>
int	map_tester()
{
	typedef typename C::value_type T;
	typedef typename C::iterator iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;

	C map;
	cout << "* creating map of size 0 *" << endl;
	c_info(map);
	cout << "Map empty() = " << (map.empty() ? "true" : "false") << ENDLL;
	cout << "Map max_size() = " << map.max_size() << std::endl;

	map['c'] = 3;
	map['e'] = 7;
	map['b'] = 2;
	map.insert(T('a', 4));
	map.insert(T('d', 4));
	map.insert(T('k', 1));

	cout << "* inserted {c, e, b, a, d, k} consecutively *" << endl;
	c_info(map);

	{
		cout << "* checking return values / changes when inserting * :\n";
		std::pair<iterator, bool> ret0 = map.insert(T('g', 10));
		std::pair<iterator, bool> ret1 = map.insert(T('d', 0));
		bool ok = (ret0.first->first == 'g' && ret0.second) && (ret1.first->first == 'd' && !ret1.second);
		cout << (ok ? "success" : "fail") << endl;
		iterator it = map.insert(ret1.first, T('f', 9));
		cout << (it->first == 'f' ? "success" : "fail") << endl;

		c_info(map);
	}
	{
		cout << "* checking range-inserting * :\n";
		T arr[4] = {T('p', 4), T('m', 5), T('z', 6), T('o', 7)};
		map.insert(arr, arr + sizeof(arr) / sizeof(arr[0]));
		c_info(map);
	}
	

	cout << "Map size() = " << map.size() << std::endl;
	cout << "Map empty() = " << (map.empty() ? "true" : "false") << ENDLL;

	cout << "* iterators: begin() to end() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (iterator it = map.begin(); it != map.end(); ++it, ++i)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
			if (i != map.size() - 1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << "* const iterators: begin() to end() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (const_iterator it = map.begin(); it != map.end(); ++it, ++i)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
			if (i != map.size() - 1)
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
	}
	cout << "* iterators: rbegin() to rend() *" << endl;
	{
		std::cout << "{ ";
		size_t i = 0;
		for (reverse_iterator it = map.rbegin(); it != map.rend(); ++it, ++i)
		{
			std::cout << "(" << it->first << ", " << it->second << ")";
			if (i != map.size() - 1)
				std::cout << ", ";
		}

	}
	cout << endl;
	cout << " * erase() *" << endl;
	cout << "-> key parameter: erasing 'o' and 'd'\n";
	map.erase('o');
	map.erase('d');
	c_info(map);
	cout << "-> iterator parameter: erasing 'e' and 'k'\n";
	map.erase(ft::fwd(map.begin(), 3));
	map.erase(ft::fwd(map.begin(), 5));
	c_info(map);
	cout << "-> iterator range: erasing ['c', 'm'[\n";
	map.erase(ft::fwd(map.begin(), 2), ft::fwd(map.begin(), 5));
	c_info(map);

	{
		cout << "* constructors/assignment op *" << std::endl;
		cout << "-> construct from iterators [first + 1, last - 1]" << std::endl;
		C bis(ft::fwd(map.begin(), 1), ft::fwd(map.end(), -1));
		c_info(bis);
		cout << "-> copy construction" << std::endl;
		C ter(bis);
		c_info(ter);
		cout << "-> assignment (operator=)" << std::endl;
		ter = map;
		c_info(ter);
	}

	{
		cout << "* swap() *" << std::endl;
		cout << "-> printing map then map_bis" << std::endl;
		c_info(map);
		C bis(ft::fwd(map.begin(), 2), ft::fwd(map.end(), -1));
		c_info(bis);
		cout << "-> printing map then map_bis" << std::endl;
		map.swap(bis);
		c_info(map);
		c_info(bis);
		map.swap(bis);

		cout << "* clear() *" << std::endl;
		cout << "-> before clear()" << std::endl;
		c_info(bis);
		cout << "-> after clear()" << std::endl;
		bis.clear();
		c_info(bis);
	}

	cout << "* key_comp() *\n";
	bool valid = true;
	for (iterator it = map.begin(); it != ft::fwd(map.end(), -1); ++it)
		valid = valid && map.key_comp()(it->first, ft::fwd(it, 1)->first);
	cout << "-> " << (valid ? "success\n" : "fail\n");

	cout << "* value_comp() *\n";
	valid = true;
	for (iterator it = map.begin(); it != ft::fwd(map.end(), -1); ++it)
		valid = valid && map.value_comp()(*it, *ft::fwd(it, 1));
	cout << "-> " << (valid ? "success\n" : "fail\n");
	c_info(map);

	cout << "* find(), count() *\n";
	iterator find = map.find('b');
	if (find != map.end())
		cout << "-> 'b' found, mapped = " << find->second << ", count = " << map.count('b') << endl;
	else
		cout << "-> 'b' not found, count = " << map.count('b') << endl;
	
	find = map.find('z');
	if (find != map.end())
		cout << "-> 'z' found, mapped = " << find->second << ", count = " << map.count('z') << endl;
	else
		cout << "-> 'z' not found, count = " << map.count('z') << endl;

	find = map.find('y');
	if (find != map.end())
		cout << "-> 'y' found, mapped = " << find->second << ", count = " << map.count('y') << endl;
	else
		cout << "-> 'y' not found, count = " << map.count('y') << endl;
	cout << endl;

	cout << "* lower_bound(), upper_bound() *\n";
	map['q'] = 9;
	map['w'] = 3;
	c_info(map);
	iterator low = map.lower_bound('c');
	cout << " -> lower_bound('c') = ";
	if (low != map.end())
		cout << low->first << endl;
	iterator high = map.upper_bound('p');
	cout << " -> upper_bound('p') = ";
	if (high != map.end())
		cout << high->first << endl;
	cout << " -> equal_range('m') = ";
	std::pair<iterator, iterator> range = map.equal_range('m');
	C bis(range.first, range.second);
	c_info(bis);
	cout << " -> equal_range('c') = ";
	range = map.equal_range('c');
	C ter(range.first, range.second);
	c_info(ter);

	cout << "* assigning from dereferenced non-const iterators *\n--> ";
	(map.begin())->second = 42;
	if (map['a'] == 42) { cout << "success"; }
	else { cout << "failed"; }
	cout << endl;

	cout << "* const map member access *\n--> ";
	const C bmap(map);
	bmap.begin();
	bmap.end();
	bmap.count('a');
	bmap.empty();
	bmap.equal_range('c');
	bmap.find('a');
	bmap.key_comp();
	bmap.value_comp();
	bmap.upper_bound('d');
	bmap.lower_bound('c');
	bmap.max_size();
	bmap.size();
	cout << "success" << endl;

	cout << "* iterators and constness *\n";
	C nc;
	nc['e'] = 8;
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
	
	std::ofstream real("./diffs/real_map.txt");
	std::cout.rdbuf(real.rdbuf());
	map_tester<std::map<char, int, std::less<char>, std::allocator<std::pair<const char, int> > > >();

	std::ofstream mine("./diffs/my_map.txt");
	std::cout.rdbuf(mine.rdbuf());
	map_tester<ft::map<char, int, std::less<char>, ft::allocator<std::pair<const char, int> > > >();
	
	std::cout.rdbuf(coutbuf);

	ft::map<int, char> bob;
	ft::map<int, char>::iterator it = bob.begin();
	ft::map<int, char>::const_iterator cit = bob.begin();
	ft::map<int, char>::reverse_iterator rit = bob.rbegin();
	ft::map<int, char>::const_reverse_iterator crit = bob.rbegin();

	// it = it;
	// it = cit;
	// it = rit;
	// it = crit;

	// cit = cit;
	// cit = it;
	// cit = rit;
	// cit = crit;

	// rit = rit;
	// rit = it;
	// rit = cit;
	// rit = crit;

	// crit = it;
	// crit = rit;
	// crit = cit;
	// crit = it;
	
}
