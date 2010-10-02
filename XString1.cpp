//-----------------------------------------------------------------------------
// XString1.cpp - Test program for simple String class
//-----------------------------------------------------------------------------

/*
 * Note: If using MS VC++, you will create this project with multiple files.
 * TString.h, TString.cpp, and this file (XString1.cpp) that contains main().
 *
 * Click File->New, select the Project tab, and "Win32 console application"
 * to create the new project. Select the location for the project,
 * enter the project name (eg. Proj2), and Click OK.  On the next window,
 * select "Empty Project", and click Finish.
 *
 * Click on the "FileView" tab in the left window to see the Source, Header,
 * and Resource files in your project (none to start).
 *
 * Click File->New, "C/C++ Header File" to create your TString.h header file.
 * This file will contain your class definition, which is included into any
 * file that will use your TString class.
 *
 * Click File->New, "C++ Source File" to create your TString.cpp source file.
 * This file will contain the member functions implementing your TString class.
 * It must #include "TString.h" to have the compiler see the header when
 * compiling it.
 *
 * Copy this file (XString1.cpp) into your project directory.
 *
 * Click Project->Add To Project->Files, select this file (XString1.cpp) from
 * the browse window, and click OK.
 *
 * Your project should now contain the Source files TString.cpp and XString1.cpp,
 * and the Header files TString.h
 *
 * Write the TString class definition in the TString.h file, write your
 * implementation code in TString.cpp, compile, and test with the main() in
 * XString.cpp.
 *
 */

#include "TString.h"

#include <fstream>
#include <iostream>
#include <iomanip>
using std::ostream;
using std::ofstream;
using std::cin;
using std::cout;
using std::dec;
using std::endl;
using std::flush;
using std::hex;
using std::ios;
using namespace std;

// Note - If you are not using Microsoft Visual Studio, you may need to uncomment the following
// code for this test program to compile. strcpy_s is Microsoft's secure replacement for strcpy
// and may not exist in other development environments. 

#include <cstring>
#define strcpy_s(a, b, c) strncpy(a, c, b)

const char *pOutfileName = "XStringOut.txt";

const char *pHello = "Hello";
const char *pHelloWorld = "Hello world from C++";
const char *pHelloLower = "hello world from c++";
const char *pHiMom = "Hi Mom!";
const char *pHi = "Hi ";
const char *pHo = "Ho ";
const char *pMom = "Mom!";
const char *pWelcome = "Welcome!";
const char *emptyString = "";


const int tempBufLen = 200;
char tempBuf[tempBufLen];

const char* copyToTemp(const char* pText)
{
    strcpy_s(tempBuf, tempBufLen, pText);
    return tempBuf;
}

