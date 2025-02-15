//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee, 
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, Indiana University,
// Bloomington, IN 47405.
//
// Permission to modify the code and to distribute the code is
// granted, provided the text of this NOTICE is retained, a notice if
// the code was modified is included with the above COPYRIGHT NOTICE
// and with the COPYRIGHT NOTICE in the LICENSE file, and that the
// LICENSE file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================
#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <boost/graph/adjacency_list.hpp>
int
main()
{
  using namespace boost;
  typedef adjacency_list < listS, listS, directedS,
    property < vertex_name_t, std::string > >graph_t;
  graph_t g;
  graph_traits < graph_t >::vertex_descriptor u = add_vertex(g);
  property_map < graph_t, vertex_name_t >::type
    name_map = get(vertex_name, g);
  name_map[u] = "Joe";
  std::cout << name_map[u] << std::endl;
  return EXIT_SUCCESS;
}
