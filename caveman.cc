#include <iostream>
#include <unistd.h>
#include <chrono>

#include "graph.hh"

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    auto k = std::atoi(argv[2]);
    auto K = std::atoi(argv[1]);
    std::cout << "Generating caveman graphs up to k = " << k << " and K = " << K << std::endl;

    std::ofstream file;
    file.open(argv[3], std::ios::out | std::ios::trunc | std::ios::binary);

    caveman cave;
    for (int j = 0; j < K; j += 10)
      for (int i = 0; i < k; i += 10)
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
