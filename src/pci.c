#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include "../inc/pci.h"
#include "../inc/vendor.h"

void getPciDev(uint16_t *venId, uint16_t *devId, uint8_t u8BusNum, uint8_t u8DevNum, uint8_t u8FuncNum)
{
    uint32_t addr;
    uint32_t data;

    addr = MK_PCICFGADDR(u8BusNum, u8DevNum, u8FuncNum);

    outpd(PCI_CONFIG_ADDRESS, addr);
    data = inpd(PCI_CONFIG_DATA);

    *venId = (data & VENDOR_ID_MASK);
    *devId = (data & DEVICE_ID_MASK) >> 16;
}

uint8_t scanPciBus(void)
{
    uint16_t bus = 0;
    uint16_t dev = 0;
    uint16_t func = 0;
    uint16_t venId = 0;
    uint16_t devId = 0;

    uint8_t rc = 0;

    for (bus = 0; bus <= PCI_BUS_MAX; ++bus)
    {
        for (dev = 0; dev <= PCI_DEVICE_MAX; ++dev)
        {
            for (func = 0; func <= PCI_FUNCTION_MAX; ++func)
            {
//                #ifdef DEBUG
                getPciDev(&venId, &devId, bus, dev, func);
                if(venId == PMC_VENDOR_ID || venId == INTEL_VENDOR_ID)
                    printf("%s:%03d:%03d:%03d - vendor %04x device %04x\n", __FUNCTION__, bus, dev, func, venId, devId);
//                #endif // !DEBUG

            } // !func
        } // !dev
    } // !bus

    return rc;
}
