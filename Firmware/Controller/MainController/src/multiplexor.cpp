#include "multiplexor.h"
#include "Pin_Defines.h"
#include "mbed.h"

DigitalIn multo1(MULTO1);
DigitalIn multo2(MULTO2);
DigitalOut multa(MULTA);
DigitalOut multb(MULTB);


bool read_CVMSIG1(void)
{
    multa = 0;
    multb = 0;
    return(multo1);
}

bool read_CVMSIG2(void)
{
    multa = 1;
    multb = 0;
    return(multo1);
}

bool read_CVMSIG3(void)
{
    multa = 0;
    multb = 1;
    return(multo1);
}

bool read_CVMSIG4(void)
{
    multa = 1;
    multb = 1;
    return(multo1);
}

bool read_H2_OK(void)
{
    multa = 0;
    multb = 0;
    return(multo2);
}

bool read_EXTRA_SIG(void)
{
    multa = 1;
    multb = 0;
    return(multo2);
}

bool read_M_SIG_1(void)
{
    multa = 0;
    multb = 1;
    return(multo2);
}

bool read_M_SIG_2(void)
{
    multa = 1;
    multb = 1;
    return(multo2);
}
