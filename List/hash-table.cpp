#include "List_struct.cpp"
#include "hash_functions.cpp"

/***************************************************************************************************/

#define PTR_ERROR NULL
#define INT_ERROR -1
#define OK 1

/***************************************************************************************************/

const int HASH_TABLE_SIZE = 1009; // simple numbers: 503 1009 4093 8053 9973
const int MAXWORDLEN = 40;

const char* INPUTFILENAME = "dictionary.txt";
const char* OUTPUTFILENAME = "data6.csv";

/**********************************************************************************************************/

typedef struct hash_t
{
    head_t* table[HASH_TABLE_SIZE];
    unsigned long long nElements;
    unsigned long long (*function) (const char*);
} hash_t;

/**********************************************************************************************************/

hash_t* table_construct (const int table_size, unsigned long long (*function) (const char*));
//=====================================================================================================================
bool table_destruct (hash_t* This, const int table_size);
//=====================================================================================================================
FILE* FileOpen (const char* FilePath, const char* FOpenMode);
//=====================================================================================================================
bool FillHashTable (FILE* InputFile, hash_t* This);
//=====================================================================================================================
void Table_fprintf (FILE* fw, FILE* fr, hash_t* This);
//=====================================================================================================================
//long long FileLength (FILE *InputFile);
//=====================================================================================================================
//char* FileBuffer (FILE *InputFile, const long long FileLength);

/**********************************************************************************************************/

int main()
{
    printf ("# Hash table by Shulgin E." "\n\n");

    bool check = true;

    FILE* fr = FileOpen (INPUTFILENAME, "rb");
    if (fr == NULL) return -1;

    FILE* fw = FileOpen (OUTPUTFILENAME, "w");
    if (fw == NULL) return -1;

    hash_t* HashTable = table_construct (HASH_TABLE_SIZE, Hash_CircularShift);
    fprintf (fw, "CircularShift ;");
    Table_fprintf (fw, fr, HashTable);
    fprintf (fw, "\n");

    hash_t* HashTable1 = table_construct (HASH_TABLE_SIZE, Hash_AverageLetter);
    fprintf (fw, "AverageLetter ;");
    Table_fprintf (fw, fr, HashTable1);
    fprintf (fw, "\n");

    hash_t* HashTable2 = table_construct (HASH_TABLE_SIZE, Hash_SumofLetters);
    fprintf (fw, "SumofLetters ;");
    Table_fprintf (fw, fr, HashTable2);
    fprintf (fw, "\n");

    hash_t* HashTable3 = table_construct (HASH_TABLE_SIZE, Hash_Equal);
    fprintf (fw, "Equal ;");
    Table_fprintf (fw, fr, HashTable3);
    fprintf (fw, "\n");

    hash_t* HashTable4 = table_construct (HASH_TABLE_SIZE, Hash_WordLen);
    fprintf (fw, "WordLen ");
    Table_fprintf (fw, fr, HashTable4);

    fclose (fr);
    fclose (fw);

    check = table_destruct (HashTable, HASH_TABLE_SIZE);
    if (! check) return -1;

    return 1;
}

/**********************************************************************************************************/

hash_t* table_construct (const int table_size, unsigned long long (*function) (const char*))
{
    if (table_size < 0)
    {
        printf ("ERROR in (%s): Table Size = %d < 0" "\n\n", __FUNC__, table_size);
        return NULL;
    }

    hash_t* This = (hash_t*) calloc (1, sizeof(hash_t));

    //This->table = (head_t*) calloc (table_size, sizeof(head_t));

    for (int i = 0; i < table_size; i++)
        This->table [i] = head_constructor();

    This->nElements = table_size;

    This->function = function;

    return This;
}

//=====================================================================================================================

bool table_destruct (hash_t* This, const int table_size)
{
    assert (This);

    if (table_size < 0)
    {
        printf ("ERROR in (%s): Table Size = %d < 0" "\n\n", __FUNC__, table_size);
        return false;
    }

    for (int i = 0; i < table_size; i++)
        head_destructor (This->table [i]);

    This->nElements = -1;

    This->function = NULL;

    free (This);
    This = NULL;

    return true;
}

//=====================================================================================================================

bool FillHashTable (FILE* InputFile, hash_t* This)
{
    assert (InputFile);
    assert (This);

    fpos_t point;
    fgetpos (InputFile, &point);

    char str [MAXWORDLEN] = {};
    int flag = 1;

    while (flag != EOF)
    {
        while (flag > 0)
            flag = fscanf (InputFile, "%*[^A-Za-z0-9]");

        if (flag != EOF)
            flag = fscanf (InputFile, "%[A-Za-z0-9]", str);

        if (flag == EOF)
            break;

        unsigned long long ip = This->function(str);

        ip = ip % This->nElements;

        list_t* elem = elem_constructor (str);

        list_insert (This->table[ip], This->table[ip]->head_elem, elem);
    }

    fsetpos (InputFile, &point);

    rewind (InputFile);

    return true;
}

//=====================================================================================================================

void Table_fprintf (FILE* fw, FILE* fr, hash_t* This)
{
    assert (fw);
    assert (fr);
    assert (This);

    FillHashTable (fr, This);

    for (unsigned int i = 0; i < This->nElements; i++)
        fprintf (fw, "%d;", This->table[i]->nElements);
}

//=====================================================================================================================

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

//=====================================================================================================================

/*long long FileLength (FILE *InputFile)
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
}*/

//=====================================================================================================================

/*char* FileBuffer (FILE *InputFile, const long long FileLength)
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
} */
