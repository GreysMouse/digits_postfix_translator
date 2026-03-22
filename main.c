#include "include/stack.h"
#include "include/stream.h"
#include "include/translator.h"
#include "macro/exceptions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *input, *output = stdout;

    long input_size;
    char *buffer;

    if (argc < 2) {
        NO_INPUT_FILE_ERR(argv[0]);
    }

    input = open_file(argv[1], "r");
    input_size = file_size(argv[1], input);
    buffer = malloc(sizeof(char) * (input_size + 1));

    if (!buffer) {
        NO_OUTPUT_MEMORY_ERR();
    }

    stack result = {buffer, 0, input_size};

    translate(input, &result);
    fclose(input);

    if (argv[2]) {
        output = open_file(argv[2], "w");
    }

    fprintf(output, "%s\n", buffer);
    free(buffer);

    return EXIT_SUCCESS;
}