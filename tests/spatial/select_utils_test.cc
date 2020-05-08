#include "catch.hpp"
#include "utils_select.h"

TEST_CASE("Spatial select utils check", "[spatial][layer][utils]") {
  using Point = cityscape::spatial::Point2d;
  using Seg = cityscape::spatial::Segment<Point>;

  auto layer = std::make_shared<cityscape::spatial::Layer<Point>>(0);
  // create some points for storing
  // Coordinates
  const std::array<double, 2> coordinates0 = {1.5, 2.4};
  const std::array<double, 2> coordinates1 = {1.8, 2.4};
  const std::array<double, 2> coordinates2 = {3, 4};

  auto p0 = std::make_shared<Point>(0, "spatial0", coordinates0);
  auto p1 = std::make_shared<Point>(1, "spatial1", coordinates1);
  auto p2 = std::make_shared<Point>(2, "spatial2", coordinates2);
  // add points
  REQUIRE(layer->add_node(p0) == true);
  REQUIRE(layer->add_node(p1) == true);
  REQUIRE(layer->add_node(p2) == true);

  // add some segments (edges)
  layer->create_edge("spatial0", "spatial1", true);
  layer->create_edge("spatial0", "spatial2", true);
  layer->create_edge("spatial1", "spatial2", true);
  REQUIRE(layer->nnodes() == 3);
  REQUIRE(layer->nedges() == 3);

  SECTION("Sublayer selection specifications test") {
    using Polygon = boost::geometry::model::polygon<Point>;
    auto triangle = std::make_shared<Polygon>();
    boost::geometry::read_wkt("POLYGON((0 0,1.5 3,3 0, 0 0))", *triangle);

    auto intersection_spec =
        cityscape::spatial::utils::IntersectionSpec<Point, Polygon>(triangle);
    intersection_spec.compute_attributes(layer);

    auto nids = intersection_spec.nids();
    REQUIRE(nids->size() == 2);
    REQUIRE(std::find(nids->begin(), nids->end(), 0) != nids->end());
    REQUIRE(std::find(nids->begin(), nids->end(), 1) != nids->end());
    REQUIRE(std::find(nids->begin(), nids->end(), 2) == nids->end());

    auto edge_specs = intersection_spec.edge_specs();
    REQUIRE(edge_specs->size() == 1);
    REQUIRE(std::find(edge_specs->begin(), edge_specs->end(),
                      std::make_tuple(0, 1)) != edge_specs->end());
  }
  SECTION("Sublayer creation test") {
    using Polygon = boost::geometry::model::polygon<Point>;
    auto triangle = std::make_shared<Polygon>();
    boost::geometry::read_wkt("POLYGON((0 0,1.5 3,3 0, 0 0))", *triangle);

    auto intersection_spec =
        cityscape::spatial::utils::IntersectionSpec<Point, Polygon>(triangle);
    auto new_layer =
        cityscape::spatial::utils::select_sub_layer<Point, Polygon>(
            layer, intersection_spec);
    // check number of attributes in new layer
    REQUIRE(new_layer->nnodes() == 2);
    REQUIRE(new_layer->nedges() == 1);
    // check stored points
    REQUIRE(layer->point(0)->name() == "spatial0");
    // check stored edges
    auto nid0 = layer->nname2id("spatial0");
    auto nid1 = layer->nname2id("spatial1");
    REQUIRE(layer->segment(nid1, nid0) == nullptr);
    REQUIRE(layer->segment(nid0, nid1)->id() == 0);
  }
}