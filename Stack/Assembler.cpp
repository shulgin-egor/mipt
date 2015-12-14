#include <stdio.h>
#include <string.h>
#include "Commands.cpp"
#include "Processor.cpp"
//#include "Commands.cpp"

#define ProgramName "factorial"
#define INT_ERROR -1
#define PTR_ERROR NULL

#define FileName "binary.myexe"

//#define STANDART_PROG_NAME "program.in"
//#define STANDART_BINARY_NAME "binary.myexe"

const int MaxCmdName = 15;
const int MaxJumpName = 15;
const int MaxNJumps = 20;
const int MaxRetAdr= 100;
const int MaxFileName = 30;

typedef struct
{
    char name [MaxJumpName];
    int address;
} jump_t;

void help_function();
bool asm_function (const char* ProgFName, const char* BinaryFName);

char* MakeMachineCode (long long* CodeSize, jump_t arr_jumps[], int* NJumps);

void MachineCode_Dump (const char* MachineCode, long long CodeSize, jump_t arr_jumps[], int* NJumps);

void MachineCode_printf (const char* MachineCode, long long CodeSize, jump_t arr_jumps[], const int NJumps);

bool in (const char cur_jump[], jump_t arr_jumps[], const int NJumps);

FILE* FileOpen (const char* FilePath, const char* FOpenMode);
long long FileLength (FILE* InputFile, jump_t arr_jumps[], int* NJumps);
char* FileBuffer (FILE *InputFile, const long long FileLength);


int main (const int argc, char* argv[])
{
    printf ("# Assembler program by Shulgin E." "\n");
    //char* ProgFName = STANDART_PROG_NAME, BinaryFName = STANDART_BINARY_NAME;

    char* ProgFName = ProgramName;                 // Standard
    char* BinaryFName = "binary.myexe";             // names

    if (argc == 1)
    {
        //return asm_function (ProgFName, BinaryFName);
        long long CodeSize = 0;

        jump_t arr_jumps [MaxNJumps] = {};
        int NJumps = 0;

        asm_function (ProgFName, BinaryFName);

        char* MachineCode = MakeMachineCode (&CodeSize, arr_jumps, &NJumps);
        if (MachineCode == NULL) return 0;

        MachineCode_Dump (MachineCode, CodeSize, arr_jumps, &NJumps);

        MachineCode_printf (MachineCode, CodeSize, arr_jumps, NJumps);
    }

    if (argc == 2)
        if (argv[1] == "--help")
            {
                help_function();
                return 1;
            }
        else ProgFName = argv[1];
    else
    {
        ProgFName = argv[1];
        BinaryFName = argv[2];
    }

    /*long long CodeSize = 0;
    jump_t arr_jumps [MaxNJumps] = {};
    int NJumps = 0;

    asm_function (ProgFName, BinaryFName);

    char* MachineCode = MakeMachineCode (&CodeSize, arr_jumps, &NJumps);
    if (MachineCode == NULL) return 0;

    MachineCode_printf (MachineCode, CodeSize, arr_jumps, NJumps);*/

    return 1;
}


