//{=================================================================================
//! @file    TextSort.cpp
//! @author  Egor Shulgin <dwarfegor@yandex.ru>, 571 group
//!
//! Sorting lines of Byron
//!
//}=================================================================================
//--------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale>

#define PTR_ERROR NULL
#define INT_ERROR -1
#define OK 1

#define MAXFILEPATH 260
#define MAXREADMODE 3

struct my_string
    {
        char *str;
        int len;
    };

/** ********************************************
 FileOpen - opens file.

 @return   *FILE_InputFile or FOPEN_ERROR

************************************************/
FILE* FileOpen (const char* FilePath, const char* FOpenMode);

/** ********************************************
 FileLength - calculates number of symbols in file.

 @return   Length of File

************************************************/
long long FileLength (FILE* InputFile);

/** ********************************************
 FileBuffer - reads all file into array of chars.

 @return   char* Buffer

***********************************************/
char* FileBuffer (FILE* InputFile, const long long FileLength);

int FreeBuffer (char buffer[]);
void Buffer_Dump (const char buffer[]);

/** *******************************************
 CountLines - counts number of lines in buffer.

 @return   number of lines

***********************************************/
int CountLines (const char buffer[], const long long FileLength);

int Text_Construct (my_string* text, char buffer[], const long long FileLength, const int NumberOfLines);
int Text_Destruct (my_string* text, const int NumberOfLines);

bool my_isalpha (const char symb);
void my_swap (char** str1, char** str2);
int str_eq (char* str1, char* str2);

int RevStrCmp (const my_string* str1, const my_string* str2);
int my_StrCmp (const my_string* str1, const my_string* str2);
int CompSortFromBegin(const void* a, const void* b);
int CompSortFromEnd(const void* a, const void* b);
int TextSort (int SortType, my_string* text, const int NumberOfLines);
void TextOut (const my_string* text, const int NumberOfLines);


int main()
{
    printf ("# Program by Shulgin E." "\n\n");
    //setlocale (LC_ALL, "Russian");      // If u want to sort a russian poem

    char FilePath[MAXFILEPATH] = "Bayrone.txt";
    char ReadMode[MAXREADMODE] = "rb";

    FILE* InputFile = FileOpen (FilePath, ReadMode);
    if (InputFile == PTR_ERROR) return -1;

    long long file_len = FileLength (InputFile);
    if (file_len == INT_ERROR) return -1;

    char* buffer = FileBuffer (InputFile, file_len);
    fclose (InputFile);
    if (buffer == PTR_ERROR) return -1;
    //printf ("\n--------------\n" "<%s>" "\n--------------\n", buffer);
    /*const char* bufCopy = (char*) calloc (file_len, sizeof(*buffer));
    memcpy(buffer, bufCopy, sizeof(buffer));
    printf("\n<%s>\n", bufCopy); */

    int nLines = 0;
    nLines = CountLines (buffer, file_len);
    if (nLines == INT_ERROR) return -1;
    //printf ("nLines = %d" "\n", nLines);

    my_string* text = (my_string*) calloc (nLines, sizeof(my_string*));
    Text_Construct (text, buffer, file_len, nLines);
    TextOut (text, nLines);

    int SortType = 1;
    printf ("Available types of sort:" "\n"
            " 1) SortFromBeg" "\n"
            " 2) SortFromEnd" "\n");
    printf ("Input number of preferred sorting: ");
    scanf ("%d", &SortType);
    int sort_check = TextSort (SortType, text, nLines);
    if (sort_check == INT_ERROR) return -1;

    printf ("\n" "Sorted text:" "\n");
    TextOut (text, nLines);

    int Text_check = Text_Destruct (text, nLines);
    if (Text_check == INT_ERROR) return -1;

    int Buf_check = FreeBuffer (buffer);
    if (Buf_check == INT_ERROR) return -1;

    return 1;
}


