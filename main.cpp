#include <iostream>
#include "myfs.h"
#include "command_interpreter.hpp"


class FSInterpreter : public CommandInterpreter {
public:
    static bool running;
private:
    static std::string _create_file(const std::string &file_path, const std::string &src) {
        create_file(file_path.data(), src.data(), src.length());
        return "";
    }

    static std::string _view_file(const std::string &file_path) {
        view_file(file_path.data());
        return "";
    }

    static std::string _remove_file(const std::string &file_path) {
        remove_file(file_path.data());
        return "";
    }

    static std::string _copy_file(const std::string &file_path_dst, const std::string &file_path_src) {
        copy_file(file_path_dst.data(), file_path_src.data());
        return "";
    }

    static std::string _move_file(const std::string &file_path_dst, const std::string &file_path_src) {
        move_file(file_path_dst.data(), file_path_src.data());
        return "";
    }

    static std::string _print_files() {
        print_files();
        return "";
    }

    static std::string _dump_fs(const std::string &bin_path) {
        dump_fs(bin_path.data());
        return "";
    }

    static std::string _load_fs(const std::string &bin_path) {
        load_fs(bin_path.data());
        return "";
    }

    static int exit(){
        exit();
    }

    void register_commands() override {
        register_command(_create_file, "create", "creates file with provided name");
        register_command(_view_file, "cat", "Show files content with provided name");
        register_command(_remove_file, "rm", "Remove file with provided name");
        register_command(_copy_file, "cp", "Copy {file_name_1} to {file_name_2}");
        register_command(_move_file, "mv", "Move {file_name_1} to {file_name_2{");
        register_command(_print_files, "ls", "Show list of files");
        register_command(_dump_fs, "dump", "Dump filesystem to file with provided name");
        register_command(_load_fs, "load", "Load filesystem to file with provided name");
        register_command(exit, "exit", "Exit the program");
    }
};

bool FSInterpreter::running = true;


int main() {
    FSInterpreter interpreter;
    std::string line;
    std::cout << ">>> ";

    while (std::getline(std::cin, line) && FSInterpreter::running) {
        interpreter.eval(line);
        dump_fs("main_dump.fs");
        std::cout << ">>> ";
    }
//    create_file("hello.txt", "asd", 3);
//    view_file("hello.txt");
//    printf("\n");
//    create_file("big.txt", "1234567890qwertyuiopasdfghjklpp\nxc", 34);
//    view_file("big.txt");
//    copy_file("big_copy.txt", "big.txt");
//    dump_fs("test.fs");
//
//    remove_file("big.txt");
//    printf("\n");
//    view_file("big_copy.txt");
//    dump_fs("test.fs");
//
//    printf("\n");
//    print_files();
//    move_file("big_copy_moved.txt", "big_copy.txt");
//    printf("\n");
//    print_files();
//    view_file("big_copy_moved.txt");
//    dump_fs("test.fs");



    return 0;
}
