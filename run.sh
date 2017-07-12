g++ caveman.cc graph.cc -o caveman
cp -rf caveman louvain/
cd louvain
make
./caveman 1000 150 3 50 20 results.txt
