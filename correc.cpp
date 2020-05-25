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

template <typename C>
void	ctnr_tester()
{
	typedef typename C::iterator iterator;
	typedef typename C::value_type value_type;
	typedef typename C::const_iterator const_iterator;
	typedef typename C::reverse_iterator reverse_iterator;
	typedef typename C::const_reverse_iterator const_reverse_iterator;

	value_type arr[] = {42, 3, 2, 6, 1};
	C vec(arr, arr + sizeof(arr)/sizeof(arr[0]));

	c_info(vec);

}

int main()
{
	std::cout << " ** real ** " << std::endl;
	ctnr_tester< std::vector<int> >();
	std::cout << std::endl;

	std::cout << " ** mine ** " << std::endl;
	ctnr_tester< ft::vector<int> >();
	std::cout << std::endl;
}

