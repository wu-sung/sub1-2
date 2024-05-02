//헤더파일 선언
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "rclcpp/time_source.hpp"
#include <memory>
#include <chrono>
#include <functional>
using std::placeholders::_1;
// 콜백 함수 정의
// mysub_callback: 메시지 콜백을 처리하는 함수. 수신된 메시지를 출력
void mysub_callback(rclcpp::Node::SharedPtr node, const std_msgs::msg::Int32::SharedPtr msg)
{
    RCLCPP_INFO(node->get_logger(), "Received message: %d", msg->data);
}

int main(int argc, char* argv[])
{
    // ROS 2 노드 초기화
    rclcpp::init(argc, argv);
    // 노드 생성
    auto node = std::make_shared<rclcpp::Node>("mynode");
    // 품질 서비스(QoS) 프로파일 설정
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    // 콜백 함수를 저장할 함수 객체 생성
    std::function<void(const std_msgs::msg::Int32::SharedPtr msg)> fn;
    // 콜백 함수를 std::bind를 사용하여 함수 객체에 바인딩
    fn = std::bind(mysub_callback, node, _1);
    // 토픽 구독자 생성
    auto mysub = node->create_subscription<std_msgs::msg::Int32>(
        "mytopic", qos_profile, fn); // "mytopic" 토픽을 구독하고, 수신된 메시지는 fn에 의해 처리됩니다.
    // ROS 2 노드 실행
    rclcpp::spin(node);
    // ROS 2 노드 종료
    rclcpp::shutdown();
    return 0;
}
