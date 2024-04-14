#pragma once

enum reg_t
{
    A = 0,
    B,
    C,
    D,
};

enum opcode_t
{
    MOVI = 0b00000000,
    ADD = 0b00001000,
    SUB = 0b00001001,
    MUL = 0b00001010,
    DIV = 0b00001011,
    IN,
    OUT,
};

union operand_t
{
    struct
    {
        int rd, rs;
    } ops;
    int rop;
    int imm;
};

struct instr_t
{
    enum opcode_t opcode;
    union operand_t opnd;
};

struct reg_state_t
{
    unsigned char data;
    unsigned char init;
};