#include "Processor.cpp"
#include "Commands.cpp"
#include <stdlib.h>
//#include "Assembler.cpp"

#define INT_ERROR -1
#define PTR_ERROR NULL

const int MaxFileName = 20;

STACK_TYPE* MakeMachineCode (long long* CodeSize);

bool ExecuteCode (const STACK_TYPE* MachineCode, long long CodeSize);

void MachineCode_Dump (const STACK_TYPE* MachineCode, long long CodeSize);

FILE* FileOpen (const char* FilePath, const char* FOpenMode);
long long FileLength (FILE* InputFile);
char* FileBuffer (FILE *InputFile, const long long FileLength);

int main()
{
    printf ("# Executor program by Shulgin E." "\n");

    long long CodeSize = 0;
    STACK_TYPE* MachineCode = MakeMachineCode (&CodeSize);
    if (MachineCode == NULL) return 0;

    ExecuteCode (MachineCode, CodeSize);

    return 1;
}

double* MakeMachineCode (long long* CodeSize)
{
    printf ("\nFunction 'MakeMachineCode'\n");

    char BinaryFName[MaxFileName] = "binary.myexe";
    FILE* BinaryFile = FileOpen (BinaryFName, "r");
    if (BinaryFile == PTR_ERROR) return PTR_ERROR;

    int cur_cmd = 0, index = 0;
    *CodeSize = FileLength (BinaryFile);
    //double* buffer = (double*) calloc (CodeSize, sizeof(*buffer));
    STACK_TYPE* buffer = (double*) calloc (*CodeSize, sizeof(STACK_TYPE*));

    char* buffer1 = FileBuffer (BinaryFile, *CodeSize);
    //printf ("\nbuffer1\n<%s>\n\n", buffer1);
    rewind (BinaryFile);

    while (fscanf (BinaryFile, "%d ", &cur_cmd) != EOF /*&& printf ("%d-", cur_cmd)*/)
        switch (cur_cmd)
        {
            case (END):
                //buffer[index] = cur_cmd;
                break;
            case (OUT):
                buffer[index++] = cur_cmd;
                break;
            case (PUSH):
                buffer[index++] = cur_cmd;
                if (fscanf (BinaryFile, "%d", &cur_cmd) == 0)
                {
                    buffer[index++] = 0;
                    fscanf (BinaryFile, "%c", &buffer[index++]);
                }
                else buffer[index++] = cur_cmd;
                break;
            case (POP):
                //printf("*");
                buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%c", &buffer[index++]);
                //char ch;
                //fscanf (BinaryFile, "%c", &ch);
                //buffer[index++] = ch;
                break;
            case (POP_):
                buffer[index++] = cur_cmd;
                break;
            case (ADD):
                buffer[index++] = cur_cmd;
                break;
            case (SUB):
                buffer[index++] = cur_cmd;
                break;
            case (MUL):
                buffer[index++] = cur_cmd;
                break;
            case (DIV):
                buffer[index++] = cur_cmd;
                break;
            default:
                printf ("\n" "ERROR: Wrong command '%d' in file '%s'" "\n", cur_cmd, BinaryFName);
                free (buffer);
                buffer = NULL;
                fclose (BinaryFile);
                return PTR_ERROR;
        }

    //printf("\n<%c>", buffer[1]);
    //printf("<%c>\n\n", buffer[3]);
    //printf("\n");

    //buffer[index] = cur_cmd;
    for (int i = 0; i < *CodeSize; i++) printf ("%lg ", buffer[i]);
    printf("\n");
    //for (int i = 0; i < *CodeSize; i++) printf ("<%c> ", buffer[i]);
    fclose (BinaryFile);

    return buffer;
}

void MachineCode_Dump (const STACK_TYPE* MachineCode, long long CodeSize)
{
    assert(MachineCode);

    printf ("--------------MachineCode_Dump start--------------" "\n");
    for (int i = 0; i < CodeSize; i++) printf ("%lg ", MachineCode[i]);
    printf ("\n" "--------------MachineCode_Dump end----------------" "\n");
}

