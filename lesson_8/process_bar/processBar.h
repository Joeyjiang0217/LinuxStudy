#pragma once

#include <stdio.h>
#include <unistd.h>

#define NUM 102
#define TOP 100
#define BODY '='
#define RIGHT '>'
#define GREEN "\033[0;32;32m"
#define NONE "\033[m"

extern void processbar();
extern void init_bar();

