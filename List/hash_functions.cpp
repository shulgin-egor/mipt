#include <assert.h>
#include <string.h>
#include <stdio.h>

/***************************************************************************************************/

#define __FUNC__ __func__

/***************************************************************************************************/

unsigned long long Hash_Equal (const char* str);
//=====================================================================================================================
unsigned long long Hash_FirstLetter (const char* str);
//=====================================================================================================================
unsigned long long Hash_WordLen (const char* str);
//=====================================================================================================================
unsigned long long Hash_SumofLetters (const char* str);
//=====================================================================================================================
unsigned long long Hash_AverageLetter (const char* str);
//=====================================================================================================================
unsigned long long Hash_CircularShift (const char* str);

/***************************************************************************************************/

unsigned long long Hash_Equal (const char* str)
{
    assert (str);

    return 0 ;
}

//=====================================================================================================================

unsigned long long Hash_FirstLetter (const char* str)
{
    assert (str);

    return (int)str[0];
}

//=====================================================================================================================

unsigned long long Hash_WordLen (const char* str)
{
    assert (str);

    return strlen (str) ;
}

//=====================================================================================================================

unsigned long long Hash_SumofLetters (const char* str)
{
    assert (str);

    long long sum = 0, len = strlen (str);

    for (int i = 0; i < len; i++)
        sum += str[i];

    return sum;
}

//=====================================================================================================================

unsigned long long Hash_AverageLetter (const char* str)
{
    assert (str);

    long long sum = 0, len = strlen (str);

    for (int i = 0; i < len; i++)
        sum += str[i];

    return (sum / strlen (str));
}

//=====================================================================================================================

unsigned long long Hash_CircularShift (const char* str)
{
    assert (str);

    unsigned int len = strlen(str), hash = 0;

    for (unsigned int i = 0; i < len; i++)
    {
        hash ^= str[i];
        hash = (hash >> 2) | (hash << 30);
    }

    return hash;
}
