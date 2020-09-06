#include "slip.h"

/* definitions of the special SLIP characters */
#define SLIP_END			(unsigned char)(0xC0)
#define SLIP_ESC			(unsigned char)(0xDB)
#define SLIP_ESC_END		(unsigned char)(0xDC)
#define SLIP_ESC_ESC		(unsigned char)(0xDD)

int slip(unsigned char * inbuff, unsigned char * outbuff, int length, int maxlength)
{
    if (length < 1)
        return -1;

    int outlength = 0;
    int i = 0;

    for (i = 0; i < length; i++)
    {
        if (inbuff[i] == SLIP_END)
        {
            outbuff[outlength] = SLIP_ESC;
            outlength++;
            if (outlength > maxlength)
                return -1;
            outbuff[outlength] = SLIP_ESC_END;
        }
        else if (inbuff[i] == SLIP_ESC)
        {
            outbuff[outlength] = SLIP_ESC;
            outlength++;
            if (outlength > maxlength)
                return -1;
            outbuff[outlength] = SLIP_ESC_ESC;
        }
        else
        {
            outbuff[outlength] = inbuff[i];
        }
        outlength++;
        if (outlength > maxlength)
            return -1;
    }
    outbuff[outlength] = SLIP_END;
    outlength++;
    return outlength;
}

int unslip(unsigned char * inbuff, unsigned char * outbuff, int maxlength)
{
    if (maxlength < 1)
        return -1; /* incorrect parameter */

    int outlength = 0;
    int i = 0;
    do
    {
        if (inbuff[i] == SLIP_ESC)
        {
            if (inbuff[i + 1] == SLIP_ESC_END)
            {
                outbuff[outlength] = SLIP_END;
                i++;
            }
            else if (inbuff[i + 1] == SLIP_ESC_ESC)
            {
                outbuff[outlength] = SLIP_ESC;
                i++;
            }
        }
        else if (inbuff[i] == SLIP_END)
            return outlength;
        else
            outbuff[outlength] = inbuff[i];

        outlength++;
        i++;
    } while (i < maxlength);

    return -2; /* SLIP_END not found in inbuff */
}