FILE* FileOpen (const char* FilePath, const char* FOpenMode)
{
    /*printf ("Input file path: ");
    scanf ("%s", FilePath);
    printf ("Input file open mode: ");
    scanf ("%s", FOpenMode);

    FilePath = "Bayrone.txt";
    FOpenMode= "rb";*/

    FILE *InputFile = fopen (FilePath, FOpenMode);
    if (InputFile == NULL)
    {
        printf ("\n" "ERROR: Could not find file '%s', "
                     "please restart the program" "\n", FilePath);
        return PTR_ERROR;
    }
    else return InputFile;
}

long long FileLength (FILE *InputFile)
{
    int check = fseek (InputFile, 0, SEEK_END);
    if (check != 0)
    {
        printf ("\n" "ERROR: Probably file is not opened" "\n");
        return INT_ERROR;
    }
    long long len = 0;
    len = ftell(InputFile);
    rewind (InputFile);

    return len;
}

char* FileBuffer (FILE *InputFile, const long long FileLength)
{
    if (FileLength < 0)
    {
        printf ("\n" "ERROR: File Length (parameter 2) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", FileLength);
        return PTR_ERROR;
    }
    if (InputFile == NULL)
    {
        printf ("\n" "ERROR: InputFile (parameter 1) = NULL" "\n");
        return PTR_ERROR;
    }
    char *buffer = (char*) calloc (FileLength, sizeof(*buffer));
    fread (buffer, FileLength, sizeof(*buffer), InputFile);
    //rewind (InputFile);

    return buffer;
}

int FreeBuffer (char buffer[])
{
    free (buffer);
    if (buffer == NULL)
    {
        printf ("\n" "ERROR: Buffer is already NULL" "\n");
        return INT_ERROR;
    }
    else
    {
        buffer = NULL;
        return OK;
    }
}

void Buffer_Dump (const char buffer[])
{
    printf ("\n--------------\n" "<%s>" "\n--------------\n", buffer);
}

int CountLines (const char buffer[], const long long FileLength)
{
    if (FileLength < 0)
    {
        printf ("\n" "ERROR: File Length (parameter 2) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", FileLength);
        return INT_ERROR;
    }
    if (buffer == NULL)
    {
        printf ("\n" "ERROR: Buffer (parameter 1) = NULL" "\n");
        return INT_ERROR;
    }

    int count = 0;
    for (int i = 0; i < FileLength; i++)
        if (buffer[i] == '\n')
            count++;
    return count;
}

int Text_Construct (my_string* text, char buffer[], const long long FileLength, const int NumberOfLines)
{
    if (NumberOfLines < 0)
    {
        printf ("\n" "ERROR: Number Of Lines (parameter 3) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", NumberOfLines);
        return INT_ERROR;
    }
    if (FileLength < 0)
    {
        printf ("\n" "ERROR: File Length (parameter 3) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", FileLength);
        return INT_ERROR;
    }
    if (buffer == NULL)
    {
        printf ("\n" "ERROR: Buffer (parameter 2) = NULL" "\n");
        return INT_ERROR;
    }

    //char** text = (char**) calloc (NumberOfLines, sizeof(**text));
    int j = 0, curlen = 0, begstr = 0;

    for (int n = 0; n < NumberOfLines; n++)
    {
        begstr = j;
        while (j < FileLength && buffer[j] != '\r') j++;
        buffer[j] = '\0';

        j += 2;
        curlen = j - begstr - 2;

        assert (begstr < FileLength);

        text[n].str = &buffer[begstr];
        text[n].len = curlen;
        //printf ("\n" "text[%d].str = '%s' text[%d].len = %d" "\n", n, text[n].str, n, curlen);
        assert (text[n].str != NULL);
    }
}

int Text_Destruct (my_string* text, const int NumberOfLines)
{
    if (NumberOfLines < 0)
    {
        printf ("\n" "ERROR: Number Of Lines (parameter 3) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", NumberOfLines);
        return INT_ERROR;
    }

    for (int i = NumberOfLines; i >=0 ; i--)
    {
        free(text[i].str);
        if (text[i].str == NULL)
        {
            printf ("\n" "ERROR: text[%d] is already NULL" "\n", i);
            return INT_ERROR;
        }
        else
        {
            text[i].str = NULL;
            text[i].len = -1;
            return OK;
        }
    }
}

