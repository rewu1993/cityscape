template <typename P, typename Q>
void IntersectionSpec<P, Q>::compute_valid_nodes(std::shared_ptr<Layer<P>> l) {
  valid_nids_.clear();
  auto point_index = l->point_index();
  auto intersect_points = point_index->intersect(*query_);

  for (const auto& p : intersect_points) {
    auto nname = p->name();
    auto nid = l->nname2id(nname);
    valid_nids_.insert(nid);
  }
}

template <typename P, typename Q>
void IntersectionSpec<P, Q>::compute_valid_edges(std::shared_ptr<Layer<P>> l) {

  std::vector<cityscape::id_t> intersect;
  auto L = l->plain_adjacency_list();

  for (const auto& sid : valid_nids_) {
    auto list = L.at(sid);
    intersect.clear();
    std::set_intersection(list.begin(), list.end(), valid_nids_.begin(),
                          valid_nids_.end(),
                          std::inserter(intersect, intersect.begin()));
    for (const auto& eid : intersect) {
      valid_edges_.emplace_back(std::make_tuple(sid, eid));
    }
  }
}

template <typename P, typename Q>
std::shared_ptr<Layer<P>> select_sub_layer(std::shared_ptr<Layer<P>> l,
                                           Specification<P, Q>& specification) {

  auto new_layer = std::make_shared<spatial::Layer<P>>(0);
  specification.compute_attributes(l);

  auto nids = specification.nids();
  auto edge_specs = specification.edge_specs();

  // construct nodes
  for (const auto nid : nids) {
    new_layer->add_node(l->point(nid));
  }
  // construct edges
  for (const auto e_spec : edge_specs) {
    new_layer->create_edge(std::get<0>(e_spec), std::get<1>(e_spec), true);
  }
  return new_layer;
}