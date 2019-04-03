// Copyright (c) 2019 fortiss GmbH, Julian Bernhard, Klemens Esterle, Patrick Hart, Tobias Kessler
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.


#include <string>
#include "map.hpp"
#include "modules/world/map/map_interface.hpp"
#include "modules/world/map/route_generator.hpp"
#include "modules/world/map/roadgraph.hpp"
#include "modules/world/opendrive/opendrive.hpp"

using namespace modules::world::map;
using modules::world::opendrive::LaneId;
using modules::geometry::Point2d;


void python_map(py::module m) {
  py::class_<MapInterface, std::shared_ptr<MapInterface>>(m, "MapInterface")
      .def(py::init<>())
      .def("set_open_drive_map", &MapInterface::set_open_drive_map)
      .def("get_nearest_lanes", [](const MapInterface& m,
                                    const Point2d& point,
                                    const unsigned& num_lanes) {
          std::vector<LanePtr> lanes;
          m.get_nearest_lanes(point, num_lanes, lanes);
          return lanes;
      }) 
      .def("set_roadgraph", &MapInterface::set_roadgraph)
      .def("get_roadgraph", &MapInterface::get_roadgraph)
      .def("get_open_drive_map", &MapInterface::get_open_drive_map)
      .def("get_driving_corridor",[](const MapInterface& m, const LaneId& startid, const LaneId goalid) {
          Line inner_line, outer_line, center_line;
          bool result = m.get_driving_corridor(startid, goalid, inner_line, outer_line, center_line);
          return std::make_tuple(inner_line, outer_line, center_line);
      });

  py::class_<RouteGenerator, std::shared_ptr<RouteGenerator>>(m, "RouteGenerator")
      .def(py::init<LaneId, const MapInterfacePtr&>())
      .def_property_readonly("inner_line", &RouteGenerator::get_inner_line)
      .def_property_readonly("outer_line", &RouteGenerator::get_outer_line)
      .def_property_readonly("center_line", &RouteGenerator::get_center_line)
      .def("set_goal_lane_id", &RouteGenerator::set_goal_lane_id)
      .def("set_map_interface", &RouteGenerator::set_map_interface)
      .def("generate", &RouteGenerator::generate);

  py::class_<Roadgraph, std::shared_ptr<Roadgraph>>(m, "Roadgraph")
    .def(py::init<>())
    .def("add_lane", &Roadgraph::add_lane)
    .def("get_vertices", &Roadgraph::get_vertices)
    .def("get_edges", &Roadgraph::get_edges)
    .def("get_edge", &Roadgraph::get_edge)
    .def("get_edge_descr", &Roadgraph::get_edge_descr)
    .def("get_out_edges", &Roadgraph::get_out_edges)
    .def("get_vertex", &Roadgraph::get_vertex)
    .def("get_next_vertices", &Roadgraph::get_next_vertices)
    .def("get_vertex_by_lane_id", &Roadgraph::get_vertex_by_lane_id)
    .def("add_inner_neighbor", &Roadgraph::add_inner_neighbor)
    .def("get_inner_neighbor", &Roadgraph::get_inner_neighbor)
    .def("add_outer_neighbor", &Roadgraph::add_outer_neighbor)
    .def("find_path", &Roadgraph::find_path)
    .def("print_graph", (void (Roadgraph::*)(const char*)) &Roadgraph::print_graph)
    .def("add_successor", &Roadgraph::add_successor);
}
