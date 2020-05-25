/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tests.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:49:05 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/25 16:28:29 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "Containers.hpp"
#include "../List.hpp"
#include <fstream>
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <typename T>
bool	is_near(T a, T b)
{
	return a - b < 5;
}

template <class C>
int		list_tester()
{
	typedef typename C::value_type T;
	typedef typename C::iterator iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;
	
	{ // MODIFIERS
		C bob;

		cout << "* creating list, push front/back *" << endl;
		bob.push_front(1);
		bob.push_front(2);
		bob.push_front(69);
		bob.push_back(4);

		cout << "* normal and reverse iteration *" << endl;
		for (typename C::iterator b = bob.begin(); b != bob.end(); b++)
		cout << *b << " ";
		cout << endl;
		for (typename C::reverse_iterator rb = bob.rbegin(); rb != bob.rend(); rb++)
		cout << *rb << " ";
		cout << ENDLL;

		cout << "* front() and back() *" << endl;
		cout << "front : " << bob.front() << ", back : " << bob.back() << ENDLL;

		T arr[] = {9, 7, 5, 3, 1};
		cout << "* assigning from array *" << endl;
		bob.assign(arr, arr + sizeof(arr)/sizeof(arr[0]));
		c_info(bob);
		cout << endl;

		cout << "* pop front/back *" << endl;
		bob.pop_back();
		bob.pop_front();
		bob.pop_back();
		c_info(bob);
		cout << endl;

		cout << "* insertions *" << endl;
		bob.insert(ft::fwd(bob.begin(), 2), (T)42);
		bob.insert(++bob.end(), (T)0);
		bob.insert(ft::fwd(bob.end(), -2), arr + 1, arr + 3);
		bob.insert(++bob.begin(), 3ul, 9);
		c_info(bob);
		cout << endl;

		cout << "* erasing last element *" << endl;
		bob.erase(--bob.end());
		c_info(bob);
		cout << endl;

		cout << "* erasing elements [1, 5[ *" << endl;
		bob.erase(++bob.begin(), ft::fwd(bob.end(), -4));
		c_info(bob);
		cout << endl;

		cout << "* assignment operator '=' *  -->  ";
		C copy1 = bob;
		cout << std::string(copy1 == bob ? "success" : "failure") << endl;

		cout << "* copy constructor *  -->  ";
		C copy2(bob);
		cout << std::string(copy2 == bob ? "success" : "failure") << endl;

		cout << "* swap (both member and non-member) *  -->  ";
		C swp;
		swp.assign(arr, arr + sizeof(arr)/sizeof(T));
		swp.swap(copy1);
		cout << (swp == copy2 ? "success, " : "failure, ");
		std::swap(swp, copy1);
		cout << (copy1 == copy2 ? "success" : "failure") << ENDLL;

		cout << "* resizing {9, 7, 5, 3, 1} to 8, filling with 77 *" << endl;
		C one(swp);
		one.resize(8, 77);
		c_info(one);
		cout << "* resizing to 3 *" << endl;
		one.resize(3);
		c_info(one);
		cout << endl;

		cout << "* size(), clear() and empty() *  -->  ";
		cout << (one.size() == 3 ? "success, " : "failure, ");
		cout << (!one.empty() ? "success, " : "failure, ");
		one.clear();
		cout << (one.empty() ? "success" : "failure") << endl;
		c_info(one);
		cout << endl;

		cout << "* max_size() *" << endl;
		cout << "max_size = " << one.max_size() << ENDLL;

		// cout << "___________________________________________________" << ENDLL;


	}
	{ // LIST ALGORITHMS
		C bob;
		C joe;
		T aa[] = {1, 7, 9};
		T bb[] = {2, 8, 10};
		bob.assign(aa, aa + sizeof(aa)/sizeof(aa[0]));
		joe.assign(bb, bb + sizeof(bb)/sizeof(bb[0]));
		cout << "* initializing bob and joe *" << endl;
		c_info(bob);
		c_info(joe);
		cout << endl;

		cout << "* splicing entire list : bob.splice(bob.begin() + 2, joe) *" << endl;
		bob.splice(ft::fwd(bob.begin(), 2), joe);
		c_info(bob);
		c_info(joe);
		cout << endl;
		bob.assign(aa, aa + 3);
		joe.assign(bb, bb + 3);

		cout << "* splicing single elem : bob.splice(bob.begin() + 2, joe, --joe.end()) *" << endl;
		bob.splice(ft::fwd(bob.begin(), 2), joe, --joe.end());
		c_info(bob);
		c_info(joe);
		cout << endl;
		bob.assign(aa, aa + 3);
		joe.assign(bb, bb + 3);

		cout << "* splicing range : bob.splice(bob.begin() + 2, joe, ++joe.begin(), --joe.end()) *" << endl;
		bob.splice(ft::fwd(bob.begin(), 2), joe, ++joe.begin(), --joe.end());
		c_info(bob);
		c_info(joe);
		cout << endl;
		bob.assign(aa, aa + sizeof(aa)/sizeof(aa[0]));
		joe.assign(bb, bb + sizeof(bb)/sizeof(bb[0]));

		cout << "* remove(), remove_if() *" << endl;
		T cc[] = {4, 8, 5, 4, 8, 6, 10, 3, 4};
		C lcc;
		C bkp(lcc);
		lcc.assign(cc, cc + sizeof(cc)/sizeof(cc[0]));
		bkp = lcc;
		cout << "removing 4's : " << lcc;
		lcc.remove(4);
		cout << "  -->  " << lcc << endl;
		lcc = bkp;
		
		cout << "removing even numbers : " << lcc;
		lcc.remove_if(ft::is_even<T>);
		cout << "  -->  " << lcc << ENDLL;
		lcc = bkp;

		cout << "* sort() *" << endl;
		cout << "sort : " << lcc;
		lcc.sort();
		cout << "  -->  " << lcc << endl;
		lcc = bkp;
		cout << "sort(sort_descend) : " << lcc;
		lcc.sort(ft::sort_descend<T>);
		cout << "  -->  " << lcc << ENDLL;
		lcc = bkp;

		cout << "* merge() *" << endl;
		T dd[] = {7, 10, 2, 12, 18};
		C ldd;
		ldd.assign(dd, dd + sizeof(dd)/sizeof(dd[0]));
		C bkp2(ldd);
		ldd.sort();
		lcc.sort();
		cout << "A : " << lcc << endl;
		cout << "B : " << ldd << endl;
		lcc.merge(ldd);
		cout << "A  -->  " << lcc << endl;
		cout << "B  -->  " << ldd << ENDLL;
		lcc = bkp;
		ldd = bkp2;

		cout << "* merge() with comparison function *" << endl;
		ldd.sort(ft::sort_descend<T>);
		lcc.sort(ft::sort_descend<T>);
		cout << "A : " << lcc << endl;
		cout << "B : " << ldd << endl;
		lcc.merge(ldd, ft::sort_descend<T>);
		cout << "A  -->  " << lcc << endl;
		cout << "B  -->  " << ldd << ENDLL;
		
		C u1(lcc);
		cout << "* unique() *" << endl;
		cout << u1 << "  ->  ";
		u1.unique();
		cout << u1 << ENDLL;

		T uarr[] = {9, 5, 3, 45, 15, 23, 22, 87, 90};
		C u2(uarr, uarr + sizeof(uarr)/sizeof(uarr[0]));
		cout << "* unique(predicate) *" << endl;
		cout << u2 << "  ->  ";
		u2.unique(is_near<T>);
		cout << u2 << ENDLL;

		cout << "* reverse() *" << endl;
		cout << lcc << "  ->  ";
		lcc.reverse();
		cout << lcc << ENDLL;

	}

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
	cout << endl;
	
	return (0);
}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();
	
	std::ofstream real("./diffs/real_list.txt");
	std::cout.rdbuf(real.rdbuf());
	list_tester<std::list<int> >();
	comp_ops<std::list<std::string> >();

	std::ofstream mine("./diffs/my_list.txt");
	std::cout.rdbuf(mine.rdbuf());
	list_tester<ft::list<int> >();
	comp_ops<ft::list<std::string> >();

	std::cout.rdbuf(coutbuf);

}