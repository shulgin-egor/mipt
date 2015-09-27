#include <stdio.h>
#include <stdlib.h>

long long FileLength (const char FileName[]);
char* FileBuffer (const char FileName[], const char ReadMode[], long long FileLength);

main()
{
    printf("# Program by Shulgin E. \n");

    /*FILE* f = fopen ("input.txt", "rb");
    fseek (f, 0, SEEK_END);
    int len = 0;
    len = ftell(f); printf ("--- %d --- \n", len);
    rewind(f);
    char* buffer = (char*)calloc(len, sizeof(*buffer));
    fread (buffer, len, sizeof(*buffer), f);
    printf ("\n" "%s-" "\n", buffer);
    fclose(f); */


   // free(buffer);
   // buffer = NULL;

}

long long FileLength (const char FileName[], const char ReadMode[])
{
    FILE* f = fopen (FileName, ReadMode);
    fseek (f, 0, SEEK_END);
    long long len = 0;
    len = ftell(f);
    rewind (f);
    fclose (f);
    return len;
}

char* FileBuffer (const char FileName[], const char ReadMode[], long long FileLength)
{
    FILE* f = fopen (FileName, ReadMode);
    char* buffer = (char*)calloc(FileLength, sizeof(*buffer));
    fread (buffer, FileLength, sizeof(*buffer), f);
    rewind (f);
    fclose (f);
    return buffer;
    free (buffer);
    buffer = NULL;
}
