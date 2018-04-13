#pragma once

#include <list>
#include <functional>

template<typename A, typename B>
std::function<A(std::tuple<A,B>)> fst = std::bind(std::get<0, A, B>, std::placeholders::_1);

template<typename A, typename B>
std::function<B(std::tuple<A,B>)> snd = std::bind(std::get<1, A, B>, std::placeholders::_1);
