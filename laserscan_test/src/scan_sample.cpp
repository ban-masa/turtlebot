#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <iostream>

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  double angle_min = msg->angle_min;
  double angle_max = msg->angle_max;
  double angle_increment = msg->angle_increment;

  double range_min = msg->range_min;
  double range_max = msg->range_max;

  std::cout << "range_max: " << range_max << std::endl;

  size_t data_length = (angle_max - angle_min) / angle_increment;
  for (size_t i = 0; i < data_length; i++) {
    double r = std::min(range_max, std::max(range_min, (double)msg->ranges[i]));
    double x = r * std::cos(angle_min + i * angle_increment);
    double y = r * std::sin(angle_min + i * angle_increment);
    //点の位置を計算してるだけ（表示はしていない）
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "lasertest_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/scan", 1, scanCallback);
  ros::spin();
  return 0;
}
