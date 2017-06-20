/*!
    \file list.h
    \brief Intrusive list container definition
    \author Ivan Shynkarenka
    \date 20.06.2017
    \copyright MIT License
*/

#ifndef CPPCOMMON_INTRUSIVE_LIST_H
#define CPPCOMMON_INTRUSIVE_LIST_H

#include <cassert>
#include <iterator>

namespace CppCommon {

template <typename T>
class ListIterator;
template <typename T>
class ListConstIterator;
template <typename T>
class ListReverseIterator;
template <typename T>
class ListReverseConstIterator;


//! Intrusive list container
/*!
    Double linked list represents container with double-ended stock algorithm.
    It means that such container works like single linked list, but items  can
    be inserted/removed into/from both container ends (list begin, list end).

    \code
                    Front-<-------- Insert here and there ---->------Back
                      |                                               |
                   +-----+ Prev    +-----+ Prev    +-----+ Prev    +-----+
          Prev     |     |<--------|     |<--------|     |<--------|     |    Next
    NULL <---------|  1  |    Next |  2  |    Next |  3  |    Next |  4  |--------> NULL
                   |     |-------->|     |-------->|     |-------->|     |
                   +-----+         +-----+         +-----+         +-----+
                      |                                               |
                      +--->------ Remove from here and there -----<---+
    \endcode

    <b>Overview.</b>\n
    \image html List.png "Double linked list"
    In computer science,  a  linked  list  is  one  of  the  fundamental  data
    structures used in computer programming. It  consists  of  a  sequence  of
    nodes, each containing arbitrary data fields and  one  or  two  references
    ("links") pointing to the next and/or previous nodes. A linked list  is  a
    self-referential datatype because it contains a pointer or link to another
    data of the same type. Linked lists permit insertion and removal of  nodes
    at any point in the list in constant time, but do not allow random access.
    Several  different  types  of  linked  list  exist:  singly-linked  lists,
    doubly-linked lists, and circularly- linked lists.

    Linked lists can be implemented in most languages. Languages such as  Lisp
    and Scheme have the data structure built  in,  along  with  operations  to
    access the linked list. Procedural languages such  as  C,  C++,  and  Java
    typically rely on mutable references to create linked lists.

    <b>Doubly-linked list.</b>\n
    A more sophisticated kind of  linked  list  is  a  doubly-linked  list  or
    two-way linked list. Each node has two links: one points to  the  previous
    node, or points to a null value or empty list if it is the first node; and
    one points to the next, or points to a null value or empty list if  it  is
    the final node.

    <b>Applications of linked lists.</b>\n
    Linked lists are used as a building block for many other data  structures,
    such as stacks, queues and their variations.

    The "data" field of a node can be another linked list. By this device, one
    can construct many  linked  data  structures  with  lists;  this  practice
    originated in the Lisp programming language,  where  linked  lists  are  a
    primary (though by no means the only) data structure, and is now a  common
    feature of the functional programming style.

    Sometimes, linked lists are used to implement associative arrays, and are
    in this context called association lists. There is very little good to be
    said about this use of linked lists; they are easily outperformed by other
    data structures such as self-balancing binary search trees even on small
    data sets (see the discussion in associative array). However, sometimes a
    linked list is dynamically created out of a subset of nodes in such a tree,
    and used to more efficiently traverse that set.

    <b>Speeding up search.</b>\n
    Finding a specific element in  a  linked  list,  even  if  it  is  sorted,
    normally requires O(n) time (linear search). This is one  of  the  primary
    disadvantages of linked lists over other data structures. In  addition  to
    some of the variants discussed in the above section, there are  number  of
    simple ways of improving search time.

    In an unordered list, one simple heuristic for decreasing  average  search
    time is the move-to-front heuristic, which simply moves an element to  the
    beginning of the list once it is found. This scheme,  handy  for  creating
    simple caches, ensures that the most recently  used  items  are  also  the
    quickest to find again.

    Another common approach is to "index" a linked list using a more efficient
    external data structure. For example, one can build a  red-black  tree  or
    hash table whose  elements  are  references  to  the  linked  list  nodes.
    Multiple such indexes can be built on a single list. The  disadvantage  is
    that these indexes may need to be updated each time a  node  is  added  or
    removed (or at least, before that index is used again).

    <b>References.</b>\n
    \li National Institute of Standards  and  Technology  (August  16,  2004).
        Definition of a linked list. Retrieved December 14, 2004.
    \li Antonakos, James L. and Mansfield,  Kenneth  C.,  Jr.  Practical  Data
        Structures Using C/C++ (1999). Prentice-Hall. ISBN 0-13-280843-9,  pp.
        165-190
    \li Collins, William J. Data Structures and the Java Collections Framework
        (2002,2005) New York, NY: McGraw Hill. ISBN 0-07-282379-8, pp. 239-303
    \li Cormen, Thomas H.; Leiserson, Charles E.; Rivest,  Ronald  L.;  Stein,
        Clifford  Introductions  to  Algorithms  (2003).   MIT   Press.   ISBN
        0-262-03293-7, pp. 205-213, 501-505
    \li Green, Bert F. Jr. (1961). Computer Languages for Symbol Manipulation.
        IRE Transactions on Human Factors in Electronics. 2 pp. 3-8.
    \li McCarthy, John (1960). Recursive Functions of Symbolic Expressions and
        Their Computation by Machine, Part I. Communications of the ACM.  HTML
        DVI PDF PostScript
    \li Donald Knuth. Fundamental Algorithms, Third  Edition.  Addison-Wesley,
        1997. ISBN 0-201-89683-4. Sections 2.2.3-2.2.5, pp.254-298.
    \li Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford
        Stein. Introduction to  Algorithms,  Second  Edition.  MIT  Press  and
        McGraw-Hill, 2001. ISBN 0-262-03293-7.  Section  10.2:  Linked  lists,
        pp.204-209.
    \li Newell, Allen and Shaw, F. C. (1957).  Programming  the  Logic  Theory
        Machine. Proceedings of the Western  Joint  Computer  Conference.  pp.
        230-240.
    \li Parlante, Nick (2001). Linked list basics. Stanford University. PDF
    \li Sedgewick,  Robert  Algorithms  in  C  (1998).  Addison  Wesley.  ISBN
        0-201-31452-5, pp. 90-109
    \li Shaffer, Clifford A. A Practical Introduction to Data  Structures  and
        Algorithm Analysis (1998). NJ: Prentice Hall. ISBN 0-13-660911-2,  pp.
        77-102
    \li Wilkes, Maurice Vincent (1964). An Experiment  with  a  Self-compiling
        Compiler for a  Simple  List-Processing  Language.  Annual  Review  in
        Automatic Programming 4, 1. Published by Pergamon Press.
    \li Wilkes, Maurice  Vincent  (1964).  Lists  and  Why  They  are  Useful.
        Proceeds of  the  ACM  National  Conference,  Philadelphia  1964  (ACM
        Publication P-64 page F1-1); Also Computer Journal 7, 278 (1965).
    \li Kulesh Shanmugasundaram (April 4,  2005).  Linux  Kernel  Linked  List
        Explained.

    <b>Taken from:</b>\n
    Linked list from Wikipedia, the free encyclopedia
    http://en.wikipedia.org/wiki/Linked_list
*/
template <typename T>
class List
{
public:
    //! List node
    struct Node
    {
        T* next;    //!< Pointer to the next list node
        T* prev;    //!< Pointer to the previous list node
    };

