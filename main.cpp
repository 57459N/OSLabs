#include "myfs.h"
#include "cstdio"

int main() {
    create_file("hello.txt", "asd", 3);
    view_file("hello.txt");
    printf("\n");
    create_file("big.txt", "1234567890qwertyuiopasdfghjklpp\nxc", 34);
    view_file("big.txt");
    copy_file("big_copy.txt", "big.txt");
    dump_fs("test.fs");

    remove_file("big.txt");
    printf("\n");
    view_file("big_copy.txt");
    dump_fs("test.fs");

    printf("\n");
    print_files();
    move_file("big_copy_moved.txt", "big_copy.txt");
    printf("\n");
    print_files();
    view_file("big_copy_moved.txt");
    dump_fs("test.fs");

    return 0;
}
