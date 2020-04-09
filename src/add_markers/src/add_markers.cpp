#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h> 

//flags and static variables
bool at_pickup = false;
bool at_dropoff = false;
float tol = 0.20;

float pickup_x = 5;
float pickup_y = 4;

float dropoff_x = 5;
float dropoff_y = 0;


float distance(float x1, float y1, float x2, float y2)
{
  float distance = pow((pow(x2-x1, 2)+pow(y2-y1, 2)), 0.5);

  return distance;
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
  float robot_x = odom->pose.pose.position.x;
  float robot_y = odom->pose.pose.position.y;
  //ROS_WARN("x: %f, y: %f", robot_x, robot_y);

  float d_to_pick_up = distance(robot_x, robot_y, pickup_x, pickup_y);
  float d_to_drop_off = distance(robot_x, robot_y, dropoff_x, dropoff_y);
  //ROS_WARN("Distance: %f", d);
  if(d_to_pick_up<tol)
  {
    at_pickup = true;
  }
  if(at_pickup && d_to_drop_off<tol)
  {
    at_dropoff = true;
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom", 10, odomCallback);
  
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  
  while (ros::ok())
  { 
    visualization_msgs::Marker marker;
    //nav_msgs::Odometry odom;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = pickup_x;
    marker.pose.position.y = pickup_y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    if(!at_pickup && !at_dropoff){
      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker.action = visualization_msgs::Marker::ADD;
    }
    else if(at_pickup && !at_dropoff){
      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      ros::Duration(5.0).sleep();
      marker.action = visualization_msgs::Marker::DELETE;
    }
    else if(at_pickup && at_dropoff){
      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker.pose.position.x = dropoff_x;
      marker.pose.position.y = dropoff_y;
      marker.action = visualization_msgs::Marker::ADD;
    }

    marker_pub.publish(marker); 

    //r.sleep();
    //ros::spin();
    ros::spinOnce();
  }
  
  return 0;

}