#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/pci.h"

int main()
{
    int ret = 0;

    printf("Hello World\n");
    scanPciBus();
    return ret;
}