    List() noexcept : _front(nullptr), _back(nullptr) {}
    List(const List&) noexcept = delete;
    List(List&&) noexcept = default;
    ~List() noexcept = default;

    List& operator=(const List&) noexcept = delete;
    List& operator=(List&&) noexcept = default;

    //! Check if the list is not empty
    explicit operator bool() const noexcept { return !empty(); }

    //! Is the list empty?
    bool empty() const noexcept { return _front == nullptr; }

    //! Get the list size
    size_t size() const noexcept;

    //! Get the front list item
    T* front() noexcept { return _front; }
    const T* first() const noexcept { return _first; }
    //! Get the back list item
    T* back() noexcept { return _back; }
    const T* back() const noexcept { return _back; }

    //! Get the begin list iterator
    ListIterator<T> begin() noexcept;
    ListConstIterator<T> begin() const noexcept;
    //! Get the end list iterator
    ListIterator<T> end() noexcept;
    ListConstIterator<T> end() const noexcept;

    //! Get the reverse begin list iterator
    ListReverseIterator<T> rbegin() noexcept;
    ListReverseConstIterator<T> rbegin() const noexcept;
    //! Get the reverse end list iterator
    ListReverseIterator<T> rend() noexcept;
    ListReverseConstIterator<T> rend() const noexcept;

