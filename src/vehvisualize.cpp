#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include <iostream>
#include <tf/transform_broadcaster.h>
//#include <geometry_msgs/TransformStamped.h>

using namespace std;

void vehicleCallback(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
  // veh_msg.pose = pose->pose;
  static tf::TransformBroadcaster br;
  tf::Transform tform;

  tform.setOrigin(tf::Vector3(msg->pose.position.x,
                              msg->pose.position.y, msg->pose.position.z));

 tform.setRotation(tf::Quaternion(msg->pose.orientation.x,msg->pose.orientation.y,
      msg->pose.orientation.z,msg->pose.orientation.w).normalize());
 // tform.setRotation(tf::Quaternion(1,1,1,1));

  br.sendTransform(tf::StampedTransform(tform, ros::Time::now(), "local_map", "quad"));
  //tf_pub.publish(tform);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "quadtf");
  ros::NodeHandle n;
  //ros::Publisher marker_pub;
  ros::Subscriber veh_sub;
  ros::Publisher tf_pub;
  // tf_pub = n.advertise<geometry_msgs::TransformStamped>("/quad", 1000);
  veh_sub = n.subscribe("vehicle", 100, &vehicleCallback);
  //uint32_t shape;

  //  geometry_msgs::TransformStamped tform;
  //ros::Rate r(1);
  ros::spin();

  return 0;
}