#pragma once

#include <tuple>
#include <functional>

using namespace std::placeholders;
using std::tuple;
#define fn std::function
#define func auto
#define let auto&&

template<typename R, typename... Args>
func fnc
(R (*f)(Args...)) -> fn<R(Args...)>
{
	return fn<R(Args...)>(f);
}

template<typename T>
func id (const T& t) -> T
{
	return t;
}

template<typename A, typename B, typename C>
func operator*
(const fn<C(B)>& outer, const fn<B(A)>& inner) -> fn<C(A)>
{
	return [inner, outer] (A a) -> C {
		return outer(inner(a));
	};
}

// associativity
template<typename A, typename B, typename C>
func operator*=
(const fn<C(B)>& outer, const fn<B(A)>& inner) -> fn<C(A)>
{
	return [inner, outer] (A a) -> C {
		return outer(inner(a));
	};
}

template<typename B, typename C, typename... Args>
func operator+
(const fn<B(Args...)>& left, const fn<C(Args...)>& right)
	-> fn<tuple<B, C>(Args...)>
{
	auto result = [left, right](Args&&... args) -> tuple<B, C>{
		return make_tuple(left(std::forward<Args>(args)...),
		                  right(std::forward<Args>(args)...));
	};
	return result;
}

template <typename R, typename A, typename... Other>
func curry
(const fn<R(A, Other...)>& f) -> fn<fn<R(Other...)>(A)>
{
	auto outer = [f](A a) -> fn<R(Other...)> {
		auto inner = [f, a](Other&&... args) -> R {
			return f(a, std::forward<Other>(args)...);
		};
		return inner;
	};
	return outer;
}

template <typename R, typename A, typename... Other>
func uncurry
(const fn<fn<R(Other...)>(A)>& f) -> fn<R(A, Other...)>
{
	auto result = [f](A a, Other&&... args) -> R {
		return f(a)(std::forward<Other>(args)...);
	};
	return result;
}

template<typename R, typename... Args>
func call
(const fn<R(Args...)>& f, Args... args) -> R
{
	return f(std::forward<Args>(args)...);
}
