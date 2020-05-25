/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:49:05 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/24 13:50:49 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
#include <fstream>
#include "../Stack.hpp"
#include "Containers.hpp"
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <class C>
int	stack_tester()
{
	C stack;
	C other;

	stack.push(7);
	cout << stack.top() << endl;
	stack.push(5);
	cout << stack.top() << endl;
	stack.pop();

	other.push(7);
	cout << (other == stack ? "OK" : "FAIL") << endl;
	other.push(1);
	cout << (other == stack ? "FAIL" : "OK") << endl;

	cout << stack.top() << endl;
	stack.top()++;
	cout << stack.top() << endl;
	cout << stack.size() << endl;

	return (0);
}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();
	
	std::ofstream real("./diffs/real_stack.txt");
	std::cout.rdbuf(real.rdbuf());
	stack_tester< std::stack<int> >();

	std::ofstream mine("./diffs/my_stack.txt");
	std::cout.rdbuf(mine.rdbuf());
	stack_tester< ft::stack<int> >();

	std::cout.rdbuf(coutbuf);
}