#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "rclcpp/time_source.hpp"
#include <memory>
#include <chrono>
#include <functional>
using std::placeholders::_1;
void mysub_callback(rclcpp::Node::SharedPtr node, 
const std_msgs::msg::Int32::SharedPtr msg)
{
RCLCPP_INFO(node->get_logger(), "Received message: %d", msg->data);
}

int main(int argc, char* argv[])
{
rclcpp::init(argc, argv);
auto node = std::make_shared<rclcpp::Node>("mynode");
auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
std::function<void(const std_msgs::msg::Int32::SharedPtr msg)> fn;
fn = std::bind(mysub_callback, node, _1);
auto mysub = node->create_subscription<std_msgs::msg::Int32>("mytopic",qos_profile,fn);
rclcpp::spin(node);
rclcpp::shutdown();
return 0;
}
