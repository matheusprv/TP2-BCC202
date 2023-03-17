#include <stdbool.h>

#define DISK_SIZE 128
#define NUM_INTERRUPTIONS 10
#define INTERRUPTION_PROBABILITY 5
#define NUM_INSTRUCTIONS 200
#define WORDS_SIZE 4
#define INVALID_ADD -1
#define COST_ACCESS_L1 1
#define COST_ACCESS_L2 10
#define COST_ACCESS_L3 100
#define COST_ACCESS_RAM 1000
#define COST_ACCESS_DISK 10000
// #define PRINT_INTERMEDIATE_RAM
// #define PRINT_LOG

//#define MAPEAMENTO_DIRETO
#define MAPEAMENTO_ASSOCIATIVO
//#define MAPEAMENTO_ASSOCIATIVO_POR_CONJUNTO

#if defined MAPEAMENTO_ASSOCIATIVO || defined MAPEAMENTO_ASSOCIATIVO_POR_CONJUNTO
    
    //LRU nao funconando para a RAM

    //#define LFU
    //#define LRU
    //#define FIFO
    #define RANDOM

#endif

//#define CAN_BE_IMPROVED 


/*
gcc -Wall *.c -o exe -lm; valgrind --leak-check=full -s ./exe random 32 4 8 10
*/