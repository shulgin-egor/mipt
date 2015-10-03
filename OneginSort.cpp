#include <stdio.h>
#include <stdlib.h>
#include <locale>

#define FOPEN_ERROR NULL

long long FileLength (const char FilePath[], const char ReadMode[]);
char* FileBuffer (const char FilePath[], const char ReadMode[], const long long FileLength);
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
    printf ("<%s>" "\n" "<%s>", FilePath, ReadMode);

    /*FILE* f = fopen ("input.txt", "rb");
    fseek (f, 0, SEEK_END);
    int len = 0;
    len = ftell(f); printf ("--- %d --- \n", len);
    rewind(f);
    char* buffer = (char*)calloc(len, sizeof(*buffer));
    fread (buffer, len, sizeof(*buffer), f);
    printf ("\n" "%s-" "\n", buffer);
    fclose(f); */


    //long long file_len = 0;
    //file_len = FileLength ("input.txt", "rb")/*-8*/;
    //char* buffer = FileBuffer ("input.txt", "rb", file_len);

    //printf ("--------------\n" "<%s>" "\n--------------", buffer);



    //free (buffer);
    //buffer = NULL;
    return 1;
}

long long FileLength (const char FilePath[], const char ReadMode[])
{
    FILE* f = fopen (FilePath, ReadMode);
    fseek (f, 0, SEEK_END);
    long long len = 0;
    len = ftell(f);
    rewind (f);
    fclose (f);

    return len;
}

char* FileBuffer (const char FilePath[], const char ReadMode[], const long long FileLength)
{
    FILE* f = fopen (FilePath, ReadMode);
    char* buffer = (char*)calloc(FileLength, sizeof(*buffer));
    fread (buffer, FileLength, sizeof(*buffer), f);
    rewind (f);
    fclose (f);

    return buffer;
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


