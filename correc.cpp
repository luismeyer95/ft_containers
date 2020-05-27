
#include "Containers.hpp"
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
		Foo() : arr(nullptr), n(0) {}
		Foo(int n) : n(n) { arr = new int[n]; }
		Foo(const Foo& o) : n(o.n) { arr = new int[n]; }
		Foo& operator=(const Foo& o)
		{
			if (arr)
				delete[] arr;
			n = o.n;
			arr = new int[n];
			return *this;
		}
		~Foo()
		{
			if (arr)
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

	iterator it = ct.begin();
	const_iterator cit = ct.begin();
	reverse_iterator rit = ct.rbegin();
	const_reverse_iterator crit = ct.rbegin();

	PRINT(ct.push_back(1));
	PRINT(ct.push_back(2));
	PRINT(ct.push_back(3));
	PRINT(ct.push_back(4));
	PRINT(ct.push_back(5));
	PRINT(ct.push_back(6));

	PRINT(ct.erase(ft::fwd(ct.begin(), 2), ft::fwd(ct.end(), -2)));

	int arr[] = {2, 7, 6, 13};


	PRINT(ct.insert(++ct.begin(), arr, arr + 4));
	// PRINT(ct.erase(ct.end()));
}

int main()
{
	std::cout << " ** real ** " << std::endl;
	ctnr_tester< std::vector<int> >();

	std::cout << " ** mine ** " << std::endl;
	ctnr_tester< ft::vector<int> >();


	ft::set<char> ct;
	ft::set<char>::iterator it = ct.begin();
	ft::set<char>::const_iterator cit = ct.begin();
	ft::set<char>::reverse_iterator rit = ct.rbegin();
	ft::set<char>::const_reverse_iterator crit = ct.rbegin();

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