bool ExecuteCode (const STACK_TYPE* MachineCode, long long CodeSize)
{
    assert(MachineCode);

    //MachineCode_Dump (MachineCode, CodeSize);

    printf ("\nFunction 'ExecuteCode'\n");

    cpu_t This;
    cpu_constructor (&This);

    char register_name = '*';
    int index = -1;
    int temp = 0;
    //printf("CodeSize = %d\n",CodeSize);
    //for (int i = 0; i < CodeSize; i++) printf ("%lg ", MachineCode[i]); printf("\n");
    //printf ("<%c>", MachineCode[8]);

    while ((++index < CodeSize) && printf("%d-", (int)MachineCode[index]))
        switch ((int) MachineCode[index])
        {
            case (END):
                cpu_dump (&This);
                cpu_destructor (&This);
                break;
            case (OUT):
                cpu_dump (&This);
                break;
            case (PUSH):
                if (!MachineCode[++index])
                {
                    //register_name = MachineCode[index + 1];
                    cpu_push (&This, (char)MachineCode[++index]);
                }
                else stack_push (&(This.stack), MachineCode[index]);
                break;
            case (POP):
                temp = MachineCode[++index];
                //temp = temp;
                //register_name = MachineCode[++index];
                printf ("<%lg><'a' = %d><%d>", MachineCode[index], 'a', temp);
                cpu_pop (&This, MachineCode[index]);
                //char ch;
                //fscanf (BinaryFile, "%c", &ch);
                //buffer[index++] = ch;
                break;
            case (POP_):
                stack_pop (&(This.stack));
                break;
            case (ADD):
                stack_add (&(This.stack));
                break;
            case (SUB):
                stack_sub (&(This.stack));
                break;
            case (MUL):
                stack_mul (&(This.stack));
                break;
            case (DIV):
                stack_div (&(This.stack));
                break;
            default:
                printf ("\n" "ERROR: Wrong command '%lg' in (%s) '%s'" "\n", MachineCode[index], __FUNC__);
                return false;
        }

    return true;
}

FILE* FileOpen (const char* FilePath, const char* FOpenMode)
{
    /*
    printf ("Input file path: ");
    scanf ("%s", FilePath);
    printf ("Input file open mode: ");
    scanf ("%s", FOpenMode);
    */

    FILE* InputFile = fopen (FilePath, FOpenMode);
    if (InputFile == NULL)
    {
        printf ("\n" "ERROR: Could not find file '%s', "
                     "please restart the program" "\n", FilePath);
        return PTR_ERROR;
    }
    else return InputFile;
}

long long FileLength (FILE* InputFile)
{
    assert (InputFile);

    /*int check = fseek (InputFile, 0, SEEK_END);
    if (check != 0)
    {
        printf ("\n" "ERROR in (%s): Probably file is not opened" "\n", __FUNC__);
        return INT_ERROR;
    }
    rewind (InputFile);*/

    long long len = 0;
    int cur_cmd = 0;
    char register_name = '*';
    //len = ftell(InputFile);
    //printf("***");

    while (fscanf (InputFile, "%d ", &cur_cmd) != EOF /*&& printf ("%d-", cur_cmd)*/)
        switch (cur_cmd)
        {
            case (0):
                len++;
                break;
            case (1):
                len++;
                break;
            case (2):
                len++;
                if (fscanf (InputFile, "%d", &cur_cmd) == 0)
                {
                    len++;
                    fscanf (InputFile, "%c", &register_name);
                }
                len++;
                break;
            case (3):
                len += 2;
                fscanf (InputFile, "%c", &register_name);
                break;
            case (33):
                len++;
                break;
            case (4):
                len++;
                break;
            case (5):
                len++;
                break;
            case (6):
                len++;
                break;
            case (7):
                len++;
                break;
            default:
                printf ("\n" "ERROR: Wrong command '%d' in file '%s'" "\n", cur_cmd, InputFile);
                //fclose (InputFile);
                return INT_ERROR;
        }

    rewind (InputFile);
    //printf("\n len = %d", len);
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

