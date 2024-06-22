//使用chatGPT生成

#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SMAX 1000

extern char *tokens[SMAX];
extern int tokenTop, tokenIdx;

int isNext(char *set);
int isEnd();
char *next();
char *skip(char *set);
void parse();

#endif