bool asm_function (const char* ProgFName, const char* BinaryFName)
{
    //FILE *InputFile = fopen (ProgFName, "r");
    //FILE *OutputFile = fopen (BinaryFName, "w");

    FILE *ProgramFile = FileOpen (ProgFName, "r");
    FILE *BinaryFile = FileOpen (BinaryFName, "w");

    if (ProgramFile == NULL)
    {
        printf ("\n" "ERROR: Could not find ProgramFile '%s', "
                     "please restart the program" "\n", ProgFName);
        return false;
    }
    if (BinaryFile == NULL)
    {
        printf ("\n" "ERROR: Could not find BinaryFile '%s', "
                     "please restart the program" "\n", BinaryFName);
        return false;
    }

    char cur_str[MaxCmdName] = "";
    double value = 0;

    while (fscanf (ProgramFile, "%s", cur_str) != EOF)
    {
        if (_stricmp (cur_str, "end") == 0)
            fprintf (BinaryFile, "%d\n", END);
        else if (_stricmp (cur_str, "out") == 0)
            fprintf (BinaryFile, "%d\n", OUT);
        else if (_stricmp (cur_str, "push") == 0)
            if (fscanf (ProgramFile, "%lg", &value) == 0)
            {
                fscanf (ProgramFile, "%s", cur_str);
                fprintf (BinaryFile, "%d", PUSH_X);
                fprintf (BinaryFile, " %c\n", cur_str[0]);
            }
            else fprintf (BinaryFile, "%d %lg\n", PUSH, value);
        else if (_stricmp (cur_str, "pop") == 0)
        {
            fprintf (BinaryFile, "%d ", POP_X);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%c\n", cur_str[0]);
        }
        else if (_stricmp (cur_str, "pop_") == 0)
            fprintf (BinaryFile, "%d\n", POP);
        else if (_stricmp (cur_str, "add") == 0)
            fprintf (BinaryFile, "%d\n", ADD);
        else if (_stricmp (cur_str, "sub") == 0)
            fprintf (BinaryFile, "%d\n", SUB);
        else if (_stricmp (cur_str, "mul") == 0)
            fprintf (BinaryFile, "%d\n", MUL);
        else if (_stricmp (cur_str, "div") == 0)
            fprintf (BinaryFile, "%d\n", DIV);
        else if (_stricmp (cur_str, "sqrt") == 0)
            fprintf (BinaryFile, "%d\n", SQRT);
        else if (_stricmp (cur_str, "dup") == 0)
            fprintf (BinaryFile, "%d\n", DUP);
        else if (_stricmp (cur_str, "in") == 0)
            fprintf (BinaryFile, "%d\n", IN);
        else if (_stricmp (cur_str, "ja") == 0)
        {
            fprintf (BinaryFile, "%d ", JA);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "jae") == 0)
        {
            fprintf (BinaryFile, "%d ", JAE);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "jb") == 0)
        {
            fprintf (BinaryFile, "%d ", JB);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "jbe") == 0)
        {
            fprintf (BinaryFile, "%d ", JBE);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "je") == 0)
        {
            fprintf (BinaryFile, "%d ", JE);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "jne") == 0)
        {
            fprintf (BinaryFile, "%d ", JNE);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "jmp") == 0)
        {
            fprintf (BinaryFile, "%d ", JMP);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if ( cur_str[strlen (cur_str) - 1] == ':')
            fprintf (BinaryFile, "%d %s\n", JUMP_VAR, cur_str);
        else if (_stricmp (cur_str, "call") == 0)
        {
            fprintf (BinaryFile, "%d ", CALL);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
        else if (_stricmp (cur_str, "ret") == 0)
            fprintf (BinaryFile, "%d\n", RET);
        else if (_stricmp (cur_str, "function") == 0)
        {
            fprintf (BinaryFile, "%d ", FUNC_VAR);
            fscanf (ProgramFile, "%s", cur_str);
            fprintf (BinaryFile, "%s\n", cur_str);
        }
    }

    fclose (ProgramFile);
    fclose (BinaryFile);

    return true;
}