bool my_isalpha (const char symb)
{
    return (symb >= 'a' && symb <= 'z' || symb >= 'A' && symb <= 'Z');
}

char ToCapitalLetter (const char letter)
{
    return (letter >= 'a' && letter <= 'z')? (char)(int(letter) - ('a' - 'A')) : letter;
}

int RevStrCmp (const my_string* str1, const my_string* str2)
{
    int index1 = (*str1).len;
    int index2 = (*str2).len;
    char letter1 = (char)(0), letter2 = (char)(0);

    while (index1 >= 0 && index2 >= 0)
    {
        if (my_isalpha ((*str1).str[index1]) && my_isalpha ((*str2).str[index2]))
        {
            letter1 = ToCapitalLetter ((*str1).str[index1]);
            letter2 = ToCapitalLetter ((*str2).str[index2]);
            if (letter1 > letter2) return 1;
            else if (letter1 < letter2) return -1;
                 else index1--, index2--;
        }
        else
        {
            if (!my_isalpha ((*str1).str[index1])) index1--;
            else if (!my_isalpha ((*str2).str[index2])) index2--;
                 else index1--, index2--;
        }

    }
    return 0;
}

int my_StrCmp (const my_string* str1, const my_string* str2)
{
    int index1 = 0, index2 = 0;
    char letter1 = (char)(0), letter2 = (char)(0);

    while (index1 < (*str1).len && index2 < (*str2).len )
    {
        if (my_isalpha ((*str1).str[index1]) && my_isalpha ((*str2).str[index2]))
        {
            letter1 = ToCapitalLetter ((*str1).str[index1]);
            letter2 = ToCapitalLetter ((*str2).str[index2]);
            if (letter1 > letter2) return 1;
            else if (letter1 < letter2) return -1;
                 else index1++, index2++;
        }
        else
        {
            if (!my_isalpha ((*str1).str[index1])) index1++;
            else if (!my_isalpha ((*str2).str[index2])) index2++;
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

int CompSortFromBegin (const void* str1, const void* str2)
{
    return my_StrCmp(*(const my_string**) str1, *(const my_string**) str2);
}

int CompSortFromEnd (const void* str1, const void* str2)
{
    return RevStrCmp(*(const my_string**) str1, *(const my_string**) str2);
}

int TextSort (int SortType, my_string* text, const int NumberOfLines)
{
    /*for (int i = 0; i < NumberOfLines - 1; i++)
        for (int j = i + 1; j < NumberOfLines; j++)
            if ((*compare)(text[i], text[j]) == 0)
                my_swap (&text[i], &text[j]); */
    if (NumberOfLines < 0)
    {
        printf ("\n" "ERROR: Number Of Lines (parameter 3) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", NumberOfLines);
        return INT_ERROR;
    }
    if (text == NULL)
    {
        printf ("\n" "ERROR: Text (parameter 2) = NULL" "\n");
        return INT_ERROR;
    }

    /*printf ("Available types of sort:" "\n"
            " 1) SortFromBeg" "\n"
            " 2) SortFromEnd" "\n");
    printf ("Input number of preferred sorting: ");
    scanf ("%d", &SortType);*/

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
            return INT_ERROR;
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

void TextOut (const my_string* text, const int NumberOfLines)
{
    //printf ("\n" "Sorted text:" "\n");
    if (NumberOfLines < 0)
        printf ("\n" "ERROR: Number Of Lines (parameter 3) = %d < 0" "\n"
                     "It must be natural (>=0)" "\n", NumberOfLines);
    else
    {
        printf ("----------------------------------" "\n");
        for (int i = 0; i < NumberOfLines; i++)
            printf("%s\n", text[i].str);
        printf ("----------------------------------" "\n");
    }
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

/*int str_eq (char* str1, char* str2)
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
}*/
