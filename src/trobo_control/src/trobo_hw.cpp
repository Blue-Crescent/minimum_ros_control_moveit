#include <ros/ros.h>
#include <ros/package.h>
#include <angles/angles.h>
#include <trobo_control/trobo_hw.h>
#include <iostream> // for debug
#include <math.h>


TRobo::TRobo()
{
  // connect and register the joint state interface
  hardware_interface::JointStateHandle state_handle_1("joint1", &pos_[0], &vel_[0], &eff_[0]);
  jnt_state_interface.registerHandle(state_handle_1);

  // connect and register the joint state interface
  hardware_interface::JointStateHandle state_handle_2("joint2", &pos_[1], &vel_[1], &eff_[1]);
  jnt_state_interface.registerHandle(state_handle_2);
  registerInterface(&jnt_state_interface);

  // connect and register the joint position interface
  hardware_interface::JointHandle pos_handle_1(jnt_state_interface.getHandle("joint1"), &cmd_[0]);
  jnt_pos_interface.registerHandle(pos_handle_1);
  
  // connect and register the joint position interface
  hardware_interface::JointHandle pos_handle_2(jnt_state_interface.getHandle("joint2"), &cmd_[1]);
  jnt_pos_interface.registerHandle(pos_handle_2);
  registerInterface(&jnt_pos_interface);
}

void TRobo::read(ros::Time time, ros::Duration period)
{
}

void TRobo::write(ros::Time time, ros::Duration period)
{
 
  // Real Robot functionality coding here...
  // below code is simulating real robot delay.	
  pos_[0] = pos_[0] + 0.0001* (cmd_[0] - pos_[0]);
  pos_[1] = pos_[1] + 0.0001* (cmd_[1] - pos_[1]);
  ROS_DEBUG_STREAM("Debug:" << pos_[0] << cmd_[0]);
  // Dump cmd_ from MoveIt!, current simulated real robot pos_.
  printf("%f, %f, %f, %f\n",pos_[0],cmd_[0],pos_[1],cmd_[1]);
}

