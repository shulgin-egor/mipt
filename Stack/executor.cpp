#include "Processor.cpp"
#include "Commands.cpp"
#include <stdlib.h>
#include <string.h>
//#include "Assembler.cpp"

#define INT_ERROR -1
#define PTR_ERROR NULL

#define FileName "binary.myexe"

//const int MaxFuncName = 20;
const int MaxJumpName = 15;
const int MaxNJumps = 20;
const int MaxRetAdr= 100;
const int MaxFileName = 30;

//const char FileName [MaxFileName] = "binary.myexe";

typedef struct
{
    char name [MaxJumpName];
    int address;
} jump_t;


//char* MakeMachineCode (long long* CodeSize, jump_t arr_jumps[], int* NJumps);

char* DownloadMachineCode (long long* CodeSize, jump_t arr_jumps[], int* NJumps);

bool ExecuteCode (const char* MachineCode, jump_t arr_jumps[], const int* NJumps, const long long CodeSize);

void MachineCode_Dump (const char* MachineCode, long long CodeSize, jump_t arr_jumps[], const int NJumps);

bool in (const char cur_jump[], jump_t arr_jumps[], const int NJumps);

FILE* FileOpen (const char* FilePath, const char* FOpenMode);
//long long FileLength (FILE* InputFile, jump_t arr_jumps[], int* NJumps);
char* FileBuffer (FILE *InputFile, const long long FileLength);


int main()
{
    printf ("# Executor program by Shulgin E." "\n");

    long long CodeSize = 0;
    jump_t arr_jumps [MaxNJumps] = {};
    int NJumps = 0;

    //char* MachineCode = MakeMachineCode (&CodeSize, arr_jumps, &NJumps);
    //if (MachineCode == NULL) return 0;

    char* MachineCode = DownloadMachineCode (&CodeSize, arr_jumps, &NJumps);
    if (MachineCode == NULL) return 0;

    /*printf ("\n******\n");
    printf ("NJumps = %d\n", NJumps);
    printf ("CodeSize = %d\n", CodeSize);
    printf ("******\n"); */

    //MachineCode_Dump (MachineCode, CodeSize, arr_jumps, NJumps);

    ExecuteCode (MachineCode, arr_jumps, &NJumps, CodeSize);

    return 1;
}


/*char* MakeMachineCode (long long* CodeSize, jump_t arr_jumps[], int* NJumps)
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
                //printf("*");
                buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%c", &buffer[index++]);
                //char ch;
                //fscanf (BinaryFile, "%c", &ch);
                //buffer[index++] = ch;
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
                //buffer[index++] = cur_cmd;
                fscanf (BinaryFile, "%s", cur_jump);
                //index++;
                break;
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

    //printf("\n<%c>", buffer[1]);
    //printf("<%c>\n\n", buffer[3]);
    //printf("\n");

    //buffer[index] = cur_cmd;
    //for (int i = 0; i < *CodeSize; i++) printf ("%d ", buffer[i]);
    //printf("\n");
    //for (int i = 0; i < *CodeSize; i++) printf ("<%c> ", buffer[i]);
    fclose (BinaryFile);

    //printf ("\nFunction (MakeMachineCode) end\n");

    return buffer;
}*/

char* DownloadMachineCode (long long* CodeSize, jump_t arr_jumps[], int* NJumps)
{
    char BinaryFName[MaxFileName] = "binary";
    FILE* BinaryFile = FileOpen (BinaryFName, "r");
    if (BinaryFile == PTR_ERROR) return PTR_ERROR;

    int temp = 0;

    /*fscanf (BinaryFile, "%d\n", NJumps);

    int temp = 0;
    char cur_jump [MaxJumpName] = "\0";

    for (int i = 0; i < *NJumps; i++)
    {
        fscanf (BinaryFile, "%d ", &temp);
        arr_jumps[i].address = temp;

        fscanf (BinaryFile, "%s\n", cur_jump);
        strcpy (arr_jumps[i].name, cur_jump);
    }*/

    fscanf (BinaryFile, "%d\n", CodeSize);

    char* MachineCode = (char*) calloc (*CodeSize, sizeof(*MachineCode));

    for (int i = 0; i < *CodeSize; i++)
    {
        fscanf (BinaryFile, "%d ", &temp);
        MachineCode[i] = (char)temp;
    }

    return MachineCode;
}

void MachineCode_Dump (const char* MachineCode, long long CodeSize, jump_t arr_jumps[], const int NJumps)
{
    assert(MachineCode);

    printf ("\n" "--------------MachineCode_Dump start--------------" "\n");

    printf ("NJumps = %d\n", NJumps);

    for (int i = 0; i < NJumps; i++)
    {
        printf ("arr_jumps[%d].address = %d\n", i, arr_jumps[i].address);
        printf ("arr_jumps[%d].name = %s" "\n\n", i, arr_jumps[i].name);
    }

     printf ("CodeSize = %d\n", CodeSize);

    for (int i = 0; i < CodeSize; i++) printf ("%d ", MachineCode[i]);

    printf ("\n" "--------------MachineCode_Dump end----------------" "\n");
}

