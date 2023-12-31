project(tmp)
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${PROJECT_SOURCE_DIR}/turing-project)

aux_source_directory(${PROJECT_SOURCE_DIR}/turing-project CPP_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(turing ${CPP_SRC}
        turing-project/parser.cpp
        turing-project/ConfigCtx.cpp
        turing-project/ConfigCtx.h
        turing-project/MoveRule.cpp
        turing-project/MoveRule.h
        turing-project/parser.h
        turing-project/executor.cpp
        turing-project/TmCtx.cpp
        turing-project/TmCtx.h
        turing-project/TMTape.cpp
        turing-project/TMTape.h
        turing-project/executor.h)