char* MakeMachineCode (long long* CodeSize, jump_t arr_jumps[], int* NJumps)
{
    //printf ("\nFunction (MakeMachineCode) start\n");

    char BinaryFName[MaxFileName] = FileName;
    FILE* BinaryFile = FileOpen (BinaryFName, "r");
    if (BinaryFile == PTR_ERROR) return PTR_ERROR;

    int cur_cmd = 0, index = 0, i = 0;
    STACK_TYPE value = 0;
    char cur_jump [MaxJumpName] = "\0";
    //jump_t arr_jumps [MaxNJumps] = {};

    *CodeSize = FileLength (BinaryFile, arr_jumps, NJumps);
    if (*CodeSize < 0)
    {
        printf ("\n" "ERROR in (%s): Wrong command '%d' in file '%s'" "\n", __FUNC__, cur_cmd, BinaryFName);
        fclose (BinaryFile);
        return PTR_ERROR;
    }

    char* buffer = (char*) calloc (*CodeSize, sizeof(*buffer));

    //char* buffer1 = FileBuffer (BinaryFile, *CodeSize);
    //printf ("\n<%s>\n\n", buffer1);
    //rewind (BinaryFile);

    while (fscanf (BinaryFile, "%d ", &cur_cmd) != EOF)
    {
        //printf ("%d-", cur_cmd);
        switch (cur_cmd)
        {
            case (END):
                //buffer[index] = cur_cmd;
                break;
            case (OUT):
                buffer[index++] = cur_cmd;
                break;
            case (PUSH_X):
            {
                buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%c", &buffer[index++]);
                break;
            }
            case (PUSH):
            {
                buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%lg", &value);
                *((STACK_TYPE*)(buffer + index)) = value;
                index += sizeof(STACK_TYPE);
                break;
            }
            case (POP_X):
            {
                buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%c", &buffer[index++]);
                break;
            }
            case (POP):
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
            case (SQRT):
                buffer[index++] = cur_cmd;
                break;
            case (DUP):
                buffer[index++] = cur_cmd;
                break;
            case (IN):
                buffer[index++] = cur_cmd;
                break;
            case (JA):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                //printf("jump = %d",*((int*)(buffer + index)));
                index += sizeof(int);

                break;
            }
            case (JAE):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                index += sizeof(int);

                break;
            }
            case (JB):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                //printf("jump = %d",*((int*)(buffer + index)));
                index += sizeof(int);

                break;
            }
            case (JBE):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                index += sizeof(int);

                break;
            }
            case (JE):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                index += sizeof(int);

                break;
            }
            case (JNE):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                index += sizeof(int);

                break;
            }
            case (JMP):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                index += sizeof(int);

                break;
            }
            case (JUMP_VAR):
            {
                fscanf (BinaryFile, "%s", cur_jump);
                break;
            }
            case (CALL):
            {
                buffer[index++] = cur_cmd;

                fscanf (BinaryFile, "%s", cur_jump);

                for (i = 0; _stricmp (arr_jumps[i].name, cur_jump) != 0; i++);

                *((int*)(buffer + index)) = arr_jumps[i].address;
                //printf ("***call address = %d", *((int*)(buffer + index)));
                index += sizeof(int);

                break;
            }
            case (RET):
                buffer[index++] = cur_cmd;
                break;
            case (FUNC_VAR):
                //buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%s", cur_jump);
                //index++;
                break;
            default:
                printf ("\n" "ERROR in (%s): Wrong command '%d' in file '%s'" "\n", __FUNC__, cur_cmd, BinaryFName);
                free (buffer);
                buffer = NULL;
                fclose (BinaryFile);
                return PTR_ERROR;
        }
    }

    fclose (BinaryFile);

    return buffer;
}

void MachineCode_Dump (const char* MachineCode, long long CodeSize, jump_t arr_jumps[], int* NJumps)
{
    assert(MachineCode);

    printf ("\n" "--------------MachineCode_Dump start--------------" "\n");

    for (int i = 0; i < *NJumps; i++)
    {
        printf ("arr_jumps[%d].address = %d\n", i, arr_jumps[i].address);
        printf ("arr_jumps[%d].name = %s" "\n\n", i, arr_jumps[i].name);
    }

    for (int i = 0; i < CodeSize; i++) printf ("%d ", MachineCode[i]);

    printf ("\n" "--------------MachineCode_Dump end----------------" "\n");
}

void MachineCode_printf (const char* MachineCode, long long CodeSize, jump_t arr_jumps[], const int NJumps)
{
    char BinaryFName[MaxFileName] = "binary";
    FILE* BinaryFile = FileOpen (BinaryFName, "w");
    if (BinaryFile == PTR_ERROR) return;

    /*fprintf (BinaryFile, "%d" "\n", NJumps);
    //printf ("%d" "\n", NJumps);
    for (int i = 0; i < NJumps; i++) //printf ("%d %s\n", arr_jumps[i].address, arr_jumps[i].name);
        fprintf (BinaryFile, "%d %s\n", arr_jumps[i].address, arr_jumps[i].name);
    */
    fprintf (BinaryFile, "%d" "\n", CodeSize);
    for (int i = 0; i < CodeSize; i++)  //printf ("%d ", MachineCode[i]);
        fprintf (BinaryFile, "%d ", MachineCode[i]);
}

bool in (const char cur_jump[], jump_t arr_jumps[], const int NJumps)
{
    for (int i = 0; i < NJumps; i++)
    {
        if ( _stricmp (arr_jumps[i].name, cur_jump) == 0 )
            return true;
        /*printf("\nstrcmp = %d", strcmp (arr_jumps[i].name, cur_jump));
        printf("\n______jump_name = <%s>\n", cur_jump);
        printf("\n______arr_jumps[%d].name = <%s>\n", i, arr_jumps[i].name);*/
    }
    return false;
}

