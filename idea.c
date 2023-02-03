// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 42
#endif

// A block size can be the size of 2048 or as large as BUFFER_SIZE
#if BUFFER_SIZE >= 2048
    // How many times of read(fd, *buf, BUFFER_SIZE) to fill one block
    #define READ_ROUND 1
    // How many bytes to malloc the buffer
    #define BLOCK_SIZE BUFFER_SIZE
#else
    #define READ_ROUND 2048 / BUFFER_SIZE
    #define BLOCK_SIZE READ_ROUND * BUFFER_SIZE
#endif

typedef struct s_block {
    char            blk[BLOCK_SIZE];
    struct s_block  *next;
}   t_block;

/*
* This means that the function's blocks max out at read BLOCK_SIZE x 2048 which
* is ~4.12MB/line at default BUFFER_SIZE of 42. You can achive bigger read size by
* increasing the BUFFER_SIZE.
*/

typedef struct s_file {
    // Blocks
    t_block *blocks;
    size_t  blk_len;
    // Env
    size_t  ptr;        // on what part of the block it's reading
    size_t  ln_len;     // readline's length
    int     fd;
    int     eof;
} t_file;

void    file_newblk (t_file *file)
{
    t_block *tmp;

    &file->blocks[file->blk_len] = malloc(
        BLOCK_SIZE);
    file->blk_len++;
}

void    file_shiftblk (t_file *file)
{
    t_block *tmp;

    tmp = &file->blocks[0];
    file->blocks[0] = *file->blocks[0].next;
    free(tmp);
    file->blk_len--;
}

void    file_readblk (t_file *file)
{
    file->blocks
}

int main() {

    return 0;
}
