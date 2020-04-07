#!/bin/sh

#turtlebot
xterm  -e " cd $(pwd)/../..; source devel/setup.bash ; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../world/U-World.world " &
sleep 5

#amcl
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../map/U-turn.yaml " & 
sleep 5

#rviz
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; rosrun rviz rviz -d $(pwd)/../RvizConfig/add_marker.rviz " &
sleep  5

#add markers
xterm  -e  " cd $(pwd)/../.. ; source devel/setup.bash ; rosrun add_markers add_markers "
sleep 5
