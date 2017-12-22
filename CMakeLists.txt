cmake_minimum_required(VERSION 2.8.3)
project(sync_data)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  message_filters
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES lesson_simple_parameters
   CATKIN_DEPENDS roscpp std_msgs sensor_msgs message_filters
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(synchronizer_node src/synchronizer_node.cpp)
target_link_libraries(synchronizer_node ${catkin_LIBRARIES})