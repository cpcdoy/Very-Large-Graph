#include <iostream>
#include <unistd.h>
#include <chrono>
#include <vector>
#include <mutex>
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "graph.hh"

std::mutex mutex;

long get_file_size(std::string file_name)
{
    struct stat stat_buf;
    int rc = stat(file_name.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void compute(std::ofstream& file, int from_k, int from_K, int k, int K, int offset, int t)
{
  std::cout << "Thread " << t << " : from k = " << from_k << " and K = " << from_K << " to k = " << k << " and K = " << K << " with offset = " << offset << std::endl;
  caveman cave;
  for (int j = from_K; j < K; j += offset)
    for (int i = from_k; i < k; i += offset)
    {
      std::string file_name("cave_" + std::to_string(t) + ".bin");
      cave.dump_caveman(i, j, file_name.c_str());

      std::lock_guard<std::mutex> lock(mutex);

      std::string convert("./convert -i " + file_name + " -o conv.bin 2>/dev/null 3>/dev/null 1> /dev/null");
      std::system(convert.c_str());

      auto start = std::chrono::system_clock::now();
      std::system("./community conv.bin -l -1 2>/dev/null 3>/dev/null 1> /dev/null");
      auto end = std::chrono::system_clock::now();
      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      file << i << " " << j << " " << (double)elapsed.count() / 100.0 << " " << cave.get_nb_nodes() << " " << get_file_size(file_name) << std::endl;
      std::cout << "Thread " << t <<  " : " << i << " " << j << " " << (double)elapsed.count() / 100.0 << " " << cave.get_nb_nodes() << " " << get_file_size(file_name) << std::endl;
    }
}

int main(int argc, char** argv)
{
  if (argc > 4)
  {
    auto k = std::atoi(argv[1]);
    auto K = std::atoi(argv[2]);
    auto from_k = std::atoi(argv[3]);
    auto from_K = std::atoi(argv[4]);
    auto offset = std::atoi(argv[5]);
    std::cout << "Generating caveman graphs from k = " << from_k << " and K = " << from_K << " to k = " << k << " and K = " << K << " with offset = " << offset << std::endl;

    std::ofstream file;
    file.open(argv[6], std::ios::out | std::ios::trunc | std::ios::binary);

    int nb_threads = std::thread::hardware_concurrency();

    std::cout << "Spawning " << nb_threads << " threads" << std::endl;

    std::vector<std::thread> tids;

    for (int t = 0; t < nb_threads; t++)
    {
      auto step = t * (K - from_K) / nb_threads;
      auto step2 = (t + 1) * (K - from_K) / nb_threads;
      std::thread th(compute, std::ref(file), from_k, from_K + step, k, from_K + step2, offset, t);
      tids.push_back(std::move(th));
    }
    for (auto& tid : tids)
      tid.join();
  }
  else
    return -1;

  return 0;
}
