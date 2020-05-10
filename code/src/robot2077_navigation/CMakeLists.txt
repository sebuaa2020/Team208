cmake_minimum_required(VERSION 2.8.3)
project(robot2077_navigation)
find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	message_generation
	controller_manager
	gazebo_ros
	move_base
	map_server
	amcl
	gmapping
	dwa_local_planner
	robot2077_basic
)

catkin_package(
   CATKIN_DEPENDS
  message_runtime urdf xacro
)



include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_executable(navi_move_trans
  src/navi_move_trans.cpp
)
add_dependencies(navi_move_trans ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(navi_move_trans
  ${catkin_LIBRARIES}
)
