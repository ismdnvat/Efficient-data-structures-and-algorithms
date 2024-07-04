#!/bin/bash

rm -r build
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release ..
make

if [ $? -ne 0 ]; then
    echo "Сборка завершилась с ошибкой."
    exit 1
fi

cd bin

./generate_data
./avltree_test
./binsearch_test
./hash_test

./generate_data 100000
./avltree_test 100000
./binsearch_test 100000
./hash_test 100000

./generate_data 500000
./avltree_test 500000
./binsearch_test 500000
./hash_test 500000

./generate_data 1000000
./avltree_test 1000000
./binsearch_test 1000000
./hash_test 1000000

cd ../../graph

python3 graph.py

python3 graph_removing.py
