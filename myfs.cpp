#include "myfs.h"
#include <cstdio>
#include "cstring"

Filesystem FS{};

size_t find_empty_chunk() {
    for (int i = 0; i < CHUNKS_CAP; ++i) {
        if (FS.chunks[i].name[0] == '\0') {
            return i;
        }
    }
    fprintf(stderr, "No empty chunks\n");
    return ERR;
}

size_t find_first_chunk(const char *file_path) {
    for (int i = 0; i < CHUNKS_CAP; ++i) {
        if (strcmp(FS.chunks[i].name, file_path) == 0) {
            return i;
        }
    }
    fprintf(stderr, "File {%s} not found\n", file_path);
    return ERR;
}

size_t create_file(const char *file_path, char *src, size_t size) {

    if (size == 0)
        return LIST_END;

    size_t chunk_id = find_empty_chunk();

    if (chunk_id == ERR) {
        return LIST_END;
    }

    size_t to_write = size > CHUNK_DATA_CAP ? CHUNK_DATA_CAP : size;

    memcpy(FS.chunks[chunk_id].data, src, to_write);

    memcpy(FS.chunks[chunk_id].name, file_path, CHUNK_NAME_CAP);
    FS.chunks[chunk_id].name[CHUNK_NAME_CAP - 1] = '\0';

    FS.chunks[chunk_id].size = to_write;
    src += to_write;
    size -= to_write;

    FS.chunks[chunk_id].next = create_file(file_path, src, size);

    return chunk_id;
}

void view_file(const char *file_path) {
    size_t chunk_id = find_first_chunk(file_path);

    if (chunk_id == ERR)
        return;

    while (chunk_id != LIST_END) {
        size_t s = FS.chunks[chunk_id].size;
        fwrite(FS.chunks[chunk_id].data, sizeof(FS.chunks[chunk_id].data[0]), s, stdout);
        chunk_id = FS.chunks[chunk_id].next;
        fflush(stdout);
    }
}

void remove_file(const char *file_path) {

    size_t chunk_id = find_first_chunk(file_path);

    if (chunk_id == ERR)
        return;

    while (chunk_id != LIST_END) {
        FS.chunks[chunk_id].name[0] = '\0';
        chunk_id = FS.chunks[chunk_id].next;
    }
}

void copy_file(const char *file_path_dst, const char *file_path_src) {
    size_t ext_chunk_id = find_first_chunk(file_path_src);
    size_t new_chunk_id = find_empty_chunk();

    if (ext_chunk_id == ERR)
        return;

    while (true) {
        if (new_chunk_id == ERR) {
            break;
        }


        memcpy(&FS.chunks[new_chunk_id], &FS.chunks[ext_chunk_id], sizeof(Chunk));

        memcpy(FS.chunks[new_chunk_id].name, file_path_dst, CHUNK_NAME_CAP);
        FS.chunks[new_chunk_id].name[CHUNK_NAME_CAP - 1] = '\0';

        size_t new_next = find_empty_chunk();
        if (FS.chunks[ext_chunk_id].next == LIST_END || new_next == ERR) {
            new_next = LIST_END;
            break;
        } else {
            FS.chunks[new_chunk_id].next = new_next;
            new_chunk_id = new_next;
            ext_chunk_id = FS.chunks[ext_chunk_id].next;
        }
    }
}

void move_file(const char *file_path_dst, const char *file_path_src) {
    size_t chunk_id = find_first_chunk(file_path_src);

    if (chunk_id == ERR)
        return;

    while (chunk_id != LIST_END) {
        memcpy(FS.chunks[chunk_id].name, file_path_dst, CHUNK_NAME_CAP);
        FS.chunks[chunk_id].name[CHUNK_NAME_CAP - 1] = '\0';
        chunk_id = FS.chunks[chunk_id].next;
    }
}

void print_files() {
    for (int i = 0; i < CHUNKS_CAP; ++i) {
        if (FS.chunks[i].next == LIST_END && FS.chunks[i].name[0] != '\0') {
            printf("%s\n", FS.chunks[i].name);
        }
    }
}

void dump_fs(const char *bin_path) {
    FILE *out = fopen(bin_path, "wb");
    if (!out) {
        fprintf(stderr, "Cannot dump filesystem\n");
        return;
    }

    fwrite(FS.chunks, sizeof(Chunk), CHUNKS_CAP, out);
    fclose(out);
}