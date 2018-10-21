#! /bin/bash

if [[ "$1" == "cpp" ]]
then
    g++ -O3 ./main.cpp -o ./bin/main
    time ./bin/main $2
elif [[ "$1" == "py" ]]
then
    time ./main.py $2
else
    echo "Invalid parameters!
Usage: ./run.sh [py | cpp] n
Where n is the number of frogs looking in one direction."
fi