    //! Push a new item into the front of the list
    /*!
        \param item - Pushed item
        \return The current list collection
    */
    List& PushFront(T& item) noexcept;
    //! Push a new item into the back of the list
    /*!
        \param item - Pushed item
        \return The current list collection
    */
    List& PushBack(T& item) noexcept;
    //! Push a new item as a next to the given one
    /*!
        \param base - Base item
        \param item - Pushed item
        \return The current list collection
    */
    List& PushNext(T& base, T& item) noexcept;
    //! Push a new item as a previous to the given one
    /*!
        \param base - Base item
        \param item - Pushed item
        \return The current list collection
    */
    List& PushPrev(T& base, T& item) noexcept;

    //! Pop the item from the front of the list
    /*!
        \return The front item popped from the list
    */
    T* PopFront() noexcept;
    //! Pop the item from the back of the list
    /*!
        \return The back item popped from the list
    */
    T* PopBack() noexcept;
    //! Pop the given item from the list
    /*!
        \param base - Base item
        \return The given item popped from the list
    */
    T* PopCurrent(T& base) noexcept;
    //! Pop the next item of the given one from the list
    /*!
        \param base - Base item
        \return The next item popped from the list
    */
    T* PopNext(T& base) noexcept;
    //! Pop the previous item of the given one from the list
    /*!
        \param base - Base item
        \return The previous item popped from the list
    */
    T* PopPrev(T& base) noexcept;

    //! Reverse the list
    void Reverse() noexcept;

    //! Swap two instances
    void swap(List& list) noexcept;
    template <typename U>
    friend void swap(List<U>& list1, List<U>& list2) noexcept;

private:
    T* _front;  //!< The front list node
    T* _back;   //!< The back list node
};

//! Intrusive list iterator
/*!
    Not thread-safe.
*/
template <typename T>
class ListIterator
{
    friend class List<T>;

public:
    // Standard iterator type definitions
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;

    ListIterator() noexcept : _current(nullptr) {}
    ListIterator(const ListIterator& it) noexcept = default;
    ListIterator(ListIterator&& it) noexcept = default;
    ~ListIterator() noexcept = default;

    ListIterator& operator=(const ListIterator& it) noexcept = default;
    ListIterator& operator=(ListIterator&& it) noexcept = default;

    friend bool operator==(const ListIterator& it1, const ListIterator& it2) noexcept
    { return it1._current == it2._current; }
    friend bool operator!=(const ListIterator& it1, const ListIterator& it2) noexcept
    { return it1._current != it2._current; }

    ListIterator& operator++() noexcept;
    ListIterator operator++(int) noexcept;

    T& operator*() noexcept;
    T* operator->() noexcept;

    //! Check if the iterator is valid
    explicit operator bool() const noexcept { return _current == nullptr; }

    //! Swap two instances
    void swap(ListIterator& it) noexcept;
    template <typename U>
    friend void swap(ListIterator<U>& it1, ListIterator<U>& it2) noexcept;

private:
    T* _current;

    ListIterator(T* current) noexcept : _current(current) {}
};

//! Intrusive list constant iterator
/*!
    Not thread-safe.
*/
template <typename T>
class ListConstIterator
{
    friend class List<T>;

public:
    // Standard constant iterator type definitions
    typedef const T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::forward_iterator_tag iterator_category;

    ListConstIterator() noexcept : _current(nullptr) {}
    ListConstIterator(const ListIterator<T>& it) noexcept : _current(it._current) {}
    ListConstIterator(const ListConstIterator& it) noexcept = default;
    ListConstIterator(ListConstIterator&& it) noexcept = default;
    ~ListConstIterator() noexcept = default;

    ListConstIterator& operator=(const ListIterator<T>& it) noexcept
    { _current = it._current; return *this; }
    ListConstIterator& operator=(const ListConstIterator& it) noexcept = default;
    ListConstIterator& operator=(ListConstIterator&& it) noexcept = default;

