/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:49:05 by lumeyer           #+#    #+#             */
/*   Updated: 2020/05/26 21:27:04 by lumeyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <queue>
#include <iostream>
#include <fstream>
#include "../Containers.hpp"
#define ENDLL endl << endl
using std::cout;
using std::endl;

template <class C>
int	queue_tester()
{
	C queue;
	C other;

	queue.push(7);
	cout << queue.back() << endl;
	queue.push(5);
	cout << queue.back() << endl;
	queue.pop();

	other.push(5);
	cout << (other == queue ? "OK" : "FAIL") << endl;
	other.push(1);
	cout << (other == queue ? "FAIL" : "OK") << endl;

	cout << queue.front() << endl;
	queue.front()++;
	cout << queue.front() << endl;
	cout << queue.size() << endl;

	return (0);
}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();
	
	std::ofstream real("./diffs/real_queue.txt");
	std::cout.rdbuf(real.rdbuf());
	queue_tester< std::queue<int> >();

	std::ofstream mine("./diffs/my_queue.txt");
	std::cout.rdbuf(mine.rdbuf());
	queue_tester< ft::queue<int> >();

	std::cout.rdbuf(coutbuf);
}