//헤더파일 선언
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "rclcpp/time_source.hpp"
#include <memory>
#include <chrono>
#include <functional>
using namespace std::chrono_literals;
//콜백함수 (Int32메세지형태) pub
void callback(rclcpp::Node::SharedPtr node, 
rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub)
{
//카운트하기 위한 정수형 변수 count 선언
static int count=0;
// Int32메세지 형태인 auto 자료형 message선언
auto message = std_msgs::msg::Int32();
//message.data값 초기화
message.data = count++;
//ROS 2에서 사용되는 로깅 매크로
RCLCPP_INFO(node->get_logger(), "Publish: %d", message.data);
//pub 메시지를 퍼블리시하는 역할(message객체를 퍼블리시)
pub->publish(message);
}

int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
// auto자료형 node변수 선언(mynode라는 노드를 만듬)
auto node = std::make_shared<rclcpp::Node>("mynode");
// qos설정
auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
// auto자료형 pub선언 (mytopic라는 만듬)
auto pub = node->create_publisher<std_msgs::msg::Int32>("mytopic", qos_profile
);
//std::function 객체인 fn을 선언
std::function<void()> fn = std::bind(callback, node, pub);
//현재 노드(node)에서 50밀리초 주기로 동작하는 타이머를 생성
auto timer = node->create_wall_timer(50ms, fn);
// node가 끝나기 전까지 반복실행
rclcpp::spin(node);
// 종료
rclcpp::shutdown();
//0값을 반환
return 0;
}
