/*
 * Author: Denis Tananaev
 * Date: 01.06.2020
 */


#include "ros/ros.h"


int main(int argc, char **argv){
   ros::init(argc, argv, "dynamic_objects");

   while (ros::ok()){
       std::cout<<"I am working!"<<"\n";

  }


  return 0;
}