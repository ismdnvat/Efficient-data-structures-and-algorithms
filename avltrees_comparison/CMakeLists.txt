cmake_minimum_required(VERSION 3.5)
project(avltrees_comparison)

add_executable(avltree_mm avltree_mm/avltree_test.cpp avltree_mm/avltree.h avltree_mm/mm.h)
add_executable(avltree_new_delete avltree_new_delete/avltree_new_delete_test.cpp avltree_new_delete/avl_new_delete.h)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_custom_target(run_all
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/avltree_mm
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/avltree_new_delete
        COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/graph/graph.py
        ${CMAKE_CURRENT_BINARY_DIR}/timer_for_graph.txt
        ${CMAKE_CURRENT_BINARY_DIR}/timer_for_graph_new_delete.txt
        DEPENDS avltree_mm avltree_new_delete
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)


add_custom_target(avltree_comparison DEPENDS run_all)