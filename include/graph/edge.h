#ifndef CITYSCAPE_GRAPH_EDGE_H_
#define CITYSCAPE_GRAPH_EDGE_H_

#include <memory>
#include <set>

#include "node.h"
#include "segment.h"

namespace cityscape {
namespace graph {

// Alias graph edge weight as double
using weight_t = double;

//! Graph edge class
//! \brief Base class of a graph edge
class Edge : public cityscape::spatial::Segment {
 public:
  //! Constructor with source and destination nodes and a unique edge id
  //! \param[in] src Source node pointer
  //! \param[in] dest Destination node pointer
  //! \param[in] id Index of the edge
  //! \param[in] tag Tag to categorize edge (default is empty)
  Edge(const std::shared_ptr<cityscape::graph::Node>& src,
       const std::shared_ptr<cityscape::graph::Node>& dest, cityscape::id_t id,
       const std::string& tag = std::string())
      : cityscape::spatial::Segment(id, src, dest) {
    src_ = std::const_pointer_cast<const cityscape::graph::Node>(src);
    dest_ = std::const_pointer_cast<const cityscape::graph::Node>(dest);
    // If not an empty tag, insert tag
    if (!tag.empty()) tags_.insert(tag);
  }

  //! Check if the edge has a specific tag
  bool check_tag(const std::string& tag) const {
    return (tags_.find(tag) != tags_.end() ? true : false);
  }

  //! Get edge weight
  //! \retval weight_ Weight of the edge
  double weight() const { return weight_; }

  //! Assign edge weight
  //! \param[in] weight Weight of the edge
  void weight(double weight) { weight_ = weight; }

  //! Source node
  std::shared_ptr<const cityscape::graph::Node> src() const { return src_; }

  //! Destination node
  std::shared_ptr<const cityscape::graph::Node> dest() const { return dest_; }

 protected:
  //! Tags
  std::set<std::string> tags_;
  //! Weight
  double weight_{0.};

 private:
  //! Source node
  std::shared_ptr<const cityscape::graph::Node> src_;
  //! Destination node
  std::shared_ptr<const cityscape::graph::Node> dest_;
};
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_EDGE_H_