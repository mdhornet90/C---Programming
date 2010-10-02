// -- TString.h header file --
#ifndef _TSTRING_H    // only include once in a compilation unit 
#define _TSTRING_H

class TString 
{ // Prefix with 'T' for uniqueness
    public:
        TString();
        TString(const char *pText); // default ctor
        TString(const TString& str);
        ~TString();
        int length() const;
        char* asChar() const;
        void assign(const TString& str);
        void assign(char *str);
        void append(const TString& str);
        bool equals(const TString& compare) const;
        bool equalsIgnoreCase(const TString& compare) const;
        int indexOf(char first) const;
            
    private:
        int mLength; // length of char data (not including null byte)
        char *mpText; // pointer to dynamic char data in heap
};

#endif   // _TSTRING_H
