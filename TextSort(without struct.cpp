//{=================================================================================
//! @file    TextSort.cpp
//! @author  Egor Shulgin <dwarfegpr@yandex.ru>, 571 group
//!
//! Sorting lines of Byron
//!
//!
//}=================================================================================
//--------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale>

#define FOPEN_ERROR NULL
#define ERROR -1

/*struct my_string
    {
        char *str;
        int len;
    };*/

FILE *FileOpen (char* FilePath, char* FOpenMode);
long long FileLength (FILE* InputFile);
char* FileBuffer (FILE* InputFile, const long long FileLength);
int FreeBuffer (char buffer[]);
int CountNumberOfLines (const char buffer[], const long long FileLength);
int SplitBuffer (char* text[], char buffer[], const long long FileLength, int NumberOfLines);
int FreeText (char* text[], const int NumberOfLines);

int RevStrCmp (const char* str1, const char* str2);
int my_StrCmp (const char* str1, const char* str2);
bool my_isalpha (const char symb);
void my_swap (char** str1, char** str2);
int str_eq (char* str1, char* str2);
int CompSortFromBegin(const void* a, const void* b);
int CompSortFromEnd(const void* a, const void* b);
int TextSort (int SortType, char* text[], int NumberOfLines);
void TextOut (char* text[], int NumberOfLines);


int main()
{
    printf ("# Program by Shulgin E. \n");
    //setlocale (LC_ALL, "Russian");

    char FilePath[260] = "***";
    char ReadMode[2] = "*";

    FILE *InputFile;
    InputFile = FileOpen (FilePath, ReadMode);
    if (InputFile == FOPEN_ERROR) return 0;

    long long file_len = 0;
    file_len = FileLength (InputFile);
    char* buffer = FileBuffer (InputFile, file_len);

    /*const char* bufCopy = (char*) calloc (file_len, sizeof(*buffer));
    memcpy(buffer, bufCopy, sizeof(buffer));
    printf("\n<%s>\n", bufCopy); */

    printf ("\n--------------\n" "<%s>" "\n--------------\n", buffer);
    int nLines = 0;
    nLines = CountNumberOfLines (buffer, file_len);
    //printf ("nLines = %d" "\n", nLines);

    char** text = (char**) calloc (nLines, sizeof(**text));
    SplitBuffer (text, buffer, file_len, nLines);

    int SortType = 1;
    int sort_check = 1;
    sort_check = TextSort (SortType, text, nLines);
    if (sort_check == ERROR) return 0;

    TextOut (text, nLines);

    fclose (InputFile);
    int Text_check = 1;
    Text_check = FreeText (text, nLines);
    if (Text_check == ERROR) return 0;

    int Buf_check = 1;
    Buf_check = FreeBuffer (buffer);
    if (Buf_check == ERROR) return 0;

    return 1;
}


FILE* FileOpen (char* FilePath, char* FOpenMode)
{
    /*printf ("Input file path: ");
    scanf ("%s", FilePath);
    printf ("Input file open mode: ");
    scanf ("%s", FOpenMode);
    */
    FilePath = "input.txt";
    FOpenMode= "rb";
    FILE *InputFile;
    InputFile = fopen (FilePath, FOpenMode);
    if (InputFile == NULL)
    {
        printf ("\n" "ERROR: Could not find such file, "
                     "please restart the program" "\n");
        return FOPEN_ERROR;
    }
    else return InputFile;
}

long long FileLength (FILE *InputFile)
{
    fseek (InputFile, 0, SEEK_END);
    long long len = 0;
    len = ftell(InputFile);
    rewind (InputFile);

    return len;
}

char* FileBuffer (FILE *InputFile, const long long FileLength)
{
    char *buffer = (char*) calloc (FileLength, sizeof(*buffer));
    fread (buffer, FileLength, sizeof(*buffer), InputFile);
    rewind (InputFile);

    return buffer;
}

int FreeBuffer (char buffer[])
{
    free (buffer);
    if (buffer == NULL)
    {
        printf ("\n" "ERROR: Buffer is already NULL" "\n");
        return ERROR;
    }
    else
    {
        buffer = NULL;
        return 1;
    }
}

int CountNumberOfLines (const char buffer[], const long long FileLength)
{
    int count = 0;
    for (int i = 0; i < FileLength; i++)
        if (buffer[i] == '\n')
            count++;
    return count;
}

int SplitBuffer (char* text[], char buffer[], const long long FileLength, int NumberOfLines)
{
    //char** text = (char**) calloc (NumberOfLines, sizeof(**text));
    int j = 0, curlen = 0, begstr = 0;

    for (int n = 0; n < NumberOfLines; n++)
    {
        begstr = j;
        while (j < FileLength && buffer[j] != '\r') j++;
        buffer[j] = '\0';
        j += 2;
        text[n] = &buffer[begstr];
        //curlen = j - begstr - 3;
        //char *bufstr = (char*) calloc (strlen, sizeof(char*));
        //my_string bufstr = {&buffer[j], curlen};
        //my_string bufstr = {NULL, -1};

    }
}

int FreeText (char* text[], const int NumberOfLines)
{
    for (int i = NumberOfLines; i >=0 ; i--)
    {
        free(text[i]);
        if (text[i] == NULL)
        {
            printf ("\n" "ERROR: text[%d] is already NULL" "\n", i);
            return ERROR;
        }
        else
        {
            text[i] = NULL;
            return 1;
        }
    }
}

bool my_isalpha (const char symb)
{
    if (symb >= 'a' && symb <= 'z' || symb >= 'A' && symb <= 'Z') return true;
    else return false;
}

char ToCapitalLetter (const char letter)
{
    if (letter >= 'a' && letter <= 'z') return (char)(int(letter) - ('a' - 'A'));
    else return letter;
}

int RevStrCmp (const char* str1, const char* str2)
{
    int len1 = strlen (str1) - 1;
    int len2 = strlen (str2) - 1;
    char letter1 = (char)(0), letter2 = (char)(0);

    while (len1 >= 0 && len2 >= 0)
    {
        if (my_isalpha (str1[len1]) && my_isalpha (str2[len2]))
        {
            letter1 = ToCapitalLetter (str1[len1]);
            letter2 = ToCapitalLetter (str2[len2]);
            if (letter1 > letter2) return 1;
            else if (letter1 < letter2) return -1;
                 else len1--, len2--;
        }
        else
        {
            if (!my_isalpha (str1[len1])) len1--;
            else if (!my_isalpha (str2[len2])) len2--;
                 else len1--, len2--;
        }

    }
    return 0;
}

int my_StrCmp (const char* str1, const char* str2)
{
    int len1 = strlen (str1);
    int len2 = strlen (str2);
    int index1 = 0, index2 = 0;
    char letter1 = (char)(0), letter2 = (char)(0);

    while (index1 < len1 && index2 < len2 )
    {
        if (my_isalpha (str1[index1]) && my_isalpha (str2[index2]))
        {
            letter1 = ToCapitalLetter (str1[index1]);
            letter2 = ToCapitalLetter (str2[index2]);
            if (letter1 > letter2) return 1;
            else if (letter1 < letter2) return -1;
                 else index1++, index2--;
        }
        else
        {
            if (!my_isalpha (str1[index1])) index1++;
            else if (!my_isalpha (str2[index2])) index2++;
                 else index1++, index2++;
        }

    }
    return 0;
}

void my_swap (char** str1, char** str2)
{
    char *temp = *str1;;
    *str1 = *str2;
    *str2 = temp;
}

int str_eq (char* str1, char* str2)
{
    int len1 = strlen (str1);
    int len2 = strlen (str2);

    while (len1 >= 0 && len2 >= 0)
    {
        if (str1[len1] != str2[len2]) return 0;
        len1--;
        len2--;
    }
    return 1;
}

int CompSortFromBegin(const void* str1, const void* str2)
{
    return my_StrCmp(*(const char**) str1, *(const char**) str2);
}

int CompSortFromEnd(const void* str1, const void* str2)
{
    return RevStrCmp(*(const char**) str1, *(const char**) str2);
}

int TextSort (int SortType, char* text[], int NumberOfLines)
{
    /*for (int i = 0; i < NumberOfLines - 1; i++)
        for (int j = i + 1; j < NumberOfLines; j++)
            if ((*compare)(text[i], text[j]) == 0)
                my_swap (&text[i], &text[j]); */

    printf ("Available types of sort:" "\n"
            " 1) SortFromBeg" "\n"
            " 2) SortFromEnd" "\n");
    printf ("Input number of preferred sorting: ");
    scanf ("%d", &SortType);
    switch (SortType)
    {
        case (1):
            qsort(text, NumberOfLines, sizeof(text[0]), CompSortFromBegin);
            break;
        case (2):
            qsort(text, NumberOfLines, sizeof(text[0]), CompSortFromEnd);
            break;
        default:
            printf ("ERROR: There is no such type of sort");
            return ERROR;
    }
    /*if (str_eq(SortType, "SortFromBeg"))
        qsort(text, NumberOfLines, sizeof(text[0]), CompSortFromBegin);
    else if (str_eq(SortType, "SortFromEnd"))
             qsort(text, NumberOfLines, sizeof(text[0]), CompSortFromEnd);
         else
         {
            printf ("ERROR: There is no such type of sort");
            return ERROR;
         }*/
    return 1;
}

void TextOut (char* text[], int NumberOfLines)
{
    printf ("\n" "Sorted text:" "\n");
    for (int i = 0; i < NumberOfLines; i++)
        printf("%s\n", text[i]);

    /*switch (SortType)
    {
        case "CmpFromBeg":
            TextSort (&stricmp, text, NumberOfLines);
            break;
        case "CmpFromEnd":
            TextSort (&RevStrCmp, text, NumberOfLines);
            break;
        default:
            printf ("ERROR: There is no such type of sort");
            return OUTERROR
            break
    }*/
}