void clearTemp()
{
    strcpy_s(tempBuf, tempBufLen, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
}

// note - you may need to change the definition of the main function to
// be consistent with what your C++ compiler expects.
int main(void)
{
    ofstream outfile (pOutfileName, ios::out);
    if( !outfile.is_open() )
    {
        cout << "Error - unable to open output file: " << pOutfileName << endl;
        return 1;
    }

    //cout << "Writing output to " << pOutfileName << "... please wait" << endl;
    //ostream& outstream = outfile;  // uncomment to write to file
    ostream& outstream = cout;  // uncomment to write directly to cout

    const char *mp = 0;
    int step = 0;
    outstream << "----- simple String class test ----- (09/16/2010)" << endl << endl;

    // const checks  (compile tests)
	// If there are compile errors in this section, then there are probably const specifiers missing from your
	// class definition, e.g.  the length() member function should be defined as a const member function so
	// it can be invoked on a const TString object, as should all other member functions that don't change the
	// state of 'this'.
    {
        if (0 != 0)  // only a compilation check for these methods at this point (for const). Tested further below.
        {
            const TString s0(pHello); // create a const TString object
            int n = s0.length();
            bool f = s0.equalsIgnoreCase(pHello);
            f = s0.equals(pHello);
            const char *p = s0.asChar();
            n = s0.indexOf('h');
            const TString s1(s0);  // const String object parameter

            TString s2;
            s2.assign(s0);  // const String object parameter
            s2.append(s0);  // const String object parameter
        }
    }

    // Default ctor
    outstream << "\n----- Step " << ++step << " - default ctor -----" << endl;
    {
        TString s0;  // default arg value
        outstream << "s0 using default ctor with default arg = \"" << s0.asChar() << "\" (length = " << s0.length() << ")" << endl;
        mp = (0 == s0.length()) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s0.length() << endl;
        mp = (0 != s0.asChar()) ? "OK: " : "ERROR: ";
        outstream << mp << "asChar() return value " << hex << "0x" << reinterpret_cast<const int *>(s0.asChar()) << dec << endl;
        mp = ('\0' == *(s0.asChar())) ? "OK: null byte " : "ERROR: null byte not ";
        outstream << mp << "at position 0" << endl;
    }
    {
        TString s0(copyToTemp(pHello));  // char * parameter
        clearTemp();
        outstream << endl << "s0 using default ctor with char* parameter = \"" << s0.asChar() << "\" (length = " << s0.length() << ")" << endl;
        mp = (s0.length() == strlen(pHello)) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s0.length() << endl;
        mp = (0 == strcmp(s0.asChar(), pHello)) ? "OK: " : "ERROR: ";
        outstream << mp << "value is \"" << s0.asChar() << "\"" << endl;
        mp = (s0.asChar() != pHello) ? "OK: different " : "ERROR: same ";
        outstream << mp << "pointer value returned from asChar()" << endl;
        mp = (s0.asChar() == s0.asChar()) ? "OK: same " : "ERROR: different ";
        outstream << mp << "pointer value returned for successive calls of asChar()" << endl;
    }


    // Copy ctor
    outstream << "\n----- Step " << ++step << " - copy ctor -----" << endl;
    {
        TString s0(copyToTemp(pHiMom));
        clearTemp();
        TString s1(s0);  // copy ctor
        outstream << "s1 using copy ctor = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.length() == s0.length() && s1.length() == strlen(pHiMom)) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s1.length() << endl;
        mp = (s1.asChar() != s0.asChar()) ? "OK: different " : "ERROR: same ";
        outstream << mp << "pointer value returned from asChar()" << endl;
        mp = (0 == strcmp(s1.asChar(), pHiMom)) ? "OK: " : "ERROR: ";
        outstream << mp << "value is \"" << s1.asChar() << "\"" << endl;
    }
    {
        // Check copy of empty string
        TString s0;
        TString s1(s0);
        outstream << "s1 using copy ctor = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (0 == s1.length()) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s1.length() << endl;
        mp = (0 != s1.asChar()) ? "OK: " : "ERROR: ";
        outstream << mp << "asChar() return value " << hex << "0x" << reinterpret_cast<const int *>(s1.asChar()) << dec << endl;
        mp = (s1.asChar() != s0.asChar()) ? "OK: different " : "ERROR: same ";
        outstream << mp << "pointer value returned from asChar()" << endl;
        mp = ('\0' == *(s0.asChar())) ? "OK: null byte " : "ERROR: null byte not ";
        outstream << mp << "at position 0" << endl;
    }


    // append
    outstream << "\n----- Step " << ++step << " - append -----" << endl;
    {
        TString s1(copyToTemp("Hello "));
        clearTemp();
        const char *p1 = s1.asChar();
        s1.append(copyToTemp("world "));
        clearTemp();
        mp = (s1.asChar() != p1) ? "OK: different " : "ERROR: same ";
        outstream << mp << "asChar() return value after append" << endl;
        s1.append(copyToTemp("from "));
        clearTemp();
        s1.append(copyToTemp("C++"));
        clearTemp();
        outstream << "s1 = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.equals(pHelloWorld)) ? "OK: matches " :  "ERROR: doesn't match ";
        outstream << mp << "\"" << pHelloWorld << "\"" << endl;
        mp = (s1.equalsIgnoreCase(pHelloLower)) ? "OK: matches ignore case " :  "ERROR: doesn't match ignore case ";
        outstream << mp << "\"" << pHelloLower << "\"" << endl;
        mp = (!s1.equals(pHiMom)) ? "OK: doesn't match " :  "ERROR: matches ";
        outstream << mp << "\"" << pHiMom << "\"" << endl;
    }
    {
        TString s1(copyToTemp(pHello));
        clearTemp();
        s1.append(s1);  // append to self
        s1.append(s1.asChar());  // append to self
        TString s2(copyToTemp(pHello));
        clearTemp();
        s2.append(copyToTemp(pHello));
        clearTemp();
        s2.append(copyToTemp(pHello));
        clearTemp();
        s2.append(copyToTemp(pHello));
        clearTemp();
        outstream << endl << "s1 appended to self = \"" << s1.asChar() << "\"" << endl;
        mp = (0 == strcmp(s1.asChar(), s2.asChar())) ? "OK: matches " : "ERROR: doesn't match ";
        outstream << mp << s2.asChar() << endl;
    }


    // assign
    outstream << "\n----- Step " << ++step << " - assign -----" << endl;
    {
        TString s0;
        s0.assign(copyToTemp(pHello));  // assign with char* parameter
        clearTemp();
        outstream << "s0 using assign with char* parameter = \"" << s0.asChar() << "\" (length = " << s0.length() << ")" << endl;
        mp = (s0.length() == strlen(pHello)) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s0.length() << endl;
        mp = (0 == strcmp(s0.asChar(), pHello)) ? "OK: " : "ERROR: ";
        outstream << mp << "value is \"" << s0.asChar() << "\"" << endl;
        mp = (s0.asChar() != pHello) ? "OK: different " : "ERROR: same ";
        outstream << mp << "pointer value returned from asChar()" << endl;
    }
    {
        TString s0(copyToTemp(pHiMom));
        clearTemp();
        TString s1;
        s1.assign(s0);  // assign with String parameter
        outstream << endl << "s1 using assign with String parameter = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.length() == s0.length() && s1.length() == strlen(pHiMom)) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s1.length() << endl;
        mp = (0 == strcmp(s1.asChar(), pHiMom)) ? "OK: " : "ERROR: ";
        outstream << mp << "value is \"" << s1.asChar() << "\"" << endl;
        mp = (s1.asChar() != s0.asChar()) ? "OK: different " : "ERROR: same ";
        outstream << mp << "pointer value returned from asChar()" << endl;
    }
    {
        TString s0(copyToTemp(pHelloWorld));
        clearTemp();
        TString s1(copyToTemp(pHi));
        clearTemp();
        s1.assign(s0);  // assign with String parameter
        outstream << endl << "s1 using assign with String parameter = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.length() == s0.length() && s1.length() == strlen(pHelloWorld)) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s1.length() << endl;
        mp = (0 == strcmp(s1.asChar(), pHelloWorld)) ? "OK: " : "ERROR: ";
        outstream << mp << "value is \"" << s1.asChar() << "\"" << endl;
        mp = (s1.asChar() != s0.asChar()) ? "OK: different " : "ERROR: same ";
        outstream << mp << "pointer value returned from asChar()" << endl;
    }
    {
        TString s1(copyToTemp(pHello));
        clearTemp();
        outstream << endl << "s1 assign to self" << endl;
        const char* p1 = s1.asChar();
        s1.assign(s1);  // assign object to self
        mp = (s1.asChar() == p1) ? "OK: same " : "ERROR: different ";
        outstream << mp << " asChar() return value after String assign to self" << endl;
        p1 = s1.asChar();
        s1.assign(s1.asChar()); // assign char* array to self
        mp = (s1.asChar() == p1) ? "OK: same " : "ERROR: different ";
        outstream << mp << " asChar() return value after asChar() assign to self" << endl;
    }
    {
        TString s1(copyToTemp(pHello));
        clearTemp();
        outstream << endl << "s1 assign with char* parameter" << endl;
        s1.assign(copyToTemp(pHi));
        clearTemp();
        s1.append(copyToTemp(pMom));
        clearTemp();
        outstream << "s1 = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.equals(pHiMom)) ? "OK: matches " :  "ERROR: doesn't match ";
        outstream << mp << "\"" << pHiMom << "\"" << endl;
        mp = (!s1.equals(emptyString)) ? "OK: doesn't match " :  "ERROR: matches ";
        outstream << mp << "\"" << emptyString << "\"" << endl;
    }

    // Test null pointer and null string args
    outstream << "\n----- Step " << ++step << " - Null ptr and empty string -----" << endl;
    {
        TString s1;
        outstream << "Appending \"" << pHelloWorld << "\", empty string, and null pointer to s1 = \"" << s1.asChar() << "\"" << endl;
        s1.append(copyToTemp(pHelloWorld));
        clearTemp();
        s1.append(copyToTemp(""));
        clearTemp();
        s1.append(0);
        outstream << "s1 = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.equals(pHelloWorld)) ? "OK: matches " :  "ERROR: doesn't match ";
        outstream << mp << "\"" << pHelloWorld << "\"" << endl;
    }
    {
        TString s1(copyToTemp("not empty"));
        clearTemp();
        outstream << endl << "Assigning empty string to s1 = \"" << s1.asChar() << "\"" << endl;
        s1.assign(emptyString);
        outstream << "s1 = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.equals("")) ? "OK: matches " : "ERROR: doesn't match ";
        outstream << mp << "\"" << emptyString << "\"" << endl;
        mp = (0 == s1.length()) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s1.length() << endl;
        mp = (0 != s1.asChar()) ? "OK: " : "ERROR: ";
        outstream << mp << "asChar() return value " << hex << "0x" << reinterpret_cast<const int *>(s1.asChar()) << dec << endl;
    }
    {
        TString s1(copyToTemp("still not empty"));
        clearTemp();
        outstream << endl << "Assigning null pointer to s1 = \"" << s1.asChar() << "\"" << endl;
        s1.assign(static_cast<const char *>(0));
        outstream << "s1 = \"" << s1.asChar() << "\" (length = " << s1.length() << ")" << endl;
        mp = (s1.equals("")) ? "OK: matches " : "ERROR: doesn't match ";
        outstream << mp << "\"" << emptyString << "\"" << endl;
        mp = (0 == s1.length()) ? "OK: " : "ERROR: ";
        outstream << mp << "length = " << s1.length() << endl;
        mp = (0 != s1.asChar()) ? "OK: " : "ERROR: ";
        outstream << mp << "asChar() return value " << hex << "0x" << reinterpret_cast<const int *>(s1.asChar()) << dec << endl;
    }

    // indexOf
    outstream << "\n----- Step " << ++step << " - indexOf -----" << endl;
    {
        TString s0(copyToTemp("Hi and hello"));
        clearTemp();
        int pos = s0.indexOf('H');
        mp = (0 == pos) ? "OK: 'H' found " : "ERROR: 'H' not found ";
        outstream << mp << " - indexOf = " << pos << endl;
        pos = s0.indexOf('h');
        mp = (7 == pos) ? "OK: 'h' found " : "ERROR: 'h' not found ";
        outstream << mp << " - indexOf = " << pos << endl;
        pos = s0.indexOf('o');
        mp = (11 == pos) ? "OK: 'o' found " : "ERROR: 'o' not found ";
        outstream << mp << " - indexOf = " << pos << endl;
        pos = s0.indexOf('z');
        mp = (-1 == pos) ? "OK: 'z' not found " : "ERROR: 'z' should return -1 ";
        outstream << mp << " - indexOf = " << pos << endl;
    }

    // Test many dynamic operations (this may take some time).
    // If the program aborts in this section, look at the code in the String ctors,
    // dtor, copy ctor, and assignment method to verify that dynamic memory
    // is managed correctly.
    outstream << "\n----- Step " << ++step << " - Heap memory use -----" << endl;
    outstream << "Heap use test (this could take a minute or two): " << endl;
    {
        TString s2;
        TString t1;
        for (int iter = 0; iter < 50000; ++iter)
        {
            s2.assign(emptyString);
            TString t1(s2);
            for (int nc = 0; nc < 200; ++nc)
            {
                s2.append("x");
                s2.append(emptyString);
                s2.asChar();
                t1.append("yz");
                t1.append(static_cast<const char *>(0));
                t1.asChar();
            }
            TString t2;
            t2.assign(s2);
            t2.assign("vwq");
            t2.assign(t1);
            t2.assign(t2);
            t2.assign(static_cast<const char *>(0));
            t2.asChar();
            if (iter%100 == 0)
            {
                outstream << "." << flush;
            }
        }
        outstream << "completed" << endl;
    }

    // Testing dynamically allocated String objects. Uses the -> member selection operator for a
    // pointer to an object.
    outstream << "\n----- Step " << ++step << " - Heap Strings -----" << endl;
    {
        TString *sp = new TString;  // Create a heap based String object (sp points to it)
        sp->assign(copyToTemp(pHi));
        clearTemp();
        sp->append(copyToTemp(pMom));
        clearTemp();
        outstream << "sp = \"" << sp->asChar() << "\" (length = " << sp->length() << ")" << endl;
        mp = (sp->equals(pHiMom)) ? "OK: matches " :  "ERROR: doesn't match ";
        outstream << mp << "\"" << pHiMom << "\"" << endl;
        mp = (!sp->equals(emptyString)) ? "OK: doesn't match " :  "ERROR: matches ";
        outstream << mp << "\"" << emptyString << "\"" << endl;
        outstream << sp->asChar() << endl;

        const char* cp = sp->asChar();  // ptr to char array
        int cpLen = sp->length();
        delete sp;  // Free the heap based String object.
    }

    outstream << endl << "\nTest of simple String class completed" << endl << endl;

    outfile.close();
    return 0;
}
