#include "graph.hh"

void caveman::set_params(int k, int K)
{
  this->clique_size = k;
  this->nb_cliques = K;
}

int caveman::get_nb_nodes()
{
  return (clique_size * (clique_size - 1) * nb_cliques) / 2;
}

void caveman::dump_caveman(int k, int K, const char* path)
{
  set_params(k, K);
  std::ofstream file;
  file.open(path, std::ios::out | std::ios::trunc | std::ios::binary);

  if (file.is_open())
  {
    // Complete graph nodes count * nb_cliques
    file << get_nb_nodes() << std::endl;
    int offset = 0;
    for (auto off = 0; off < nb_cliques; off++)
    {
      offset = off * clique_size;
      // clique_size - 2 because we don't link the last 2 nodes
      for (int i = 0; i < clique_size - 2; i++)
        for (int j = i + 1; j < clique_size; j++)
          file << i + offset << " " << j + offset << std::endl;
    }

    // Links all the cliques
    for (auto off = 0; off < nb_cliques - 1; off++)
    {
      offset = off * clique_size;
      file << clique_size - 1 + offset << " " << clique_size + offset << std::endl;
    }

    // Links the first and the last clique
    file << 0 << " " << clique_size * nb_cliques - 1 << std::endl;

    file.close();
  }
}
