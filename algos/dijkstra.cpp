//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee, 
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

int main(int argc, char **argv)
{
    typedef adjacency_list <listS, vecS, directedS, no_property, property <edge_weight_t, int>> graph_t;
    typedef graph_traits <graph_t>::vertex_descriptor vertex_descriptor;
    typedef std::pair<int, int> Edge;

    graph_t G;

    std::vector<std::pair<int, int>> edge_list;

    std::ifstream infile(argv[1]);
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::vector<std::string> row(std::istream_iterator<std::string>(iss), {});
        int u = std::stoi(row[0]) - 1;
        for (int i = 1; i < row.size(); ++i) {
            std::vector<std::string> nums;
            boost::split(nums, row[i], boost::is_any_of(","));
            int v = std::stoi(nums[0]) - 1;
            int w = std::stoi(nums[1]);
            // std::cout << u << " --> " << v << " (" << w << ")" << std::endl;
            add_edge(u, v, w, G);
        }
    }

    std::vector<vertex_descriptor> p(num_vertices(G));
    std::vector<int> d(num_vertices(G));
    vertex_descriptor s = vertex(0, G);
    dijkstra_shortest_paths(G, s,
            predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, G))).
                distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, G))));

    graph_traits <graph_t>::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(G); vi != vend; ++vi) {
        // std::cout << "distance(" << *vi + 1 << ") = " << d[*vi] << ", ";
        // std::cout << "parent(" << *vi + 1 << ") = " << p[*vi] << std::endl;
    }

    int dest_list[] = {7,37,59,82,99,115,133,165,188,197};
    for (auto dest : dest_list) {
        // std::cout << dest << ": " << d[dest - 1] << std::endl;
        std::cout << d[dest - 1] << ",";
    }
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
