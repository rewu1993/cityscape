#ifndef CITYSCAPE_UTILS_SELECT_H
#define CITYSCAPE_UTILS_SELECT_H

#include "layer.h"
namespace cityscape {
namespace spatial {
namespace utils {
template <typename P, typename Q>
struct Specification {
  using ntypes = std::vector<cityscape::id_t>;
  using etypes = std::vector<std::tuple<cityscape::id_t, cityscape::id_t>>;
  //  virtual ~Specification() = default;
  virtual void compute_attributes(std::shared_ptr<Layer<P>> l){};
  virtual std::shared_ptr<ntypes> nids(){};
  virtual std::shared_ptr<etypes> edge_specs(){};
};

template <typename P, typename Q>
class IntersectionSpec : public Specification<P, Q> {
 public:
  typedef typename Specification<P, Q>::ntypes ntypes;
  typedef typename Specification<P, Q>::etypes etypes;
  inline explicit IntersectionSpec(std::shared_ptr<Q>& intersect_obj)
      : query_(intersect_obj),
        valid_nids_(std::make_shared<ntypes>()),
        valid_edges_(std::make_shared<etypes>()) {}

  inline std::shared_ptr<ntypes> nids() override { return valid_nids_; };

  inline std::shared_ptr<etypes> edge_specs() override { return valid_edges_; };

  void compute_attributes(std::shared_ptr<Layer<P>> l) override {
    compute_valid_nodes(l);
        compute_valid_edges(l);
  }

 private:
  void compute_valid_nodes(std::shared_ptr<Layer<P>> l);
  void compute_valid_edges(std::shared_ptr<Layer<P>> l);

  std::shared_ptr<Q> query_;
  std::shared_ptr<ntypes> valid_nids_;
  std::shared_ptr<etypes> valid_edges_;
};

template <typename P, typename Q>
std::shared_ptr<Layer<P>> select_sub_layer(std::shared_ptr<Layer<P>> l,
                                           Specification<P, Q>& specification);

#include "utils_select.tcc"
}  // namespace utils
}  // namespace spatial
}  // namespace cityscape

#endif  // CITYSCAPE_UTILS_SELECT_H
