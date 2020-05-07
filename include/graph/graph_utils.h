#ifndef CITYSCAPE_GRAPH_UTILS_H
#define CITYSCAPE_GRAPH_UTILS_H
namespace cityscape {
namespace graph {
namespace utils {
struct Weight {
  virtual ~Weight() = default;

  virtual double get_weight(const std::shared_ptr<cityscape::graph::Edge>&) = 0;
};

struct NoWeight : Weight {
  double get_weight(const std::shared_ptr<cityscape::graph::Edge>&) override {
    return 1;
  }
};

struct DefaultWeight : Weight {
  double get_weight(
      const std::shared_ptr<cityscape::graph::Edge>& edge) override {
    return edge->weight();
  }
};
}  // namespace utils
}  // namespace graph
}  // namespace cityscape

#endif  // CITYSCAPE_GRAPH_UTILS_H
