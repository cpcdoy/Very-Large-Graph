g++ caveman.cc graph.cc -o caveman
cp -rf caveman louvain/
cd louvain
make
./caveman 1000 180 3 170 20 results.txt
