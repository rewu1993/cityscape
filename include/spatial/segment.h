#ifndef CITYSCAPE_SEGMENT_H
#define CITYSCAPE_SEGMENT_H

#include <vector>

#include "point.h"

namespace cityscape {
namespace spatial {
//! Spatial Segment class
//! \brief Base class of a spatial segment
class Segment {
public:
  Segment() = default;
  //! Constructor
  //! \param[in] id Index of the segment
  //! \param[in] p1 One end point
  //! \param[in] p1 One end point
  Segment(cityscape::id_t id, const std::shared_ptr<Point> &p1,
          const std::shared_ptr<Point> &p2)
      : id_{id}, p1_{p1}, p2_{p2} {}

  //! Get id
  const cityscape::id_t id() const { return id_; }

  //! Source point
  std::shared_ptr<const Point> p1() const { return p1_; }

  //! Destination point
  std::shared_ptr<const Point> p2() const { return p2_; }

private:
  //! id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Source node
  std::shared_ptr<Point> p1_{NULL};
  //! Destination node
  std::shared_ptr<Point> p2_{NULL};
};
} // namespace spatial
} // namespace cityscape

// Register segment into boost

namespace boost {
namespace geometry {
namespace traits {
using namespace cityscape::spatial;

template <> struct tag<Segment> { typedef segment_tag type; };

template <> struct point_type<Segment> { typedef Point type; };

template <std::size_t Dimension> struct indexed_access<Segment, 0, Dimension> {
  typedef typename geometry::coordinate_type<Point>::type coordinate_type;

  static inline coordinate_type get(Segment const &s) {
    return geometry::get<Dimension>(*s.p1());
  }

  static inline void set(Segment &s, coordinate_type const &value) {
    geometry::set<Dimension>(*s.p1(), value);
  }
};

template <std::size_t Dimension> struct indexed_access<Segment, 1, Dimension> {
  typedef typename geometry::coordinate_type<Point>::type coordinate_type;

  static inline coordinate_type get(Segment const &s) {
    return geometry::get<Dimension>(*s.p2());
  }

  static inline void set(Segment &s, coordinate_type const &value) {
    geometry::set<Dimension>(*s.p2(), value);
  }
};
} // namespace traits
} // namespace geometry
} // namespace boost

#endif // CITYSCAPE_SEGMENT_H