# funcXX - SiBears training task for 2018-04-13
You have just learned about allocators. Time to use them! This program uses a lot of allocations, and one of them contains the flag sought for. Get the flag!

### Hints
 - It probably won't work if you derive from `std::allocator`. Try writing your own and using member `std::allocator`
 - Printing memory on deallocation might not work, it's better to print it on object construction
 - List nodes can't be printed, but you can access their member data and print it
