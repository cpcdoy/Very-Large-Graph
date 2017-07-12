g++ caveman.cc graph.cc -o caveman
cp -rf caveman louvain/
cd louvain
make
./caveman 1000 200 100 100 100 results.txt
