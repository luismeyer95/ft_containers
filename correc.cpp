
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


	ct.push_back(1);
	ct.push_back(2);
	ct.push_back(3);
	ct.push_back(4);
	ct.push_back(5);
	ct.push_back(6);

	const_iterator ita = ct.begin() + 2;
	iterator itb = ct.begin() + 6;

	const_reverse_iterator rita(ita);
	reverse_iterator ritb(itb);

	cout << ita - itb << endl;
	cout << itb - ita << endl;
	cout << rita - ritb << endl;
	cout << ritb - rita << endl;

	cout << rita[1] << endl;
}

int main()
{
	std::cout << " ** real ** " << std::endl;
	ctnr_tester< std::vector<int> >();

	std::cout << " ** mine ** " << std::endl;
	ctnr_tester< ft::vector<int> >();


	// ft::set<char> ct;
	// ft::set<char>::iterator it = ct.begin();
	// ft::set<char>::const_iterator cit = ct.begin();
	// ft::set<char>::reverse_iterator rit = ct.rbegin();
	// ft::set<char>::const_reverse_iterator crit = ct.rbegin();

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

