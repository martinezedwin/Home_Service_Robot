#!/bin/sh
xterm  -e " cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../world/U-World.world " &
sleep 5
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_gazebo gmapping_demo.launch " & 
sleep 5
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5 
xterm  -e " cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_teleop keyboard_teleop.launch "
sleep 2