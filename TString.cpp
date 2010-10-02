// -- TString.cpp source file --
#include "TString.h"
#include <string> //Only used for the approved functions, I SWEAR

TString::TString(char **pText) 
{
    if (0 == *pText) 
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
        mLength = strlen(mpText);
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
        mLength = strlen(mpText);
    }
}

void TString::append(const TString& str)
{
    int i = strlen(mpText) + 1, j;
    if (*mpText == *str.mpText)
        return;
    else if ( str.mpText == "" )
        return;
    else
    {
        mpText[i] = ' ';
        mpText = new char[strlen(str.mpText) + 1];   
        for ( i = strlen(mpText), j = 0; str.mpText[j] != '\0'; i++, j++ )
            mpText[i] = str.mpText[j];
    }    
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