long long FileLength (FILE* InputFile, jump_t arr_jumps[], int* NJumps)
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
    //char func_name[MaxFuncName] = "\0";
    STACK_TYPE temp = 0;

    char cur_jump [MaxJumpName] = "\0";
    *NJumps = -1;
    //jump_t arr_jumps [MaxNJumps] = {};
    //int NJumps = 0;
    //len = ftell(InputFile);
    //printf("***");

    while (fscanf (InputFile, "%d ", &cur_cmd) != EOF)
    {
        //printf ("%d_", cur_cmd);
        len++;
        switch (cur_cmd)
        {
            case (END):
                break;
            case (OUT):
                break;
            case (PUSH_X):
                len++;
                fscanf (InputFile, "%c", &register_name);
                break;
            case (PUSH):
                fscanf (InputFile, "%lg", &temp);
                len += sizeof(STACK_TYPE);
                break;
            case (POP_X):
                len++;
                fscanf (InputFile, "%c", &register_name);
                break;
            case (POP):
                break;
            case (ADD):
                break;
            case (SUB):
                break;
            case (MUL):
                break;
            case (DIV):
                break;
            case (SQRT):
                break;
            case (DUP):
                break;
            case (IN):
                break;
            case (JA):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                {
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);
                    //printf("\nja NJumps = %d\n", (*NJumps));
                }
                /*printf("arr_jumps[%d].name = %s "
                       "arr_jumps[%d].address = %d\n",
                       *NJumps, arr_jumps[*NJumps].name, *NJumps , arr_jumps[*NJumps].address);*/
                //len += strlen (cur_jump);
                len += sizeof(int);

                break;
            }
            case (JAE):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                len += sizeof(int);

                break;
            }
            case (JB):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                /*printf("arr_jumps[%d].name = %s "
                       "arr_jumps[%d].address = %d\n",
                       *NJumps, arr_jumps[*NJumps].name, *NJumps , arr_jumps[*NJumps].address);*/

                len += sizeof(int);

                break;
            }
            case (JBE):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                len += sizeof(int);

                break;
            }
            case (JE):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                len += sizeof(int);

                break;
            }
            case (JNE):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                len += sizeof(int);

                break;
            }
            case (JMP):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                len += sizeof(int);

                break;
            }
            case (JUMP_VAR):
            {
                //len--;
                fscanf (InputFile, "%s", cur_jump);
                cur_jump [strlen (cur_jump) - 1] = '\0'; //printf("strlen = %d", strlen (cur_jump));

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                for (int i = 0; i <= *NJumps; i++)
                    if ( _stricmp (arr_jumps[i].name, cur_jump) == 0 )
                        arr_jumps[i].address = --len;

                /*printf("arr_jumps[%d].name = %s "
                       "arr_jumps[%d].address = %d\n",
                       *NJumps, arr_jumps[*NJumps].name, *NJumps , arr_jumps[*NJumps].address);*/

                //len += strlen (cur_jump);

                break;
            }
            case (CALL):
            {
                fscanf (InputFile, "%s", cur_jump);

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                len += sizeof(int);

                break;
            }
            case (RET):
                break;
            case (FUNC_VAR):
            {
                fscanf (InputFile, "%s", cur_jump);

                cur_jump [strlen (cur_jump) - 1] = '\0';

                if (! in (cur_jump, arr_jumps, *NJumps + 1) )
                    strcpy (arr_jumps[++(*NJumps)].name, cur_jump);

                for (int i = 0; i <= *NJumps; i++)
                    if ( _stricmp (arr_jumps[i].name, cur_jump) == 0 )
                        arr_jumps[i].address = --len;

                break;
            }
            default:
                printf ("\n" "ERROR in (%s): Wrong command '%d' in file '%s'" "\n", __FUNC__, cur_cmd, InputFile);
                //fclose (InputFile);
                return INT_ERROR;
        }
    }

    (*NJumps)++;

    rewind (InputFile);
    printf("\n" "Size of MachineCode = %d", len);
    printf ("\nNumber of jumps = %d\n", *NJumps);
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

    printf ("\n|<%s>|\n\n", buffer);

    return buffer;
}

FILE* FileOpen (const char* FilePath, const char* FOpenMode)
{
    /*
    printf ("Input file path: ");
    scanf ("%s", FilePath);
    printf ("Input file open mode: ");
    scanf ("%s", FOpenMode);
    */

    FILE *InputFile = fopen (FilePath, FOpenMode);
    if (InputFile == NULL)
    {
        printf ("\n" "ERROR: Could not find file '%s', "
                     "please restart the program" "\n", FilePath);
        return NULL;
    }
    else return InputFile;
}

void help_function()
{
    printf ("\n" "Help" "\n");
}
