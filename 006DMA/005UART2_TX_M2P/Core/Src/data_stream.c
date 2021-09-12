/*
 * data_stream.c
 *
 *  Created on: Aug 6, 2021
 *      Author: igor
 */

#include <stdint.h>

uint8_t data_stream[] = "This is a text\n"
		"this is a very important text\n"
		"this text is really cool\n"
		"this text has ended\n"
		"I hope you enjoyed it\n";

uint32_t data_len = sizeof(data_stream);
