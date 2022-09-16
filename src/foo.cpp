#include <foo/foo.h>

int FooVersion()
{
    return 1 << 16 | 0;
}

const char* FooVersionString()
{
    return "0.1.0";
}
