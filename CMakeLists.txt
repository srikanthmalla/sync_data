cmake_minimum_required(VERSION 2.8.3)
project(sync_data)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  message_filters
  pcl_conversions
  pcl_ros
  laser_geometry
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( PCL REQUIRED )
include_directories(${PCL_INCLUDE_DIRS} )
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

catkin_package(
   INCLUDE_DIRS include 
   CATKIN_DEPENDS roscpp sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_executable(synchronizer_node src/synchronizer_node.cpp src/Sync.cpp src/Filewriter.cpp)
target_link_libraries(synchronizer_node ${catkin_LIBRARIES})