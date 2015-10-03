#include <stdio.h>
#include <stdlib.h>
#include <locale>

#define FOPEN_ERROR NULL
#define FREEBUFFER_ERROR -1

long long FileLength (FILE *InputFile);
char* FileBuffer (FILE *InputFile, const long long FileLength);
int FreeBuffer (char buffer[]);
int CountNumberofLines (const char buffer[], const long long FileLength);
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
    if (InputFile == FOPEN_ERROR) return 0;
    printf ("\n-----------\n"
            "<%s> <%s>"
            "\n-----------\n", FilePath, ReadMode);

    long long file_len = 0;
    file_len = FileLength (InputFile)/*-8*/;
    char* buffer = FileBuffer (InputFile, file_len);

    printf ("\n--------------\n" "<%s>" "\n--------------\n", buffer);
    int nLines = 0;
    nLines = CountNumberofLines (buffer, file_len);
    printf ("nLines = %d" "\n", nLines);


    fclose (InputFile);
    int Buf_check = 1;
    Buf_check = FreeBuffer (buffer);
    if (Buf_check == FREEBUFFER_ERROR) return 0;
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
    char* buffer = (char*) calloc (FileLength, sizeof(char));
    fread (buffer, FileLength, sizeof(char), InputFile);
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

int CountNumberofLines (const char buffer[], const long long FileLength)
{
    int count = 0;
    for (int i = 0; i << FileLength; i++)
    {
        printf (buffer[i]);
        if (buffer[i] == "\n")
            count++;
    }
    printf ("1. nLines = %d" "\n", count);
    return count;
}

FILE *FileOpen (char* FilePath, char* FOpenMode)
{
    printf ("Input file path: ");
    int s = scanf ("%s", FilePath);
    printf ("Input file open mode: ");
    scanf ("%s", FOpenMode);//FILE *InputF

    FILE *InputFile;
    InputFile = fopen (FilePath, FOpenMode);//FILE *InputF
    if (InputFile == NULL)
    {
        printf ("\n" "ERROR: Could not find such file, "
                     "please restart the program" "\n");//FILE *InputF
        return FOPEN_ERROR;
    }
    else return InputFile;
}


