#pragma once

# include <vector>
# include <fstream>
# include <string>
# include <set>


class caveman
{
  public:
    caveman(int k = 1, int K = 1)
    {
      this->clique_size = k;
      this->nb_cliques = K;
    }

    void set_params(int k, int K);
    int get_nb_nodes();
    void dump_caveman(int k, int K, const char* path);

  private:
    int clique_size = 0;
    int nb_cliques = 0;

    std::vector<std::pair<int, int>> nodes;
};
