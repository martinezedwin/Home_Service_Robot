#!/bin/sh

#turtlebot
xterm  -e " cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../world/U-World.world " &
sleep 5

#amcl
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../map/U-turn.yaml " & 
sleep 5

#rviz
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep  10

#pick_objects
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; rosrun pick_objects pick_objects "
sleep 5
