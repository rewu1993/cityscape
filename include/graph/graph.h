#ifndef CITYSCAPE_GRAPH_GRAPH_H_
#define CITYSCAPE_GRAPH_GRAPH_H_

#include <map>

#include "tsl/robin_map.h"

#include "edge.h"
#include "index_manager.h"
#include "node.h"

namespace cityscape {
namespace graph {

//! Graph class
//! \brief Base class of graph
class Graph {
 public:
  //! Constructor with a unique graph id, tag and initialize idx
  //! \param[in] id Index of the graph
  //! \param[in] tag Tag to categorize graph (default is empty)
  Graph(cityscape::id_t id, const std::string& tag = std::string());

  //! Graph id
  //! \retval id_ Id of the graph
  cityscape::id_t id() const;

  //! Check if the graph has a specific tag
  bool check_tag(const std::string& tag) const;

  //! Add node
  //! \param[in] node Pointer to node object
  bool add_node(const std::shared_ptr<Node>& node);

  //! Number of nodes
  cityscape::id_t nnodes() const;

  //! Create edge
  //! \param[in] src Source node name
  //! \param[in] dest Destination node name
  //! \param[in] directed Edge is directed or undirected
  //! \param[in] tag Tag to categorize edge (default is empty)
  bool create_edge(const std::string& src, const std::string& dest,
                   bool directed, const std::string& tag = std::string());

  //! Number of edges
  cityscape::id_t nedges() const;

 private:
  //! Graph id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Tags
  std::set<std::string> tags_;
  //! Node ID manager
  cityscape::IndexManager node_idx_;
  //! Edge ID manager
  cityscape::IndexManager edge_idx_;
  //! Nodes
  tsl::robin_map<cityscape::id_t, std::shared_ptr<cityscape::graph::Node>>
      nodes_;
  //! Nodes and names key
  tsl::robin_map<std::string, cityscape::id_t> nodes_names_;
  // Edges
  std::map<std::tuple<cityscape::id_t, cityscape::id_t>,
           std::shared_ptr<cityscape::graph::Edge>>
      edges_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_GRAPH_H_
