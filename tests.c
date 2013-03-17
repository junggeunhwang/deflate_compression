#include "tests.h"

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "deflate.h"
#include "reader.h"
#include "cyclic_queue.h"

/* reader */
void test_init_reader()
{
	reader_t *reader;
	init_reader(&reader);
	assert(reader->output != NULL);
	assert(reader->isfinal == false);
	assert(reader->compress_type == ERROR_C);
	assert(reader->input != NULL);
	assert(reader->read_b != 0);
	assert(reader->read_i == 0);
	delete_reader(&reader);
	assert(reader == NULL);
	printf("OK\n");
}

void test_read_header()
{
	reader_t *reader;
	init_reader(&reader);
	read_block_header(reader);
	assert(reader->compress_type != ERROR_C);
	assert(reader->read_i == 3);
	delete_reader(&reader);
	printf("OK\n");
}

void test_is_in_huffman_code()
{
	reader_t *reader;
	init_reader(&reader);
	assert(is_in_huffman_code(51, 0) == true);
	assert(is_in_huffman_code(403, 1) == true);
	assert(is_in_huffman_code(5, 2) == true);
	assert(is_in_huffman_code(195, 3) == true);
	assert(is_in_huffman_code(52, 3) == false);
	assert(is_in_huffman_code(405, 0) == false);
	assert(is_in_huffman_code(191, 0) == true);
	assert(is_in_huffman_code(511, 1) == true);
	assert(is_in_huffman_code(23, 2) == true);
	assert(is_in_huffman_code(199, 3) == true);
	printf("OK\n");
}

void test_decode_next_litlen()
{
	reader_t *reader;
	init_reader(&reader);
	read_block_header(reader);
	delete_reader(&reader);
	printf("OK\n");
}

/* cyclic_queue */

void test_get_cyclic_queue()
{
	int s = 7;
	cyclic_queue *cq = new_cyclic_queue(s);
	add_cyclic_queue(cq, 'D');
	add_cyclic_queue(cq, 'e');
	add_cyclic_queue(cq, 'f');
	add_cyclic_queue(cq, 'l');
	add_cyclic_queue(cq, 'a');
	add_cyclic_queue(cq, 't');
	add_cyclic_queue(cq, 'e');
	print_cyclic_queue(cq);
	byte bytes[s];
	int len = 1;
	int off = 1;
	get_cyclic_queue(cq, bytes, len, off);
	int i = 0;
	for (i = 0; i < len; i++) {
		printf("%c, ", bytes[i]);
	}
	printf("\n");
}

/* inflate */

/* static_inflate */

/* dynamic_inflate */
void test_huffman_codes()
{
	size_t size = 8;
	huffman_code huff_code[] = {
		{3, 0},
		{3, 0},
		{3, 0},
		{3, 0},
		{3, 0},
		{2, 0},
		{4, 0},
		{4, 0}
	};

	build_huffman_codes(huff_code, size);
	assert(huff_code[0].code == 2);
	assert(huff_code[1].code == 3);
	assert(huff_code[5].code == 0);
	assert(huff_code[7].code == 15);
	printf("OK\n");
}
