#ifndef CITYSCAPE_UTILS_SELECT_H
#define CITYSCAPE_UTILS_SELECT_H

#include "layer.h"
namespace cityscape {
namespace spatial {
namespace utils {
template <typename P, typename Q>
class Specification {
  //  virtual ~Specification() = default;
 public:
  virtual void compute_attributes(std::shared_ptr<Layer<P>> l){};
  virtual std::set<cityscape::id_t> nids(){};
  virtual std::vector<std::tuple<cityscape::id_t, cityscape::id_t>>
      edge_specs(){};
};

template <typename P, typename Q>
class IntersectionSpec : public Specification<P, Q> {
 public:
  explicit IntersectionSpec(std::shared_ptr<Q>& intersect_obj)
      : query_(intersect_obj) {}
  inline std::set<cityscape::id_t> nids() override { return valid_nids_; };

  inline std::vector<std::tuple<cityscape::id_t, cityscape::id_t>> edge_specs()
      override {
    return valid_edges_;
  };

  void compute_attributes(std::shared_ptr<Layer<P>> l) override {
    compute_valid_nodes(l);
    compute_valid_edges(l);
  }

 private:
  void compute_valid_nodes(std::shared_ptr<Layer<P>> l);
  void compute_valid_edges(std::shared_ptr<Layer<P>> l);

  std::shared_ptr<Q> query_;
  std::set<cityscape::id_t> valid_nids_;
  std::vector<std::tuple<cityscape::id_t, cityscape::id_t>> valid_edges_;
};

template <typename P, typename Q>
std::shared_ptr<Layer<P>> select_sub_layer(std::shared_ptr<Layer<P>> l,
                                           Specification<P, Q>& specification);

#include "utils_select.tcc"
}  // namespace utils
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_SELECT_H
