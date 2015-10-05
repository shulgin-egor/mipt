#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <locale>

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

int RevStrCmp (const char str1[], const char str2[]);
bool my_isalpha (const char symb);
void my_swap (char** str1, char** str2);
void TextSort (int (*compare) (const char str1[], const char str2[]), char* text[], int NumberOfLines);
int TextOut (char* SortType, char* text[], int NumberOfLines);

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

    TextOut ("", text, nLines);

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
    //printf (" %d ", FileLength);
    for (int i = 0; i < FileLength; i++)
    {
        //printf ("%c", buffer[i]);
        if (buffer[i] == '\n')
            count++;
    }
    //printf ("1. nLines = %d" "\n", count);
    return count;
}

int SplitBuffer (char *text[], char buffer[], const long long FileLength, int NumberOfLines)
{
    //printf ("\nSPLITBUFFER START\n");
    //char** text = (char**) calloc(numberOfLines, sizeof(char));
  //char** text = (char**) calloc (NumberOfLines, sizeof(**text));
    //char *tempstr = (char*) calloc ()
    int i = 0, j = 0, curlen = 0, begstr = 0;
    for (int n = 0; n < NumberOfLines; n++)
    {
        begstr = j;
        while (j < FileLength && buffer[j] != '\r') j++;
        //for (; j < FileLength && buffer[j] != '\n'; j++) printf (".%c", buffer[j]);
        buffer[j] = '\0';
        j += 2;
        //curlen = j - begstr - 3;
        //char *bufstr = (char*) calloc (strlen, sizeof(char*));
        //my_string bufstr = {&buffer[j], curlen};
        text[n] = &buffer[begstr]/*&bufstr*/;
        //my_string bufstr = {NULL, -1};

    }
    //printf ("\nSPLITBUFFER END\n");
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

int RevStrCmp (const char str1[], const char str2[])
{
    int len1 = strlen (str1) - 1; //printf ("len1 = %d ", len1);
    int len2 = strlen (str2) - 1; //printf ("len2 = %d\n\n", len2);
    bool f1 = false, f2 = false;

    while (len1 > 0 && len2 > 0 && !(f1 && f2))
    {
        f1 = f2 = true;
        if (!my_isalpha(str1[len1]))
        {
            len1--;
            f1 = false;
            //printf ("FLAG1 ");
        }
        //printf ("len1 = %d symbol = %c\n", len1, str1[len1]);
        if (!my_isalpha(str2[len2]))
        {
            len2--;
            f2 = false;
            //printf ("FLAG2 ");
        }
        //printf ("len2 = %d symbol = %c\n", len2, str2[len2]);
    }

    return (str1[len1] > str2[len2])? 1 : 0;
}

void my_swap (char** str1, char** str2)
{
    char *temp = *str1;;
    //temp = strdup (str1);
    //if (temp == NULL) printf ("!NULL");
    *str1 = *str2;
    *str2 = temp;
    //free (temp);
    //printf ("OK");
}

void TextSort (int (*compare) (const char str1[], const char str2[]), char* text[], int NumberOfLines)
{
    for (int i = 0; i < NumberOfLines - 1; i++)
        for (int j = i + 1; j < NumberOfLines; j++)
            if ((*compare)(text[i], text[j]) == 0)
                my_swap (&text[i], &text[j]);
}

int TextOut (char* SortType, char* text[], int NumberOfLines)
{
    printf ("Input preferred type of sort: ");
    scanf ("%s", SortType);
    if (SortType == "CmpFromBeg")
        TextSort (&stricmp, text, NumberOfLines);
    else if (SortType == "CmpFromEnd")
            TextSort (&RevStrCmp, text, NumberOfLines);
         else
         {
            printf ("ERROR: There is no such type of sort");
            return ERROR;
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
    printf ("\n" "Sorted text:" "\n");
    for (int i = 0; i < NumberOfLines; i++)
        printf("%s\n", text[i]);
    return 1;
}
