g++ -pthread caveman.cc graph.cc -o caveman
cp -rf caveman louvain/
cd louvain
make
./caveman 1000 1200 3 1000 20 results.txt
