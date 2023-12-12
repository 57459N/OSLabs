#ifndef OSLABS5_MYFS_H
#define OSLABS5_MYFS_H

#include <cstdlib>

#define CHUNK_NAME_CAP 64
#define CHUNK_DATA_CAP 32
#define CHUNKS_CAP 128

#define ERR (CHUNKS_CAP + 1)
#define LIST_END (CHUNKS_CAP + 1)


typedef struct Chunk {
    size_t prepad = 0xAAAAAAAAAAAAAAAA;
    char name[CHUNK_NAME_CAP]{};
    char data[CHUNK_DATA_CAP]{};
    size_t size{};
    size_t next{};
    size_t postpad = 0xBBBBBBBBBBBBBBBB;
} Chunk;

typedef struct {
    Chunk chunks[CHUNKS_CAP];
} Filesystem;

extern Filesystem FS;

size_t find_empty_chunk();

size_t find_first_chunk(const char *file_path);

size_t create_file(char const *file_path, char const *src, size_t size);

void view_file(const char *file_path);

void remove_file(const char *file_path);

void copy_file(const char *file_path_dst, const char *file_path_src);

void move_file(const char *file_path_dst, const char *file_path_src);

void print_files();

void dump_fs(const char *bin_path);

void load_fs(const char *bin_path);

#endif //OSLABS5_MYFS_H
