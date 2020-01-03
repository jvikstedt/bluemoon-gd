#pragma once

#include <stdio.h>

void client_printf(const char * format, ...);
void client_set_printf_function(int (*function)(const char * /*format*/, ...));
