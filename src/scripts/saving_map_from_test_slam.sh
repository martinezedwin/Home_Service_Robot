#!/bin/bash
cd $(pwd)/../..; source devel/setup.bash ; rosrun map_server map_saver -f $(pwd)/src/map/U-turn
