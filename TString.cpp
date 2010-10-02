// -- TString.cpp source file --
#include "TString.h"
#include <string> //Only used for the approved functions, I SWEAR

TString::TString(char **pText) 
{
    if (0 == *pText) 
        mpText = '\0';
}

TString::TString(const TString& str)
{   
    mpText = new char[strlen(str.mpText) + 1]; 
    strcpy(mpText, str.mpText); 
}

TString::~TString()
{
    delete mpText;
    mpText = '\0';
}

int TString::length()
{   
    return mLength;
}

const char* TString::asChar()
{
    return mpText;
}

void TString::assign(TString& str)
{
    if (*mpText == *str.mpText)
        return;
    else
    {
        char *tmp
        mpText = new char[strlen(str.mpText) + 1]; 
        strcpy(mpText, str.mpText);
        delete tmp;
    }
}

void TString::assign(char *str)
{
    if (*mpText == *str)
        return;
    else
    {   
        mpText = new char[strlen(str) + 1]; 
        mpText = str;
    }
    delete mpText;
}

void TString::append(const TString& str)
{
    mpText = new char[strlen(str.mpText) + 1];   
}
