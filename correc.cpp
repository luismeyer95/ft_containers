#include "Vector.hpp"
#include "List.hpp"
#include "Stack.hpp"
#include "Map.hpp"
#include "Queue.hpp"
#include "Set.hpp"
#include "Multiset.hpp"
#include "Multimap.hpp"
#include "Deque.hpp"
#include "container_tests/Containers.hpp"

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <deque>
// #include <iostream>

using std::cout;
using std::endl;

#define PRINT(x) x;\
				c_info(ct);

class Foo
{
	private:
		int*	arr;
		int		n;
	public:
		Foo(int n) : n(n) { arr = new int[n]; }
		Foo(const Foo& o) : n(o.n) { arr = new int[n]; }
		Foo& operator=(const Foo& o)
		{
			delete[] arr;
			n = o.n;
			arr = new int[n];
			return *this;
		}
		~Foo()
		{
			delete[] arr;
			arr = nullptr;
		}
		friend std::ostream& operator<<(std::ostream& o, const Foo& foo)
		{
			o << "foo[" << foo.n << "]";
			return o;
		}
};



template <typename C>
void	ctnr_tester()
{
	typedef typename C::iterator iterator;
	typedef typename C::value_type value_type;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;

	C ct;
	typedef std::pair<char, Foo> pair;

	// ct['e'] = Foo(2);
	PRINT(ct.insert(pair('a', Foo(4))));
	PRINT(ct.insert(pair('y', Foo(5))));
	PRINT(ct.insert(pair('c', Foo(6))));
	PRINT(ct.insert(pair('b', Foo(7))));
	PRINT(ct.insert(pair('z', Foo(8))));
}

int main()
{
	std::cout << " ** real ** " << std::endl;
	ctnr_tester< std::map<char, Foo, std::greater<char> > >();

	std::cout << " ** mine ** " << std::endl;
	ctnr_tester< ft::map<char, Foo, std::greater<char> > >();

}

