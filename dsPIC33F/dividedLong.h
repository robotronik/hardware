#ifndef DIVIDEDLONG_H
#define DIVIDEDLONG_H

// Structure associant 2 shorts dans un long pour les QEI
typedef union {
    long all;
    struct {
        short low;
        short high;
    } part;
} T_dividedLong;


#endif