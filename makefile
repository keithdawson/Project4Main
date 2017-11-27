encode: main.o
    g++ -Wall -std=c++11 main.cpp -o encode

main.o: main.cpp
    gcc -Wall -c main.cpp

clean:
    rm -f *.o encode

test:   encode
    ./encode foo.txt