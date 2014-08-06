/* 	
	-- CONFIDENTIAL - SOURCE MATERIALS --
                                                                                                                                                                                                        
 	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE.
	
	-- CONFIDENTIAL - SOURCE MATERIALS --

 */

#include "encoding.h"

char * 
base64_encode(char *data,
                    size_t input_length,
                    size_t *output_length) 
{
	int i, j;

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = malloc(*output_length);

    if (encoded_data == NULL) return NULL;

    for (i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}