#pragma once

#include <list>
#include <tuple>
#include <functional>
#include "tuple.cpp"
#include "func_stuff.cpp"

using std::list;
using std::tuple;

template<typename A, typename B, typename C>
func zip_with
(fn<C(A, B)> f, list<A> a, list<B> b) -> list<C>
{
	auto ai = a.begin();
	auto bi = b.begin();
	list<C> result;

	while (ai != a.end() and bi != b.end())
	{
		result.push_back(f(*ai, *bi));
		++ai; ++bi;
	}

	return result;
}

template<typename A, typename B>
func zip
(list<A> a, list<B> b) -> list<tuple<A, B>>
{
	fn<tuple<A,B>(A,B)> make_tuple (std::make_tuple<A, B>);
	return zip_with(make_tuple, a, b);
}

template<typename A, typename B>
func map
(fn<B(A)> f, list<A> l) -> list<B>
{
	list<B> result;
	for (auto i : l)
	{
		result.push_back(f(i));
	}
	return result;
}

template<typename A, typename S>
func reduce
(fn<S(S, A)> f, S s, list<A> l) -> S
{
	for (auto i : l)
	{
		s = f(s, i);
	}
	return s;
}

template<typename A, typename S>
func reduce_r
(fn<S(A, S)> f, list<A> l, S s) -> S
{
	for (auto it = l.rbegin(); it != l.rend(); ++it)
	{
		s = f(*it, s);
	}
	return s;
}

template<typename A>
func replicate
(size_t times, A val) -> list<A>
{
	list<A> result;
	for (size_t i = 0; i < times; ++i)
	{
		result.push_back(val);
	}
	return result;
}

template<typename A>
func tail
(list<A> l) -> list<A>
{
	list<A> result;
	if (l.size() < 2) return l;
	for (auto it = ++l.begin(); it != l.end(); ++it)
	{
		result.push_back(*it);
	}
	return result;
}

template<typename A>
func indicies
(list<A> l) -> list<size_t>
{
	list<size_t> result;
	size_t cur = 0;
	for (auto i : l)
	{
		result.push_back(cur);
		cur += 1;
	}
	return result;
}

template<typename A>
func drop_while
(fn<bool(A)> predicate, list<A> l) -> list<A>
{
	using Param = fn<list<A>(list<A>)>;
	fn<Param(A, Param)> combine(
			[&predicate](A next, Param rec) -> Param {
				if (predicate(next))
				{
					return rec * fnc(tail<A>);
				}
				else
				{
					return fnc(id<list<A>>);
				}
			});
	Param base = fnc(id<list<A>>);
	Param dropper = reduce_r(combine, l, base);
	return dropper(l);
}

template<typename A>
func range
(A begin, A end, A step = 1) -> list<A>
{
	list<A> result;
	while (begin < end)
	{
		result.push_back(begin);
		begin += step;
	}
	return result;
}

template<typename A>
func init
(list<A> l) -> A
{
	return l.front();
}
