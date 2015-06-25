
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"


std_msgs::String raw_word;
std_msgs::String command;
std::stringstream command_raw;
int listen_count = 0;
int hibe=1;



void chatterCallback(const std_msgs::String& voz)
{
  ::raw_word = voz;
  
  
  if (::raw_word.data == "sleep"){

		ROS_INFO("Good Bye Sir");
		listen_count=0;	
	}
  else {  


	  if (::raw_word.data == "timmy")
		{
		       
			ROS_INFO("Ass slam aly kum sir. How can I be of assistance");
		        listen_count=5;      
			hibe=1;         
		}
		else if (::raw_word.data == "sleep")
		{
		        
			ROS_INFO("Good Bye Sir");
			listen_count=0;	
		                       
		}
		else{
			
			if(listen_count>0){
				if(::raw_word.data == "move forward"){
					ROS_INFO("Aye AYe Sir, Moving Forward");
					::command_raw << "01";
				}
				else if(::raw_word.data == "move backward"){
					ROS_INFO("Aye AYe Sir, Moving Backward");
					::command_raw << "02";
				}
				else if(::raw_word.data == "turn right"){
					ROS_INFO("Turning Left Now");
					::command_raw << "03";
				}
				else if(::raw_word.data == "turn left"){
					ROS_INFO("Turning Right Now");
					::command_raw << "04";
				}
				else if(::raw_word.data == "speed up"){
					ROS_INFO("Increasing Speed");
					::command_raw << "05";
				}
				else if(::raw_word.data == "slow down"){
					ROS_INFO("Decreasing Speed");
					::command_raw << "06";
				}
				else if(::raw_word.data == "rotate right"){
					ROS_INFO("Rotating Clockwise");
					::command_raw << "07";
				}
				else if(::raw_word.data == "rotate left"){
					ROS_INFO("Rotating AntiClockwise");
					command_raw << "08";
				}
				else if(::raw_word.data == "stop"){
					ROS_INFO("Applying Brakes, and Halted.");
					::command_raw << "09";
				}
				else if(::raw_word.data == "what are you"){
					ROS_INFO("I am ROS Based robot, a part of idris system.");
					::command_raw << "00";
				}
				else if(::raw_word.data == "who are you"){
					ROS_INFO("I am Timmy.");
					::command_raw << "00";
				}
				else if(::raw_word.data == "how are you"){
					ROS_INFO("I am fine and working.");
					::command_raw << "00";
				}
				else if(::raw_word.data == "follow me"){
					ROS_INFO("Sure, Let me cllibrate first...Make the sign please...Callibrated...Lead the way.");
					::command_raw << "10";
				}
				else{
				//	ROS_INFO("Sorry , Can you say it again?");
					::command_raw << "00";
					listen_count--;			
				}// listen count k ander wala else ends here
			} // <-- listen count >0 wala if ends here
			else{
				listen_count--;
				if(listen_count<0)
				{
					if(hibe>0){
					ROS_INFO("I am hibernating now. Call me if you need me.");
					::command_raw << "99";
					hibe=0;
					}
					else{
					
					}

				}
			} // <-- listen count >0 wala else ends here
					
		}

   } // <-- Sleep wala else ends here
	
  
}

int main(int argc, char **argv)
{
  

  ros::init(argc, argv, "control_timmy");

  ros::NodeHandle n;

  ros::init(argc, argv, "captain");
 
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("captain", 1000);
  ros::Rate loop_rate(10);
  command.data = command_raw.str(); 
  
  ROS_INFO("PUBLISHING : %s", command.data.c_str());

  chatter_pub.publish(command);

 // %Tag(SUBSCRIBER)%
  ros::Subscriber speech_subs = n.subscribe("/recognizer/output", 1000, chatterCallback);
// %EndTag(SUBSCRIBER)%

  
  
  ros::spin();


  return 0;
}
// %EndTag(FULLTEXT)%

