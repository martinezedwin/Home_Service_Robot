#!/bin/sh
xterm  -e " cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../world/U-World.world " &
sleep 5
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../map/U-turn.yaml " & 
sleep 5
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_rviz_launchers view_navigation.launch "
sleep 5 
