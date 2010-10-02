Assignment 3 - simple String Class

Necessary skills: class design, abstraction/encapsulation, constructors, destructor, heap memory management with C++ new/delete operators.

Description

Create a simple String class that represents a character string abstraction. The class must use the C++ new and delete operators to dynamically manage memory (in the heap) to store the character data. Provide the following member functions:

A constructor accepting a character pointer to an array of characters, with a default argument value of 0. If a null pointer or empty string is passed, it initializes the String object to point at an empty string (a one element character array with the value '\0') in the heap.
A copy constructor accepting a String object. It initializes this String from the parameter String object, making a deep copy of the character data.
A destructor that uses the C++ delete operator to free the heap character data owned by this String, and then sets the mpText pointer member to null.
A length member function returning the current size of the character data (not including the final null byte).
An asChar member function returning a const char pointer to this String's encapsulated character data. It does not allocate new memory for the char data to be returned.
An assign member function accepting a String object parameter. It checks for assignment to self, and assigns a new value to this String from the parameter String, making a deep copy of the character data (the C++ string library function strcpy_s can be used).
An assign member function accepting a character pointer. It checks for assignment to self, and assigns a new value to this String from the parameter character array.
An append member function accepting a String object parameter. It appends the parameter String object's character data to this String's character data.
An equals member function accepting a String object parameter, and a return type of bool. It compares the character data of 'this' String with the character data of the parameter String object and returns true if they match, else false (the C++ string library function strcmp can be used).
An equalsIgnoreCase member function accepting a String object parameter, and a return type of bool. It compares the character data of 'this' String with the character data of the parameter String object (ignoring case differences) and returns true if they match, else false (the C++ string library function stricmp can be used).
An indexOf member function accepting a character parameter, and a return type of int.  It searches this String's character data for the first occurrence of the parameter character and returns the position if found (first character is position 0) or -1 if not found.
Implementation Notes

Use the following code as the basis for your String class (the class name TString is used to prevent conflicts with any other String class). Put the complete class definition in a header file (TString.h) as follows:

 // -- TString.h header file --

#ifndef _TSTRING_H    // only include once in a compilation unit 
#define _TSTRING_H

class TString { // Prefix with 'T' for uniqueness
public:
  TString(const char *pText = 0); // default ctor
  // TODO: -- add remaining member function declarations here --

private:
  int mLength; // length of char data (not including null byte)
  char *mpText; // pointer to dynamic char data in heap
};

#endif   // _TSTRING_H
Place all the member function implementation code in a separate source file (TString.cpp). It requires a #include "TString.h" at the beginning of the file to include the class definition (above):

// -- TString.cpp source file --

#include "TString.h"

TString::TString(const char *pText) {
  ....
}

// TODO: -- Add remaining TString class member functions --
...
Use the C++ operators new and delete .in the TString class member functions to dynamically allocate and free the heap memory used to store the character data. Do not use malloc() and free().

TString parameter(s) in member functions should be defined as const reference parameters to (1) indicate the member function does not change the parameter, (2) improve performance since pass-by-ref doesn't make a copy of the caller's argument object, and (3) allow const objects to be used as arguments when calling the function.

TString member functions that do not change the state of 'this' object should be specified as const member functions to allow them to be invoked on const objects.

The class member mpText must always be assigned a pointer value obtained by calling the C++ new operator to allocate a character array in the heap, and never set to point at a non-heap address, e.g:

mpText = ""; // error - points to non-heap memory

The problem occurs when the C++ delete operator is used to free the character array pointed to by mpText. If mpText points to memory not obtained by calling the C++ new operator, memory corruption can occur, causing a program fault (possibly at a later point in the program)..

mpText must always point to a correctly sized dynamic character array, i.e., the class cannot just allocate a large character array (e.g. 500) and assume any text assigned will fit in that amount of space.  Each time a TString object is created, assigned to, appended to, etc., the memory allocated for character storage must be the correct size for the text to be stored.  Any existing dynamic memory must be released to prevent memory leaks.

The assign member function should check for assignment-to-self, and if so, simply return. Otherwise, it should acquire heap memory for the new character array prior to releasing the heap memory it already owns.

The append member function must create a new character array which contains the concatenated values of this TString and the parameter TString, and set it as the new value for this TString. It should allow for appending to self.  It can have an optimization to simply return if the parameter is an empty (length 0) TString.

Note that member functions with const TString&  parameters can be called with a char pointer argument due to C++ implicit conversion rules. C++ can silently call a single argument constructor to convert one type to another where needed. For example, if the equals() member function is called with a char* argument, C++ will silently invoke the TString(const char*) constructor to create a temporary TString object to pass as the argument. Thus, you will see an extra (unexpected) constructor call in this situation.

All member functions with character pointer parameters must test for a null pointer, and treat it as an empty (length 0) string (i.e: ""). Do not pass null pointers to the C++ string library functions (e.g: strlen), as it is not portable code (will not work on all platforms).

All member functions must manage heap memory correctly, and must not leak heap memory (i.e. they must delete any heap memory no longer used so it can be recycled).

The C++ string library functions (e.g: strlen, strcpy_s, strcat_s) may be used to implement the TString class member functions (e.g. use strcpy_s for copying char data instead of writing a for-loop). 

The C++ Standard Library string class (std::string) is not used in this assignment and should not be included in any of the code.

A few notes on pointers, arrays, and characters in C++

A null pointer typically contains 0 (NULL) and should never be de-referenced, nor passed to the C++ string library functions (e.g. strlen, strcat, strcmp, etc).
Neither C nor C++ have a built-in string type, only arrays of characters. By convention, C/C++ character arrays representing a "string" end in a terminating null byte ('\0'). The length returned by strlen() doesn't include the terminating null byte.
A double quoted set of characters ("hello world") is compiled as an unnamed array of characters with a terminating null byte, and placed in the initialized data area of the executable.
"x" is different than 'x'. The double-quoted "x" is a null terminated character array (2 chars required), whereas the single-quoted 'x' is a single character.
An octal escape sequence can be used to specify a octal character value (e.g: '\0' for a null byte containing 8 zero bits). Certain control characters can be specified with a character escape sequence (e.g: '\n' for newline, '\t' for tab, etc), which C++ converts to the correct character value.
When passing an array to a function in C/C++, a pointer to the first element is passed (arrays are not passed by value, but by reference).
p = ""; assigns the address of an empty (length 0) string literal (character array of size [1] with the value '\0') in the initialized data area of memory to the character pointer p.   p="hello"; assigns p the address of the first character of a six character array.   p = 'x'; sets the pointer to the binary value of the character 'x'.
If p and q both point at null terminated character arrays, p == q does not compare their character data values, only the pointer values. To compare the character data, use the C library strcmp_s() function, or an explicit loop that compares individual characters as *p == *q.
A character pointer can be indexed to access elements of the character array, e.g: p[n] addresses the n'th character in the array of characters pointed to by p. So does p+n