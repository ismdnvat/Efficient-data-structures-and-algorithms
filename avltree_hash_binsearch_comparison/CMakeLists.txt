cmake_minimum_required(VERSION 3.5)
project(avltree_hash_binsearch_comparison)

add_executable(generate_data generate_data.cpp)

add_executable(avltree_test avltree_test/avltree.h avltree_test/test_avltree.cpp memory_manager/mm.h)
add_executable(hash_test hash_test/hash.h hash_test/test_hash.cpp memory_manager/mm.h)
add_executable(binsearch_test binsearch_test/sort.h binsearch_test/test_binsearch.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)