enum Commands
 {
    END = 0,
    OUT = 1,

    PUSH_X = 2,
    PUSH = 22,
    POP_X = 3,
    POP = 33,

    ADD = 4,
    SUB = 5,
    MUL = 6,
    DIV = 7,
    SQRT = 8,
    DUP = 80,

    IN = 81,

    JA = 9,
    JAE = 91,
    JB = 10,
    JBE = 11,
    JE = 12,
    JNE = 13,
    JMP = 14,
    JUMP_VAR = 100,

    CALL = 101,
    RET = 102,
    FUNC_VAR = 103
 };
