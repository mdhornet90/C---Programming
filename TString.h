// -- TString.h header file --
#ifndef _TSTRING_H    // only include once in a compilation unit 
#define _TSTRING_H

class TString 
{ // Prefix with 'T' for uniqueness
    public:
        TString(char **pText = 0); // default ctor
        TString(const TString& str);
        ~TString();
        int length();
        const char* asChar();
        void assign(TString& str);
        void assign(char *str);
        void append(const TString& str);
        bool equals(char *compare);
        bool equalsIgnoreCase(char *compare);
        int indexOf(char first);
            
    private:
        int mLength; // length of char data (not including null byte)
        char *mpText; // pointer to dynamic char data in heap
};

#endif   // _TSTRING_H