bool ExecuteCode (const char* MachineCode, jump_t arr_jumps[], const int* NJumps, const long long CodeSize)
{
    assert(MachineCode);

    if (CodeSize < 0)
    {
        printf ("\n" "ERROR in (%s): CodeSize = %d < 0" "\n", __FUNC__, NJumps);
        return false;
    }

    if (*NJumps < 0)
    {
        printf ("\n" "ERROR in (%s): Number of jumps and functions = %d < 0" "\n", __FUNC__, *NJumps);
        return false;
    }

    //MachineCode_Dump (MachineCode, CodeSize);

    //printf ("\nFunction (ExecuteCode)\n");

    cpu_t* cpu = cpu_constructor();

    //char register_name = '*';
    int index = -1, temp = 0, i = 0, cur_adr = -1;
    int ret_address [MaxRetAdr] = {};

    //printf("CodeSize = %d\n",CodeSize);
    //for (int i = 0; i < CodeSize; i++) printf ("%d ", MachineCode[i]); printf("\n");
    //printf ("<%c>", MachineCode[8]);

    //for (int j = 0; j < *NJumps; j++)
    //    printf ("\n~~~arr_jumps[%d].name = %s, \naddress = %d\n", j, arr_jumps[j].name, arr_jumps[j].address);

    while (++index < CodeSize)
    {
        //printf("%d-", MachineCode[index]);
        switch (MachineCode[index])
        {
            case (END):
                //cpu_dump (cpu);
                cpu_destructor (cpu);
                break;
            case (OUT):
                cpu_dump (cpu);
                break;
            case (PUSH_X):
                cpu_push (cpu, MachineCode[++index]);
                break;
            case (PUSH):
            {
                index++;
                stack_push (cpu->stack, *((STACK_TYPE*)(MachineCode + index)));
                index += sizeof(STACK_TYPE) - 1;
                break;
            }
            case (POP_X):
                cpu_pop (cpu, MachineCode[++index]);
                break;
            case (POP):
                stack_pop (cpu->stack);
                break;
            case (ADD):
                stack_add (cpu->stack);
                break;
            case (SUB):
                stack_sub (cpu->stack);
                break;
            case (MUL):
                stack_mul (cpu->stack);
                break;
            case (DIV):
                stack_div (cpu->stack);
                break;
            case (SQRT):
                stack_sqrt (cpu->stack);
                break;
            case (DUP):
                stack_dup (cpu->stack);
                break;
            case (IN):
                printf("Input ");
                scanf ("%d", &temp);
                stack_push (cpu->stack, temp);
                break;
            case (JA):
            {
                if (stack_pop (cpu->stack) > stack_pop (cpu->stack))
                {
                    index++;
                    index = *((int*)(MachineCode + index)) - 1;
                    //printf ("\nJA index = %d\n", index);
                }
                else index += sizeof(int);

                break;
            }
            case (JAE):
            {
                if (stack_pop (cpu->stack) >= stack_pop (cpu->stack))
                {
                    index++;
                    index = *((int*)(MachineCode + index)) - 1;
                    //printf ("\nJA index = %d\n", index);
                }
                else index += sizeof(int);

                break;
            }
            case (JB):
            {
                if (stack_pop (cpu->stack) < stack_pop (cpu->stack))
                {
                    index++;
                    index = *((int*)(MachineCode + index)) - 1;
                    //printf ("\nJB index = %d\n", index);
                }
                else index += sizeof(int);

                break;
            }
            case (JBE):
            {
                if (stack_pop (cpu->stack) <= stack_pop (cpu->stack))
                {
                    index++;
                    index = *((int*)(MachineCode + index)) - 1;
                    //printf ("\nJB index = %d\n", index);
                }
                else index += sizeof(int);

                break;
            }
            case (JE):
            {
                if (stack_pop (cpu->stack) == stack_pop (cpu->stack))
                {
                    index++;
                    index = *((int*)(MachineCode + index)) - 1;
                    //printf ("\nJB index = %d\n", index);
                }
                else index += sizeof(int);

                break;
            }
            case (JNE):
            {
                if (stack_pop (cpu->stack) != stack_pop (cpu->stack))
                {
                    index++;
                    index = *((int*)(MachineCode + index)) - 1;
                    //printf ("\nJB index = %d\n", index);
                }
                else index += sizeof(int);

                break;
            }
            case (JMP):
            {
                index++;
                index = *((int*)(MachineCode + index)) - 1;
                //printf ("\nJA index = %d\n", index);

                break;
            }
            case (CALL):
            {
                ret_address [++cur_adr] = index + sizeof(int) + 1;
                printf ("\nret address = %d\n", ret_address [cur_adr]); index++;

                index = *((int*)(MachineCode + index)) - 1;
                printf ("\ncall address = %d\n", index);

                break;
            }
            case (RET):
            {
                index = ret_address [cur_adr--] - 1;
                printf ("\nreturn address = %d\n", index);

                break;
            }
            default:
                printf ("\n" "ERROR: Wrong command '%d' in (%s) '%s'" "\n", MachineCode[index], __FUNC__);
                return false;
        }
    }

    return true;
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

    /*for (int i = 0; i < *NJumps; i++)
    {
        printf ("\n\n----arr_jumps[%d].address = %d", i, arr_jumps[i].address);
        printf ("\narr_jumps[%d].name = %s", i, arr_jumps[i].name);
    }*/

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

