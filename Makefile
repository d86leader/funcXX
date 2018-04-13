CXXFLAGS = -std=c++17 -O3

main: main.cpp func_stuff.cpp list.cpp tuple.cpp
	${CXX} $(CXXFLAGS) $< -o $@
