// -- TString.cpp source file --
#include "TString.h"
#include <string> //Only used for the approved functions, I SWEAR

TString::TString(const char *pText) 
{
    if (0 == pText) 
        mpText = '\0';
        
    mLength = strlen(mpText);
}

TString::TString(TString& str)
{   
    if ( str.mpText == 0 )
        str.mpText = "";
        
    mpText = new char[strlen(str.mpText) + 1]; 
    strcpy(mpText, str.mpText);
    mLength = strlen(mpText);
}

TString::~TString()
{
    delete mpText;
    mpText = 0;
    
    mLength = strlen(mpText);
}

const int TString::length()
{   
    mLength = strlen(mpText);
    return mLength;
}

const char* TString::asChar()
{
    return mpText;
}

void TString::assign(const TString& str)
{
    if (*mpText == *str.mpText)
        return;
    else
    {
        delete mpText;
        mpText = new char[strlen(str.mpText) + 1]; 
        strcpy(mpText, str.mpText);
        mLength = strlen(mpText);
    }
}

void TString::assign(char *str)
{
    if (*mpText == *str || *str == '\0')
        return;
    else
    {   
        delete mpText;
        mpText = new char[strlen(str) + 1]; 
        mpText = str;
        mpText[strlen(str)] = '\0';
        mLength = strlen(mpText);
    }
}

void TString::append(const TString& str)
{
    int i = strlen(mpText), j;
    if (*mpText == *str.mpText)
        return;
    else if ( str.mpText == "" )
        return;
    else
    {
        mpText[i] = ' ';
        i++;
        mpText = new char[strlen(str.mpText) + 1];   
        for ( i, j = 0; str.mpText[j] != '\0'; i++, j++ )
            mpText[i] = str.mpText[j];
        
    }    
}

bool TString::equals(const TString& compare)
{
    if (!strcmp(this->mpText, compare.mpText))
        return true;
    else
        return false;
}

bool TString::equalsIgnoreCase(const TString& compare)
{
    if (!stricmp(this->mpText, compare.mpText))
        return true;
    else
        return false;
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
