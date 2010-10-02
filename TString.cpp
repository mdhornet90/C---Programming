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
        delete mpText;
        mpText = new char[strlen(str.mpText) + 1]; 
        strcpy(mpText, str.mpText);
    }
}

void TString::assign(char *str)
{
    if (*mpText == *str)
        return;
    else
    {   
        delete mpText;
        mpText = new char[strlen(str) + 1]; 
        mpText = str;
        mpText[strlen(str)] = '\0';
    }
}

void TString::append(const TString& str)
{
    int i;
    i = indexOf('\0');
    mpText[i] = ' ';
    
    mpText = new char[strlen(str.mpText) + 1];   
    
    for ( i 
}

int TString::indexOf(char first)
{
    int i = 0;
    
    while ( *mpText != first )
    {
        mpText++;
        i++;
    }
    
    return i;
}
