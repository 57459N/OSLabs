#include <iostream>

#define CHUNK_NAME_CAP 64
#define CHUNK_DATA_CAP 128
#define CHUNKS_CAP 128

#define LIST_END (-1)

typedef struct Chunk {
    size_t prepad = 0xAAAAAAAAAAAAAAAA;
    char name[CHUNK_NAME_CAP]{};
    char data[CHUNK_DATA_CAP]{};
    size_t size{};
    size_t next{};
    size_t postpad = 0xBBBBBBBBBBBBBBBB;
} Chunk;

typedef struct {
    Chunk chinks[CHUNKS_CAP];
} Filesystem;

Filesystem FS{};

size_t find_empty_block(){
    for (int i = 0; i < CHUNKS_CAP; ++i) {
        if (FS.chinks[i].name[0] == '\0'){
            return i;
        }
    }

    return -1;
}

void create_file(const char* file_path, char* src, size_t size){

}

void remove_file(const char* file_path){

}

void copy_file(const char* file_path_dst, const char* file_path_src){

}

void move_file(const char file_path_dst, const char* file_path_src){

}

void view_file(const char* file_path){

}

void print_files(){

}



int main() {
    system("ls -l");
    return 0;
}
