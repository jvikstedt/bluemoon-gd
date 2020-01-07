#include <stdarg.h>
#include "logger.hpp"

static int (*client_printf_function)(const char* format, ...) = printf;
void client_set_printf_function(int (*function)(const char* format, ...)) {
  client_printf_function = function;
}

void client_printf(const char* format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[4*1024];
  vsprintf(buffer, format, args);
  client_printf_function("%s", buffer);
  va_end(args);
}
