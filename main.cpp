/* демоны, во что вы превратили мой си с классами */

#include <iostream>
#include "func_stuff.cpp"
#include "list.cpp"

using std::cout;
using std::endl;

template<typename A>
func plus (A a, A b) -> A
{
	return a + b;
}
template<typename A>
func mult (A a, A b) -> A
{
	return a * b;
}
template<typename A, typename B>
func minus (A a, B b) -> decltype(a - b)
{
	return a - b;
}

template<typename A>
fn<A(A, list<A>)>
	prod_from =
		curry(fnc(reduce<A, A>))(fnc(mult<A>));

template<typename A>
fn< fn<A(A)> (list<fn<A(A)>>) >
	concat =
		curry(prod_from<fn<A(A)>>)(id<A>);

template<typename A>
func middle (list<A> l) -> A
{
	l.sort();
	let middle = l.size() / 2;

	let it = l.begin();
	while (middle --> 0)
	{
		++it;
	}
	return *it;
}

template<typename A>
func to_char (A x) -> char
{
	return static_cast<char>(x);
}

fn<list<int>(int)> f1 = std::bind(range<int>, 0, _1, 1);

fn<int(list<int>)> f2 = middle<int>;

fn< list<fn<int(int)>> (int) > f3 =
	std::bind(replicate<fn<int(int)>>, _1, curry(fnc(plus<int>))(1));

fn< fn<int(int)> (list<fn<int(int)>>) > f4 = concat<int>;

fn<int(fn<int(int)>)> f5 = std::bind(call<int, int>, _1, 0);

fn< char(int) > f6 = to_char<int>;

let inter = curry(fnc(zip_with<int, unsigned char, int>))(minus<int, unsigned char>);


func main () -> int
{
	list<unsigned char> pre_start {70, 142, 2, 31, 115, 151, 148, 26, 202, 135, 121, 94, 28, 12, 103, 131, 42, 35, 170, 120, 44, 114, 28, 146, 142, 188, 200, 124, 203};
	list<int> minu5 {181, 433, 343, 141, 291, 385, 281, 382, 458, 240, 465, 415, 278, 242, 232, 407, 432, 392, 199, 463, 434, 238, 168, 265, 430, 236, 377, 349, 408};
	list<int> minu4 {151, 665, 436, 280, 339, 330, 320, 464, 622, 430, 664, 616, 194, 268, 511, 427, 472, 420, 459, 686, 475, 9, 232, 215, 499, 281, 588, 348, 584};
	list<int> minu3 {352, 538, 405, 355, 565, 151, 556, 425, 360, 251, 525, 522, 235, 548, 454, 247, 119, 310, 475, 597, 203, 97, 159, 288, 285, 529, 587, 208, 469};
	list<int> minu2 {370, 259, 344, 295, 420, 435, 267, 289, 359, 380, 435, 231, 433, 422, 325, 204, 307, 455, 325, 419, 391, 263, 433, 262, 220, 398, 422, 242, 337};
	list<int> minu1 {402, 228, 302, 209, 463, 545, 266, 216, 456, 515, 571, 116, 514, 392, 337, 135, 276, 505, 432, 522, 422, 260, 450, 262, 202, 572, 600, 208, 377};

	let operation = f6 *= f5 *= f4 *= f3 *= f2 *= f1;
	let step = curry(fnc(map<int, unsigned char>))(operation);
	let super_inter = curry(inter);

	let conveyor =
		   step *= super_inter(minu5)
		*= step *= super_inter(minu4)
		*= step *= super_inter(minu3)
		*= step *= super_inter(minu2)
		*= step *= super_inter(minu1);
	let end = conveyor(pre_start);

	for (let i : end)
	{
		cout << i;
	}
	cout<<endl;

	return 0;
}
