g++ caveman.cc graph.cc -o caveman
cp -rf caveman louvain/
cd louvain
make
./caveman 1000 50 3 3 20 results.txt
