#include "throwError.h"

#include "Exception.h"
#include "stacktrace.h"

#include <stdio.h>

void throwError(const char *msg)
{
print_stacktrace(stdout);
throw new Exception(NULL,msg);

}
