# C++ for C Programmers [DRAFT](DRAFT.md) #
FIXME: motivate by explaining how C++ can be seen (and used) as a "better C than C".
FIXME: explain (easy), (medium), and (hard).


---


## Rename .c to .cpp (easy) ##
To take advantage of C++ features, you'll need to use the C++ compiler. The easiest way to do this is to use the `.cpp` extension instead of `.c`. Some people use `.cc` or `.cxx` instead, but `.cpp` is the most widely-used.

Note that you can't tell from a `.h` file's extension whether it's a C or C++ header file. Some people use `.hpp` to make this explicit. If you're able, the easiest is to just decree that all `.h` files are C++. (See later for the details of mixing C and C++.)


---


## `//` comments (easy) ##
You're probably already using C++'s `//` comments, which comment to end of line. They've been in C since C99, and were available as a non-standard extension in many compilers long before then. Use whatever you like:
```
// Single-line C++ comment.

/* Multi-line block
 * comment.
 */

// Multi-line C++
// comment.

/* Single-line block comment. */
```
(Both styles of multi-line comment are popular, but it's rare to see a C-style single-line block comment, just because it requires more keyboarding.)


---


## No more `typedef struct` (easy) ##
C programmers typically write:
```
typedef struct {
  int x;
  int y;
} DesiredName;
```
So they can later say `DesiredName` instead of `struct DesiredName`. In C++, you can simply write:
```
struct DesiredName {
  int x;
  int y;
};
```
And refer to `DesiredName` without having to prefix it with `struct`. This requires less keyboarding, and will sometimes lead to better behavior from tools: in the C version, there's an anonymous struct that's being `typedef`ed, and sometimes you'll be presented with that anonymous type's machine-generated name. In the C++ version, there's no anonymous type, so you'll only ever see the name you expect to see.


---


## No more `f(void)` (easy) ##
Another way to save a few keystrokes (but this time with no other benefit) is that functions that take no arguments can now be written without the bogus `void` parameter:
```
void f(void); /* C */
void f();     // C++
```
For compatibility with old code, in C, this meant "I'm not telling you anything about this function's arguments". In C++, it means "this function takes no arguments".


---


## Minimal-scope locals (easy) ##
FIXME: more intention-revealing.
FIXME: leads to more secure code (don't declare until you can assign an initial value, go out of scope as soon as you're finished).
FIXME: easier to detect unused locals.
FIXME: easier to break one big function into multiple smaller functions.
FIXME: harder to mix up two locals.
FIXME: for C++ objects, lets you control where/how many times the constructor/destructor get called.


---


## Mixing C and C++ (easy) ##
FIXME: extern "C".
FIXME: #ifdef


---


## `const` (medium) ##


---


## `new` instead of `malloc` (easy) ##
FIXME: no more `n*sizeof(T)`.
FIXME: no more `(T*)`.
FIXME: new and delete, new[.md](.md) and delete[.md](.md).
FIXME: don't mix new/free, malloc/delete.
FIXME: see also string, vector, and scoped\_ptr.


---


## `std::string` (easy) ##


---


## `std::vector` (easy) ##


---


## Named casts (medium) ##


---


## RAII (medium) ##


---


## Smart pointers (medium) ##


---


## `scoped_ptr` and `scoped_array` ##