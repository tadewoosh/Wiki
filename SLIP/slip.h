/*
 * SLIP - Serial Line Internet Protocol
 * Author: Tadeusz Kaluba
 * This library contains definitions and functions for SLIP  protocol
 */

#ifndef SLIP_H
#define SLIP_H

/* definitions of the special SLIP characters */
#define SLIP_END			(unsigned char)(0xC0)
#define SLIP_ESC			(unsigned char)(0xDB)
#define SLIP_ESC_END		(unsigned char)(0xDC)
#define SLIP_ESC_ESC		(unsigned char)(0xDD)

/*
 * The Function for SLIPping data - it  takes the data frame from the
 * inbuff with length converts the characters according to SLIP protocol
 * and stores the SLIPped result in outbuff.
 * It returns the frame length in outbuff..
 */
int slip(unsigned char * inbuff, unsigned char * outbuff, int length, int maxlength);

/*
 * The Function for un-SLIPping data - it  takes the data frame from the
 * inbuff with length recovers the characters according to SLIP protocol
 * and stores the unSLIPped result in outbuff.
 * It returns the frame length in outbuff.
 */
int unslip(unsigned char * inbuff, unsigned char * outbuff, int maxlength);

#endif
