#include "catch.hpp"
#include "csv_reader.h"
#include "utils_io.h"

TEST_CASE("CSV reader", "[csv_reader]") {
  auto reader = std::make_shared<cityscape::io::CSV_reader>(
      "../tests/test_data/csv_test.csv");

  SECTION("check read keys ") {
    auto headers = reader->headers();
    REQUIRE(headers[0] == "id");
    REQUIRE(headers[1] == "x");
    REQUIRE(headers[2] == "y");
  }

  SECTION("check row format data") {
    auto row_data = reader->row_data();
    REQUIRE(row_data[0][0] == "0");
    REQUIRE(row_data[1][2] == "210");
    REQUIRE(row_data[2][1] == "300");
  }

  SECTION("check col format data") {
    auto col_data = reader->col_data();
    REQUIRE(col_data[0][0] == "0");
    REQUIRE(col_data[1][2] == "300");
    REQUIRE(col_data[2][1] == "210");
  }

  SECTION("check transform to different types") {
    auto col = reader->get_col<int>("x");
    REQUIRE(col[0] == 100);
    REQUIRE(col[1] == 200);
    REQUIRE(col[2] == 300);

    auto col_double = reader->get_col<double>("x");
    REQUIRE(col_double[0] == 100);
    REQUIRE(col_double[1] == 200);
    REQUIRE(col_double[2] == 300);

    auto col_str = reader->get_col<std::string>("x");
    REQUIRE(col_str[0] == "100");
    REQUIRE(col_str[1] == "200");
    REQUIRE(col_str[2] == "300");
  }

  SECTION("Construct points from csv file") {
    cityscape::io::CSV_point_info csv_info("../tests/test_data/csv_test.csv",
                                           "id", "x", "y", "name", "tag");
    auto point_list = cityscape::io::construct_points_csv(csv_info);

    REQUIRE(point_list.size() == 3);
    REQUIRE(point_list[1]->id() == 1);
    REQUIRE(point_list[2]->check_tag("\"a fair place\"") == true);
  }
}
