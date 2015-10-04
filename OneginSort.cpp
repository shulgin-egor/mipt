#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale>

#define FOPEN_ERROR NULL
#define FREEBUFFER_ERROR -1

struct my_string
    {
        char *str;
        int len;
    };

long long FileLength (FILE *InputFile);
char* FileBuffer (FILE *InputFile, const long long FileLength);
int FreeBuffer (char buffer[]);
int CountNumberOfLines (const char buffer[], const long long FileLength);
int SplitBuffer (char *text[], char buffer[], const long long FileLength, int NumberOfLines);
FILE *FileOpen (char* FilePath, char* FOpenMode);

int main()
{
    printf ("# Program by Shulgin E. \n");
    setlocale (LC_ALL, "Russian");

    char FilePath[260] = "***";
    char ReadMode[2] = "*";
    //printf ("Input file path: ");
    //scanf ("%s", FilePath);

    /*bool ErrorCheck = 1;
    ErrorCheck = FileOpen (FilePath, ReadMode);
    if (ErrorCheck == 0) return 0;  */

    FILE *InputFile;
    InputFile = FileOpen (FilePath, ReadMode);
    //FilePath = "input.txt";
    //ReadMode= "r";
    //InputFile = fopen (FilePath, ReadMode);
    if (InputFile == FOPEN_ERROR) return 0;
    printf ("\n-----------\n"
            "<%s> <%s>"
            "\n-----------\n", FilePath, ReadMode);

    long long file_len = 0;
    file_len = FileLength (InputFile)/*-8*/;
    char* buffer = FileBuffer (InputFile, file_len);
    //const char* bufCopy = (char*) calloc (file_len, sizeof(*buffer));
    //memcpy(buffer, bufCopy, sizeof(buffer));
    //printf("\n<%s>\n", bufCopy);

    printf ("\n--------------\n" "<%s>" "\n--------------\n", buffer);
    int nLines = 0;
    nLines = CountNumberOfLines (buffer, file_len);
    printf ("nLines = %d" "\n", nLines);
    /*int count = 0;
    for (int i = 0; i < file_len; i++)
    {
        printf ("%c", buffer[i]);
        if (buffer[i] == '\n')
            count++;
    } nLines = count;
    */
    char** text = (char**) calloc (nLines, sizeof(**text));
    SplitBuffer (text, buffer, file_len, nLines);

    // for (int i = 0; i < nLines; i++)
    //   printf("<%s>\n", text[i]);

    fclose (InputFile);
    int Buf_check = 1;
    Buf_check = FreeBuffer (buffer);
    if (Buf_check == FREEBUFFER_ERROR) return 0;
    //FreeBuffer (bufCopy);
    // free (buffer);
    // buffer = NULL;
    return 1;
}

long long FileLength (FILE *InputFile)
{
    //FILE* f = fopen (FilePath, ReadMode);
    fseek (InputFile, 0, SEEK_END);
    long long len = 0;
    len = ftell(InputFile);
    rewind (InputFile);
    //fclose (InputFile);

    return len;
}

char* FileBuffer (FILE *InputFile, const long long FileLength)
{
    //FILE* f = fopen (FilePath, ReadMode);
    char *buffer = (char*) calloc (FileLength, sizeof(*buffer));
    fread (buffer, FileLength, sizeof(*buffer), InputFile);
    rewind (InputFile);
    //fclose (f);

    return buffer;
}

int FreeBuffer (char buffer[])
{
    free (buffer);
    if (buffer == NULL)
    {
        printf ("\n" "ERROR: Buffer is already NULL" "\n");
        return FREEBUFFER_ERROR;
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
    printf ("\nSPLITBUFFER START\n");
    //char** text = (char**) calloc(numberOfLines, sizeof(char));
  //char** text = (char**) calloc (NumberOfLines, sizeof(**text));
    //char *tempstr = (char*) calloc ()
    int i = 0, j = 0, curlen = 0, begstr = 0;
    for (int n = 0; n < NumberOfLines; n++)
    {
        begstr = j;
        while (j < FileLength && buffer[j] != '\r')
        {
            //printf ("%c", buffer[j]);
            j++;
        }
        //for (; j < FileLength && buffer[j] != '\n'; j++) printf (".%c", buffer[j]);
        buffer[j] = '\0';
        j += 2;
        curlen = j - begstr - 1;
        //char *bufstr = (char*) calloc (strlen, sizeof(char*));
        //my_string bufstr = {&buffer[j], curlen};
        text[n] = &buffer[begstr]/*&bufstr*/;
        //my_string bufstr = {NULL, -1};

    }
    printf ("\nSPLITBUFFER END\n");
}

FILE *FileOpen (char* FilePath, char* FOpenMode)
{
    /*printf ("Input file path: ");
    int s = scanf ("%s", FilePath);
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


