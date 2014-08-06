/* 	
	-- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
 	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
	
	-- CONFIDENTIAL - SOURCE MATERIALS --

 */

#ifndef _CORE_ENCODING_H_
#define _CORE_ENCODING_H_


#include "common.h"

static int mod_table[] = {0, 2, 1};


/* base 64 encoding */
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};


char * base64_encode(char *data, size_t input_length, size_t *output_length);

#endif
