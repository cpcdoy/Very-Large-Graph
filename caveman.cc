#include <iostream>
#include <unistd.h>
#include <chrono>

#include "graph.hh"

int main(int argc, char** argv)
{
  if (argc > 4)
  {
    auto k = std::atoi(argv[2]);
    auto K = std::atoi(argv[1]);
    auto from_k = std::atoi(argv[3]);
    auto from_K = std::atoi(argv[4]);
    auto offset = std::atoi(argv[5]);
    std::cout << "Generating caveman graphs from k = " << from_k << " and K = " << K << " to k = " << k << " and K = " << K << " with offset = " << offset << std::endl;

    std::ofstream file;
    file.open(argv[6], std::ios::out | std::ios::trunc | std::ios::binary);

    caveman cave;
    for (int j = from_K; j < K; j += offset)
      for (int i = from_k; i < k; i += offset)
      {
        cave.set_params(i, j);
        cave.dump_caveman("cave.bin");

        std::system("./convert -i cave.bin -o conv.bin 2>/dev/null 3>/dev/null 1> /dev/null");

        auto start = std::chrono::system_clock::now();
        std::system("./community conv.bin -l -1 2>/dev/null 3> /dev/null 1> /dev/null");
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        file << i << " " << j << " " << (double)elapsed.count() / 100.0 << " " << cave.get_nb_nodes() << std::endl;
        std::cout << i << " " << j << " " << (double)elapsed.count() / 100.0 << " " << cave.get_nb_nodes() << std::endl;
      }
  }
  else
    return -1;

  return 0;
}
