cmake_minimum_required(VERSION 2.8.3)
project(dynamic_objects)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
MESSAGE("FALGS: ${CMAKE_CXX_FLAGS}")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS  roscpp roslib image_transport sensor_msgs geometry_msgs visualization_msgs tf2)
find_package(PNG)
find_package(Boost 1.45.0 COMPONENTS filesystem) 
catkin_package()


include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_executable(dynamic_objects src/dynamic_objects_app.cpp src/data_loader.cpp src/data_streamer.cpp src/helpers.cpp)

target_link_libraries(dynamic_objects ${catkin_LIBRARIES} ${PNG_LIBRARIES}  ${Boost_LIBRARIES} )


