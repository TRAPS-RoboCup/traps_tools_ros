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

#include "traps_tools/sample/node.hpp"

#include "traps_tools/default_qos.hpp"
#include "traps_tools/sample.hpp"

namespace traps_tools::sample
{

Node::Node(
  const std::string & node_name, const std::string & node_namespace,
  const rclcpp::NodeOptions & node_options)
: rclcpp::Node(node_name, node_namespace, node_options),
  republish_string_publisher_(this->create_publisher<traps_tools::msg::SampleString>(
      std::string(this->get_name()) + "/republish_string", traps_tools::dynamic_qos())),
  string_subscription_(this->create_subscription<traps_tools::msg::SampleString>(
      std::string(this->get_name()) + "/string", traps_tools::dynamic_qos(),
      [this](traps_tools::msg::SampleString::ConstSharedPtr string_msg) {
        this->republish(string_msg);
      }))
{
}

void Node::republish(traps_tools::msg::SampleString::ConstSharedPtr string_msg)
{
  RCLCPP_INFO(this->get_logger(), "republish string : %s", string_msg->data.c_str());
  republish_string_publisher_->publish(Sample::sample_string_msg_from_ptr(string_msg));
}

}  // namespace traps_tools::sample

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(traps_tools::sample::Node)
