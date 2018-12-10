#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/Image.h"
#include <fstream>
#include <iostream>
#include <algorithm>

size_t data_length;
double* pointx;
double* pointy;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  double angle_min = msg->angle_min;
  double angle_max = msg->angle_max;
  double angle_increment = msg->angle_increment;

  double range_min = msg->range_min;
  double range_max = msg->range_max;

  data_length = (angle_max - angle_min) / angle_increment;
  delete[] pointx;
  delete[] pointy;
  pointx = new double[data_length];
  pointy = new double[data_length];
  for (size_t i = 0; i < data_length; i++) {
    double r = std::min(range_max, std::max(range_min, (double)msg->ranges[i]));
    pointx[i] = r * std::cos(angle_min + i * angle_increment);
    pointy[i] = r * std::sin(angle_min + i * angle_increment);
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "lasertest_node");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/scan", 1, scanCallback);
  ros::Publisher pub = n.advertise<sensor_msgs::Image>("/laser_image", 10);
  ros::Rate loop_rate(10);
  while (ros::ok()) {
    ros::spinOnce();
    sensor_msgs::Image msg;
    msg.height = 500;
    msg.width = 500;
    msg.encoding = "mono8";
    msg.step = msg.width;
    for (int y = 0; y < msg.height; y++) {
      for (int x = 0; x < msg.width; x++) {
        msg.data.push_back(0xFF);
      }
    }
    for (int i = 0; i < data_length; i++) {
      int x = (int)((pointx[i] * 50) + msg.width / 2);
      int y = (int)(msg.height / 2 - (pointy[i] * 50));
      x = std::min((int)msg.width - 1, std::max(0, x));
      y = std::min((int)msg.height - 1, std::max(0, y));
      msg.data[msg.width * y + x] = 0x00;
    }
    pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
