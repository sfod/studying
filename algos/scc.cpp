#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

/*

  This example demonstrates the usage of the connected_components
  algorithm on a undirected graph. The example graphs come from
  "Introduction to Algorithms", Cormen, Leiserson, and Rivest p. 87
  (though we number the vertices from zero instead of one).

  Sample output:

  Total number of components: 3
  Vertex 0 is in component 0
  Vertex 1 is in component 0
  Vertex 2 is in component 1
  Vertex 3 is in component 2
  Vertex 4 is in component 0
  Vertex 5 is in component 1

 */

using namespace std;

int main(int argc, char **argv) 
{
    using namespace boost;
    {
        typedef adjacency_list <vecS, vecS, directedS> Graph;

        Graph G;
        std::ifstream infile(argv[1]);
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::vector<int> nums(std::istream_iterator<int>(iss), {});
            int u = nums[0];
            int v = nums[1];
            // std::cout << u << " --> " << v << std::endl;
            add_edge(u, v, G);
        }

        // add_edge(0, 1, G);
        // add_edge(1, 2, G);
        // add_edge(2, 0, G);
        // add_edge(3, 4, G);
        // add_edge(4, 5, G);
        // add_edge(5, 3, G);

        typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;

        std::vector<int> component(num_vertices(G)), discover_time(num_vertices(G));
        std::vector<default_color_type> color(num_vertices(G));
        std::vector<Vertex> root(num_vertices(G));
        int num = strong_components(G, make_iterator_property_map(component.begin(), get(vertex_index, G)), 
                    root_map(make_iterator_property_map(root.begin(), get(vertex_index, G))).
                    color_map(make_iterator_property_map(color.begin(), get(vertex_index, G))).
                    discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, G))));


        std::map<int, int> comps;

        // std::cout << "Total number of components: " << num << std::endl;
        std::vector<int>::size_type i;
        for (i = 0; i != component.size(); ++i) {
            ++comps[component[i]];
        }

        for (auto it : comps) {
            std::cout << it.first << " " << it.second << std::endl;
        }

    }
    return 0;
}
