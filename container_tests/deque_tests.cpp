/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 09:07:38 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:04:23 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include "../Deque.hpp"
#include "Containers.hpp"
#include <fstream>
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <class C>
int	deque_tester()
{
	typedef typename C::value_type T;
	typedef typename C::iterator iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;

	C dq;
	cout << "* creating deque of size 0 *" << endl;
	c_info(dq);
	cout << "Map empty() = " << (dq.empty() ? "true" : "false") << ENDLL;
	cout << "Map max_size() = " << dq.max_size() << std::endl;

	cout << "* construct and fill *" << endl;
	{
		C bis(size_t(6), 3);
		c_info(bis);
	}

	dq.push_back(1);
	dq.push_back(4);
	dq.push_back(2);
	dq.push_back(7);
	dq.push_back(9);


	cout << "* pushed {1, 4, 2, 7, 9} consecutively *" << endl;
	cout << "Front : " << dq.front() << ", back : " << dq.back() << endl;
	c_info(dq);
	dq.pop_back();
	dq.pop_back();

	cout << endl << "* popped 2 values *" << endl;
	c_info(dq);
	cout << endl;
	T arr[4] = { 9, 10, 11, 12};
	dq.insert(dq.begin() + 2, arr, arr + 4);
	cout << "* inserted array {9, 10, 11, 12} before the 2nd index *" << endl;
	c_info(dq);
	cout << endl;

	dq.erase(dq.begin() + 6);
	cout << "* erased dq[6] *" << endl;
	c_info(dq);
	cout << endl;

	dq.erase(dq.begin() + 2, dq.begin() + 5);
	cout << "* erased elements [2; 5[ *" << endl;
	c_info(dq);
	cout << endl;

	T arr2[10] = {4, 9, 18, 98, 7, 32, 1, -9, 5, 21};
	dq.assign(arr2, arr2 + sizeof(arr2)/sizeof(T));
	cout << "* assigning array {4, 9, 18, 98, 7, 32, 1, -9, 5, 21} to dq *" << endl;
	c_info(dq);

	cout << "* copy constructor / assignment operator '=' *  -->\n";
	C copy2(dq);
	cout << std::string(copy2 == dq ? "-> success" : "-> failure") << endl;
	C copy1;
	copy1 = dq;
	cout << std::string(copy1 == dq ? "-> success" : "-> failure") << endl;

	cout << "* swap (both member and non-member) *  -->  ";
	C swp;
	swp.assign(arr, arr + sizeof(arr)/sizeof(T));
	swp.swap(copy1);
	cout << std::string(swp == copy2 ? "success, " : "failure, ");
	ft::swap(swp, copy1);
	cout << std::string(copy1 == copy2 ? "success" : "failure") << endl;

	cout << "* normal and reverse iteration *" << endl;
	for (iterator b = dq.begin(); b != dq.end(); b++)
		cout << *b << " ";
	cout << endl;
	for (reverse_iterator rb = dq.rbegin(); rb != dq.rend(); rb++)
		cout << *rb << " ";
	cout << ENDLL;

	cout << "* assigning from dereferenced non-const iterators *  -->  ";
	*(dq.begin()) = 42;
	if (dq[0] == 42) { cout << "success"; }
	else { cout << "failed"; }
	cout << endl;

	cout << "* dq.at(i) && dq[i] *  -->  ";
	bool b = true;
	for (size_t i(0); i < dq.size(); i++)
		if (dq.at(i) != dq[i])
			b = false;
	cout << std::string(b ? "success" : "failed") << endl;

	cout << "* const and non-const overloads for op[] and at() *  -->  ";
	const C bob(arr2, arr2 + sizeof(arr2)/sizeof(T));
	cout << (ft::is_const(bob[0]) ? "success, " : "failure, ");
	cout << (ft::is_const(bob.at(0)) ? "success" : "failure") << endl;

	cout << "* out-of-range exception thrown when bound-checking with dq.at() *  -->  ";
	try {
		dq.at(10);
		cout << "failure" << endl;
	} catch (const std::out_of_range& e) {
		cout << "success" << endl;
	}

	cout << "* iterators and relational operations *\n";
	iterator itbeg = dq.begin();
	iterator itlast = dq.end() - 1;
	cout << "beg = " << *itbeg << ", end = " << *itlast << endl;
	cout << "last > beg ? " << (itlast > itbeg ? "success" : "fail") << endl;
	cout << "beg < last ? " << (itbeg < itlast ? "success" : "fail") << endl;
	cout << "last < end() ? " << (itlast < dq.end() ? "success" : "fail") << endl;
	reverse_iterator r_beg = dq.rbegin();
	reverse_iterator r_last = dq.rend() - 1;

	cout << "rbeg = " << *r_beg << ", end = " << *r_last << endl;
	cout << "rlast > rbeg ? " << (r_last > r_beg ? "success" : "fail") << endl;
	cout << "rbeg < rlast ? " << (r_beg < r_last ? "success" : "fail") << endl;
	cout << "rlast < rend() ? " << (r_last < dq.rend() ? "success" : "fail") << endl;
	cout << endl;

	cout << "* iterators and constness *\n";
	C nc;
	nc.push_back(3);
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

template <class C>
int	comp_ops()
{
	typedef typename C::value_type T;
	cout << "* comparison operator overloads *" << endl;
	T aa[] = {"yo", "ca", "va"}; 
	T bb[] = {"oui", "et", "toi"};
	T cc[] = {"le", "bon", "steak"};
	T dd[] = {"le", "cpp", "c cool"};
	C vaa(aa, aa + sizeof(aa)/sizeof(aa[0]));
	C vbb(bb, bb + sizeof(bb)/sizeof(bb[0]));
	C vcc(cc, cc + sizeof(cc)/sizeof(cc[0]));
	C vdd(dd, dd + sizeof(dd)/sizeof(dd[0]));
	cout << vaa << endl << vbb << endl << vcc << endl << vdd << endl;

	cout << "== --> " << std::string(vaa == vaa ? "success" : "failure") << endl;
	cout << "!= --> " << std::string(vaa != vbb ? "success" : "failure") << endl;
	cout << ">  --> " << std::string(vaa > vbb && vaa > vcc && vdd > vcc ? "success" : "failure") << endl;
	cout << ">= --> " << std::string(vaa >= vbb && vaa >= vaa ? "success" : "failure") << endl;
	cout << "<  --> " << std::string(vbb < vaa && vcc < vaa && vcc < vdd ? "success" : "failure") << endl;
	cout << "<= --> " << std::string(vbb <= vaa && vaa <= vaa ? "success" : "failure") << endl;
	return (0);
}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();
	
	std::ofstream real("./diffs/real_deque.txt");
	std::cout.rdbuf(real.rdbuf());
	deque_tester<std::deque<int, std::allocator<int> > >();
	comp_ops<std::deque<std::string, std::allocator<std::string> > >();

	std::ofstream mine("./diffs/my_deque.txt");
	std::cout.rdbuf(mine.rdbuf());
	deque_tester<ft::deque<int, ft::allocator<int> > >();
	comp_ops<ft::deque<std::string, ft::allocator<std::string> > >();

	std::cout.rdbuf(coutbuf);
}