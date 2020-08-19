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
  //! \param[in] src Source point
  //! \param[in] dest Destination point
  Segment(cityscape::id_t id, const std::shared_ptr<Point> &src,
          const std::shared_ptr<Point> &dest)
      : id_{id}, src_{src}, dest_{dest} {}

  //! Get id
  const cityscape::id_t id() const { return id_; }

  //! Source point
  std::shared_ptr<const Point> src() const { return src_; }

  //! Destination point
  std::shared_ptr<const Point> dest() const { return dest_; }

private:
  //! id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! Source node
  std::shared_ptr<Point> src_{NULL};
  //! Destination node
  std::shared_ptr<Point> dest_{NULL};
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
    return geometry::get<Dimension>(*s.src());
  }

  static inline void set(Segment &s, coordinate_type const &value) {
    geometry::set<Dimension>(*s.src(), value);
  }
};

template <std::size_t Dimension> struct indexed_access<Segment, 1, Dimension> {
  typedef typename geometry::coordinate_type<Point>::type coordinate_type;

  static inline coordinate_type get(Segment const &s) {
    return geometry::get<Dimension>(*s.dest());
  }

  static inline void set(Segment &s, coordinate_type const &value) {
    geometry::set<Dimension>(*s.dest(), value);
  }
};
} // namespace traits
} // namespace geometry
} // namespace boost

#endif // CITYSCAPE_SEGMENT_H