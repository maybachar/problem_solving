cmake_minimum_required(VERSION 3.15)
project(problem_solving)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS-pthread)

add_executable(problem_solving main.cpp CacheManager.h ClientHandler.h FileCacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.h Server.h Solver.h StringReverser.cpp StringReverser.h MyClientHandler.h Point.cpp Point.h Matrix.cpp Matrix.h Searchable.h State.h SearcherToSolver.h SearcherToSolver.cpp Searcher.h)
target_link_libraries(${PROJECT_NAME} pthread)