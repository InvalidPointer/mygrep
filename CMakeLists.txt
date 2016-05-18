cmake_minimum_required(VERSION 3.5)
project(mygrep)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES LexicalAnalyzer.cpp LexicalAnalyzer.h SyntaxAnalyzer.cpp SyntaxAnalyzer.h Regexp.cpp Regexp.h RegexpChecker.cpp RegexpChecker.h)
add_executable(mygrep ${SOURCE_FILES} main.cpp)
add_executable(tester ${SOURCE_FILES} tester.cpp)
