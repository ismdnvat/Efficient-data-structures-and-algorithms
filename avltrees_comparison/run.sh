#!/bin/bash

rm -r build
mkdir build
cd build

cmake ..
make

if [ $? -ne 0 ]; then
    echo "Сборка завершилась с ошибкой."
    exit 1
fi
cd bin

./avltree_mm

./avltree_new_delete

cd ../../graph

python3 graph.py ../build/bin/timer_for_graph.txt ../build/bin/timer_for_graph_new_delete.txt



