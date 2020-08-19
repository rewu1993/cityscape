#ifndef CITYSCAPE_POINT_H
#define CITYSCAPE_POINT_H

#include <array>
#include <boost/geometry/geometry.hpp>
#include <limits>
#include <memory>

#include "types.h"

namespace cityscape {
namespace spatial {
class Point {
 public:
  Point() = default;
  //! Constructor with a unique point id
  //! \param[in] id Index of the point
  constexpr Point(cityscape::id_t id) : id_{id} {}

  //! Constructor with coordinates
  //! \param[in] id Index of the point
  //! \param[in] coordinates Coordinates (x,y) of the point
  Point(cityscape::id_t id, const std::array<double, 2> coordinates)
      : id_{id}, coordinates_{coordinates} {}

  //! Get id
  const cityscape::id_t id() const { return id_; }

  //! Return kth coordinates (for boost register)
  //! \retval kth coordinate of the point
  template <std::size_t K>
  double get() const {
    if (K > dim_ - 1) {
      throw std::runtime_error("Try to get more dimension for a point");
    }
    return coordinates_[K];
  }

  //! Set kth coordinate (for boost register)
  template <std::size_t K>
  void set(const double x) {
    if (K > dim_ - 1) {
      throw std::runtime_error("Try to get more dimension for a point");
    }
    coordinates_[K] = x;
  }

  //! Setup coordinate
  //! \param[in] x coordinate x
  //! \param[in] y coordinate y
  void coordinate(const double x, const double y) {
    set<0>(x);
    set<1>(y);
  }

  //! return coordinate
  const std::array<double, 2> coordinate() const { return coordinates_; }

 private:
  //! dimension
  unsigned dim_{2};
  //! id
  cityscape::id_t id_{std::numeric_limits<cityscape::id_t>::max()};
  //! point coordinate
  std::array<double, 2> coordinates_{std::numeric_limits<double>::max(),
                                     std::numeric_limits<double>::max()};
};

inline bool operator==(Point const& lhs, Point const& rhs) {
  return lhs.coordinate() == rhs.coordinate();
}

inline bool operator!=(Point const& lhs, Point const& rhs) {
  return !(lhs == rhs);
}

}  // namespace spatial
}  // namespace cityscape

// Register Point as a 2D Point
// Adapt the point to the boost concept
namespace boost {
namespace geometry {
namespace traits {
template <>
struct tag<cityscape::spatial::Point> {
  typedef point_tag type;
};

template <>
struct coordinate_type<cityscape::spatial::Point> {
  typedef double type;
};

template <>
struct coordinate_system<cityscape::spatial::Point> {
  typedef boost::geometry::cs::cartesian type;
};

template <>
struct dimension<cityscape::spatial::Point> : boost::mpl::int_<2> {};

template <std::size_t Dimension>
struct access<cityscape::spatial::Point, Dimension> {
  static inline double get(cityscape::spatial::Point const& p) {
    return p.get<Dimension>();
  }

  static inline void set(cityscape::spatial::Point& p, double const& value) {
    p.set<Dimension>(value);
  }
};
}  // namespace traits
}  // namespace geometry
}  // namespace boost

#endif  // CITYSCAPE_POINT_H
