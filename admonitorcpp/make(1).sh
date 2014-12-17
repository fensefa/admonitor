g++ -c jsoncompute.cpp -I/home/w/include -L/home/w/lib64 -ljsoncpp
g++ merge.cpp jsoncompute.cpp -I/home/w/include -L/home/w/lib64 -ljsoncpp -o merge.out
g++   add.cpp jsoncompute.cpp -I/home/w/include -L/home/w/lib64 -ljsoncpp -o   add.out
g++ composite.cpp jsoncompute.cpp -I/home/w/include -L/home/w/lib64 -ljsoncpp -o composite.out