    friend bool operator==(const ListConstIterator& it1, const ListConstIterator& it2) noexcept
    { return it1._current == it2._current; }
    friend bool operator!=(const ListConstIterator& it1, const ListConstIterator& it2) noexcept
    { return it1._current != it2._current; }

    ListConstIterator& operator++() noexcept;
    ListConstIterator operator++(int) noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    //! Check if the iterator is valid
    explicit operator bool() const noexcept { return _current == nullptr; }

    //! Swap two instances
    void swap(ListConstIterator& it) noexcept;
    template <typename U>
    friend void swap(ListConstIterator<U>& it1, ListConstIterator<U>& it2) noexcept;

private:
    const T* _current;

    ListConstIterator(const T* current) noexcept : _current(current) {}
};

//! Intrusive list reverse iterator
/*!
    Not thread-safe.
*/
template <typename T>
class ListReverseIterator
{
    friend class List<T>;

public:
    // Standard iterator type definitions
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;

    ListReverseIterator() noexcept : _current(nullptr) {}
    ListReverseIterator(const ListReverseIterator& it) noexcept = default;
    ListReverseIterator(ListReverseIterator&& it) noexcept = default;
    ~ListReverseIterator() noexcept = default;

    ListReverseIterator& operator=(const ListReverseIterator& it) noexcept = default;
    ListReverseIterator& operator=(ListReverseIterator&& it) noexcept = default;

    friend bool operator==(const ListReverseIterator& it1, const ListReverseIterator& it2) noexcept
    { return it1._current == it2._current; }
    friend bool operator!=(const ListReverseIterator& it1, const ListReverseIterator& it2) noexcept
    { return it1._current != it2._current; }

    ListReverseIterator& operator++() noexcept;
    ListReverseIterator operator++(int) noexcept;

    T& operator*() noexcept;
    T* operator->() noexcept;

    //! Check if the iterator is valid
    explicit operator bool() const noexcept { return _current == nullptr; }

    //! Swap two instances
    void swap(ListReverseIterator& it) noexcept;
    template <typename U>
    friend void swap(ListReverseIterator<U>& it1, ListReverseIterator<U>& it2) noexcept;

private:
    T* _current;

    ListReverseIterator(T* current) noexcept : _current(current) {}
};

//! Intrusive list constant reverse iterator
/*!
    Not thread-safe.
*/
template <typename T>
class ListReverseConstIterator
{
    friend class List<T>;

public:
    // Standard constant iterator type definitions
    typedef const T value_type;
    typedef const T& reference;
    typedef const T* pointer;
    typedef std::forward_iterator_tag iterator_category;

    ListReverseConstIterator() noexcept : _current(nullptr) {}
    ListReverseConstIterator(const ListReverseIterator<T>& it) noexcept : _current(it._current) {}
    ListReverseConstIterator(const ListReverseConstIterator& it) noexcept = default;
    ListReverseConstIterator(ListReverseConstIterator&& it) noexcept = default;
    ~ListReverseConstIterator() noexcept = default;

    ListReverseConstIterator& operator=(const ListReverseIterator<T>& it) noexcept
    { _current = it._current; return *this; }
    ListReverseConstIterator& operator=(const ListReverseConstIterator& it) noexcept = default;
    ListReverseConstIterator& operator=(ListReverseConstIterator&& it) noexcept = default;

    friend bool operator==(const ListReverseConstIterator& it1, const ListReverseConstIterator& it2) noexcept
    { return it1._current == it2._current; }
    friend bool operator!=(const ListReverseConstIterator& it1, const ListReverseConstIterator& it2) noexcept
    { return it1._current != it2._current; }

    ListReverseConstIterator& operator++() noexcept;
    ListReverseConstIterator operator++(int) noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    //! Check if the iterator is valid
    explicit operator bool() const noexcept { return _current == nullptr; }

    //! Swap two instances
    void swap(ListReverseConstIterator& it) noexcept;
    template <typename U>
    friend void swap(ListReverseConstIterator<U>& it1, ListReverseConstIterator<U>& it2) noexcept;

private:
    const T* _current;

    ListReverseConstIterator(const T* current) noexcept : _current(current) {}
};

/*! \example intrusive_list.cpp Intrusive list container example */

} // namespace CppCommon

#include "list.inl"

#endif // CPPCOMMON_INTRUSIVE_LIST_H
