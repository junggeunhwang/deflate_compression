#ifndef READER_H
#define READER_H
#include <stdio.h>
#include <stdbool.h>
#include "deflate.h"

typedef enum {NO_C, STATIC_C, DYNAMIC_C, ERROR_C} compress_t;

typedef struct _reader_t {
	char *input_name;
	FILE *input;
	FILE *output;
	byte read_b;
	byte read_i;
	bool isfinal;
	compress_t compress_type;
} reader_t;

void init_reader(reader_t **reader);
void delete_reader(reader_t **reader);
void read_block_header(reader_t *reader);
two_bytes decode_next_litlen(reader_t *reader);
two_bytes decode_length(reader_t *reader, two_bytes lencode);
two_bytes decode_distance(reader_t *reader);
void read_next_bit(reader_t *reader);
void read_next_byte(reader_t *reader);
bool is_in_huffman_code(two_bytes code, int index);

#endif
