// Copyright 2024 TRAPS
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TRAPS_TOOLS_SAMPLE__NODE_HPP_
#define TRAPS_TOOLS_SAMPLE__NODE_HPP_

#include <string>

#include "rclcpp/node.hpp"

#include "traps_tools/visibility.hpp"

namespace traps_tools::sample
{

class Node : public rclcpp::Node
{
public:
  static constexpr auto default_node_name() noexcept {return "sample";}

  TRAPS_TOOLS_PUBLIC
  Node(
    const std::string & node_name, const std::string & node_namespace,
    const rclcpp::NodeOptions & node_options = rclcpp::NodeOptions());

  TRAPS_TOOLS_PUBLIC
  explicit inline Node(
    const std::string & node_name,
    const rclcpp::NodeOptions & node_options = rclcpp::NodeOptions())
  : Node(node_name, "", node_options) {}

  TRAPS_TOOLS_PUBLIC
  explicit inline Node(const rclcpp::NodeOptions & node_options = rclcpp::NodeOptions())
  : Node(this->default_node_name(), "", node_options) {}
};

} // namespace traps_tools::sample

#endif  // TRAPS_TOOLS_SAMPLE__NODE_HPP_
