cmake_minimum_required(VERSION 3.23)
project(OSLabs5)

set(CMAKE_CXX_STANDARD 23)

# BOOST LEXICAL CAST
add_library(boost_lexical_cast INTERFACE)
add_library(Boost::lexical_cast ALIAS boost_lexical_cast)

target_include_directories(boost_lexical_cast INTERFACE include)

target_link_libraries(boost_lexical_cast
        INTERFACE
        Boost::config
        Boost::container
        Boost::core
        Boost::integer
        Boost::numeric_conversion
        Boost::throw_exception
        Boost::type_traits
)


# BOOST PREPROCESSOR
add_library(boost_preprocessor INTERFACE)
add_library(Boost::preprocessor ALIAS boost_preprocessor)

target_include_directories(boost_preprocessor INTERFACE include)

add_executable(OSLabs5 main.cpp
        myfs.h
        myfs.cpp)

add_executable(commands_test repl.cpp command_interpreter.hpp)