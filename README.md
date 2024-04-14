<h1 align="center">my assembly decoder</h1>

The program reads encoded instructions and outputs a mnemonic representation. The architecture assumes that we have 4 _8-bit_ registers: A, B, C, D and 7 commands.

Command encoding is represented in the table below:

| mnemonic | operands | encoding |
| :------: | :------: | :------: |
|   MOVI   |    I     | 0IIIIIII |
|   ADD    |  R1, R2  | 1000RRRR |
|   SUB    |  R1, R2  | 1001RRRR |
|   MUL    |  R1, R2  | 1010RRRR |
|   DIV    |  R1, R2  | 1011RRRR |
|    IN    |    R     | 110000RR |
|   OUT    |    R     | 110001RR |
| ILLEGAL  |          | 111111XX |

where:

1. operations:

- MOVI - move immediate to D register
- ADD - R1 = R1 + R2
- SUB - R1 = R1 - R2
- MUL - R1 = R1 \* R2
- DIV - R1 = R1 / R2
- IN - read from input
- OUT - output to screen

2. operands:

- R - register
- I - immediate number

3. encoding:

- I - immediate
- R - register
- XX - no matter

To compile with gcc and run:

```shell
gcc my_asm_decoder.c -o decoder
./decoder
```

To run test:

```shell
bash test.sh
```

The program was made by lectures by https://github.com/tilir/c-graduate
