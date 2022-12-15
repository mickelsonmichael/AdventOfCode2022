# Day 12: Hill Climbing Algorithm

Starting day 12 on day 15. Hopefully this one takes less time than others so I can finally make up some lost ground.
I think I'm starting to realize that if I ever want to make it to day 25 on time, I'm going to have to buckle down
and actually code on the weekends.

Working on part 1 currently, and I'm just getting slapped in the face with pointer issues, `const` issues, and any other kind of C++ specific issue you can think of.
My current bug is, I suspect, due to another copy constructor being called.
To remove that and hopefully diagnose the line, I added the required `Node(const Node &n) = delete;` to explicitly delete the copy constructor.
That results in the following _extremely ugly error_:

```raw
In file included from /usr/include/x86_64-linux-gnu/c++/7/bits/c++allocator.h:33:0,
                 from /usr/include/c++/7/bits/allocator.h:46,
                 from /usr/include/c++/7/string:41,
                 from /usr/include/c++/7/bits/locale_classes.h:40,
                 from /usr/include/c++/7/bits/ios_base.h:41,
                 from /usr/include/c++/7/ios:42,
                 from /usr/include/c++/7/ostream:38,
                 from /usr/include/c++/7/iostream:39,
                 from main.cpp:1:
/usr/include/c++/7/ext/new_allocator.h: In instantiation of ‘void __gnu_cxx::new_allocator<_Tp>::construct(_Up*, _Args&& ...) [with _Up = Node; _Args = {Node}; _Tp = Node]’:
/usr/include/c++/7/bits/alloc_traits.h:475:4:   required from ‘static void std::allocator_traits<std::allocator<_CharT> >::construct(std::allocator_traits<std::allocator<_CharT> >::allocator_type&, _Up*, _Args&& ...) [with _Up = Node; _Args = {Node}; _Tp = Node; std::allocator_traits<std::allocator<_CharT> >::allocator_type = std::allocator<Node>]’
/usr/include/c++/7/bits/vector.tcc:100:30:   required from ‘void std::vector<_Tp, _Alloc>::emplace_back(_Args&& ...) [with _Args = {Node}; _Tp = Node; _Alloc = std::allocator<Node>]’
/usr/include/c++/7/bits/stl_vector.h:954:21:   required from ‘void std::vector<_Tp, _Alloc>::push_back(std::vector<_Tp, _Alloc>::value_type&&) [with _Tp = Node; _Alloc = std::allocator<Node>; std::vector<_Tp, _Alloc>::value_type = Node]’
topography.cpp:98:65:   required from here
/usr/include/c++/7/ext/new_allocator.h:136:4: error: use of deleted function ‘Node::Node(const Node&)’
  { ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from topography.cpp:6:0,
                 from main.cpp:8:
node.cpp:13:5: note: declared here
     Node(const Node &n) = delete;
     ^~~~
In file included from /usr/include/c++/7/bits/stl_algobase.h:71:0,
                 from /usr/include/c++/7/bits/char_traits.h:39,
                 from /usr/include/c++/7/ios:40,
                 from /usr/include/c++/7/ostream:38,
                 from /usr/include/c++/7/iostream:39,
                 from main.cpp:1:
/usr/include/c++/7/bits/predefined_ops.h: In instantiation of ‘bool __gnu_cxx::__ops::_Iter_pred<_Predicate>::operator()(_Iterator) [with _Iterator = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _Predicate = Topography::steps_to_optimal_signal() const::<lambda(const size_t&, const size_t&)>::<lambda(Node)>]’:
/usr/include/c++/7/bits/stl_algo.h:120:14:   required from ‘_RandomAccessIterator std::__find_if(_RandomAccessIterator, _RandomAccessIterator, _Predicate, std::random_access_iterator_tag) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _Predicate = __gnu_cxx::__ops::_Iter_pred<Topography::steps_to_optimal_signal() const::<lambda(const size_t&, const size_t&)>::<lambda(Node)> >]’
/usr/include/c++/7/bits/stl_algo.h:161:23:   required from ‘_Iterator std::__find_if(_Iterator, _Iterator, _Predicate) [with _Iterator = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _Predicate = __gnu_cxx::__ops::_Iter_pred<Topography::steps_to_optimal_signal() const::<lambda(const size_t&, const size_t&)>::<lambda(Node)> >]’
/usr/include/c++/7/bits/stl_algo.h:3932:28:   required from ‘_IIter std::find_if(_IIter, _IIter, _Predicate) [with _IIter = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _Predicate = Topography::steps_to_optimal_signal() const::<lambda(const size_t&, const size_t&)>::<lambda(Node)>]’
topography.cpp:113:53:   required from here
/usr/include/c++/7/bits/predefined_ops.h:283:11: error: use of deleted function ‘Node::Node(const Node&)’
  { return bool(_M_pred(*__it)); }
           ^~~~~~~~~~~~~~~~~~~~
In file included from topography.cpp:6:0,
                 from main.cpp:8:
node.cpp:13:5: note: declared here
     Node(const Node &n) = delete;
     ^~~~
In file included from main.cpp:8:0:
topography.cpp:112:30: note:   initializing argument 1 of ‘Topography::steps_to_optimal_signal() const::<lambda(const size_t&, const size_t&)>::<lambda(Node)>’
                 [r, c](Node n)
                              ^
In file included from /usr/include/c++/7/vector:62:0,
                 from main.cpp:3:
/usr/include/c++/7/bits/stl_construct.h: In instantiation of ‘void std::_Construct(_T1*, _Args&& ...) [with _T1 = Node; _Args = {const Node&}]’:
/usr/include/c++/7/bits/stl_uninitialized.h:83:18:   required from ‘static _ForwardIterator std::__uninitialized_copy<_TrivialValueTypes>::__uninit_copy(_InputIterator, _InputIterator, _ForwardIterator) [with _InputIterator = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _ForwardIterator = Node*; bool _TrivialValueTypes = false]’
/usr/include/c++/7/bits/stl_uninitialized.h:134:15:   required from ‘_ForwardIterator std::uninitialized_copy(_InputIterator, _InputIterator, _ForwardIterator) [with _InputIterator = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _ForwardIterator = Node*]’
/usr/include/c++/7/bits/stl_uninitialized.h:289:37:   required from ‘_ForwardIterator std::__uninitialized_copy_a(_InputIterator, _InputIterator, _ForwardIterator, std::allocator<_Tp>&) [with _InputIterator = __gnu_cxx::__normal_iterator<const Node*, std::vector<Node> >; _ForwardIterator = Node*; _Tp = Node]’
/usr/include/c++/7/bits/stl_vector.h:331:31:   required from ‘std::vector<_Tp, _Alloc>::vector(const std::vector<_Tp, _Alloc>&) [with _Tp = Node; _Alloc = std::allocator<Node>]’
topography.cpp:107:26:   required from here
/usr/include/c++/7/bits/stl_construct.h:75:7: error: use of deleted function ‘Node::Node(const Node&)’
     { ::new(static_cast<void*>(__p)) _T1(std::forward<_Args>(__args)...); }
       ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from topography.cpp:6:0,
                 from main.cpp:8:
node.cpp:13:5: note: declared here
     Node(const Node &n) = delete;
     ^~~~
In file included from /usr/include/c++/7/vector:62:0,
                 from main.cpp:3:
/usr/include/c++/7/bits/stl_construct.h: In instantiation of ‘void std::_Construct(_T1*, _Args&& ...) [with _T1 = Node; _Args = {Node}]’:
/usr/include/c++/7/bits/stl_uninitialized.h:83:18:   required from ‘static _ForwardIterator std::__uninitialized_copy<_TrivialValueTypes>::__uninit_copy(_InputIterator, _InputIterator, _ForwardIterator) [with _InputIterator = std::move_iterator<Node*>; _ForwardIterator = Node*; bool _TrivialValueTypes = false]’
/usr/include/c++/7/bits/stl_uninitialized.h:134:15:   required from ‘_ForwardIterator std::uninitialized_copy(_InputIterator, _InputIterator, _ForwardIterator) [with _InputIterator = std::move_iterator<Node*>; _ForwardIterator = Node*]’
/usr/include/c++/7/bits/stl_uninitialized.h:289:37:   required from ‘_ForwardIterator std::__uninitialized_copy_a(_InputIterator, _InputIterator, _ForwardIterator, std::allocator<_Tp>&) [with _InputIterator = std::move_iterator<Node*>; _ForwardIterator = Node*; _Tp = Node]’
/usr/include/c++/7/bits/stl_uninitialized.h:311:2:   required from ‘_ForwardIterator std::__uninitialized_move_if_noexcept_a(_InputIterator, _InputIterator, _ForwardIterator, _Allocator&) [with _InputIterator = Node*; _ForwardIterator = Node*; _Allocator = std::allocator<Node>]’
/usr/include/c++/7/bits/vector.tcc:426:6:   required from ‘void std::vector<_Tp, _Alloc>::_M_realloc_insert(std::vector<_Tp, _Alloc>::iterator, _Args&& ...) [with _Args = {Node}; _Tp = Node; _Alloc = std::allocator<Node>; std::vector<_Tp, _Alloc>::iterator = __gnu_cxx::__normal_iterator<Node*, std::vector<Node> >; typename std::_Vector_base<_Tp, _Alloc>::pointer = Node*]’
/usr/include/c++/7/bits/vector.tcc:105:21:   required from ‘void std::vector<_Tp, _Alloc>::emplace_back(_Args&& ...) [with _Args = {Node}; _Tp = Node; _Alloc = std::allocator<Node>]’
/usr/include/c++/7/bits/stl_vector.h:954:21:   required from ‘void std::vector<_Tp, _Alloc>::push_back(std::vector<_Tp, _Alloc>::value_type&&) [with _Tp = Node; _Alloc = std::allocator<Node>; std::vector<_Tp, _Alloc>::value_type = Node]’
topography.cpp:98:65:   required from here
/usr/include/c++/7/bits/stl_construct.h:75:7: error: use of deleted function ‘Node::Node(const Node&)’
     { ::new(static_cast<void*>(__p)) _T1(std::forward<_Args>(__args)...); }
       ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from topography.cpp:6:0,
                 from main.cpp:8:
node.cpp:13:5: note: declared here
     Node(const Node &n) = delete;
     ^~~~
```
It took a good walk before I realized that the `vector::push_back` method creates a copy.
To avoid this, I instead need to work with pointers directly.
Which inevitably means more `Segmentation fault`s.
