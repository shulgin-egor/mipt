#include <stdio.h>
#include <string.h>
#include "Commands.cpp"
//#include "Commands.cpp"

#define ProgramName "factorial"
//#define ProgramName "factorial"

/*
#define DEF_CMD(name, num)                  \
    if (stricmp (str, #name) == 0)          \
        fprintf (out, "%d", cmd_##name)     \
    else

#include "CmdList.cpp"
*/

//#define STANDART_PROG_NAME "program.in"
//#define STANDART_BINARY_NAME "binary.myexe"

const int MaxCmdName = 15;

void help_function();
bool asm_function (const char* ProgFName, const char* BinaryFName);
FILE* FileOpen (const char* FilePath, const char* FOpenMode);

int main (const int argc, char* argv[])
{
    printf ("# Assembler program by Shulgin E." "\n");
    //char* ProgFName = STANDART_PROG_NAME, BinaryFName = STANDART_BINARY_NAME;

    char* ProgFName = ProgramName;                 // Standard
    char* BinaryFName = "binary.myexe";             // names

    if (argc == 1) return asm_function (ProgFName, BinaryFName);

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

    return asm_function (ProgFName, BinaryFName);
}

void help_function()
{
    printf ("\n" "Help" "\n");
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
    //char* cur_str;
    /*
    while (true)
    {
        if (fscanf (ProgramFile, "%s", cur_str) == EOF)
        {
            printf("EOF");
            break;
        }
        printf ("<%s>", cur_str);
    }
    */

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
