// -- TString.cpp source file --
#include "TString.h"
#include <string.h> //Only used for the approved functions, I SWEAR


TString::TString() 
{
    mpText = new char[0];
    mpText = "";
    mLength = 0;
}

TString::TString(const char *pText = NULL)
{
    if (0 == pText){
        mpText = new char[0];
        mpText = "";
    }
    mLength = strlen(pText);
    //mpText = ...
}

TString::TString(const TString& str)
{   
    if ( 0 == str.mpText )
        mpText = '\0';
        
    mpText = new char[strlen(str.mpText) + 1]; 
    strcpy(mpText, str.mpText);
    mLength = strlen(mpText);
}

TString::~TString()
{
    delete mpText;
    mpText = 0;
    
    mLength = 0;
}

int TString::length() const
{   
    //mLength = strlen(mpText);
    return mLength;
}

char* TString::asChar() const
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
    else if ( !strcmp(str.mpText, "") )
        return;
    else
    {
        mpText[i] = ' ';
        i++;
        mpText = new char[strlen(str.mpText) + 1];   
        for ( j = 0; str.mpText[j] != '\0'; i++, j++ )
            mpText[i] = str.mpText[j];
        
    }    
}

bool TString::equals(const TString& compare) const
{
    if (!strcmp(this->mpText, compare.mpText))
        return true;
    else
        return false;
}

bool TString::equalsIgnoreCase(const TString& compare) const
{
    if (!strcasecmp(this->mpText, compare.mpText))
        return true;
    else
        return false;
}
int TString::indexOf(char first) const
{
    int i = 0;
    
    while ( *mpText != first )
    {
        mpText[i]++;
        i++;
    }
    
    return i;
}
