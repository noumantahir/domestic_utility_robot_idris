#include "std_msgs/Int16.h"
  #include "std_msgs/String.h"
#include "std_msgs/Bool.h"
  #include "geometry_msgs/Twist.h"
  #include "sound_play/sound_play.h"
 
  int inicio = 0;
  int rotate = 0;
  int turn = 0;
  int start = 0;
  int stop = 1;
  float linear_vel = 0.0;
  float angular_vel = 0.0;
  std_msgs::String comando_voz;  
  ros::Publisher follow_it;
  ros::Publisher register_face_pub;
 
  void sleepok(int t, ros::NodeHandle &n)
  {
       if (n.ok())
               sleep(t);
  }
 
  void speech(const std_msgs::String& voz)
  {
  	ros::NodeHandle n;  
        ::comando_voz = voz;
	sound_play::SoundClient voz_robot;
         
        ros::Publisher move_base_pub_=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
      
        std_msgs::Int16 objeto;
        geometry_msgs::Twist mover_base;
             
        if (::comando_voz.data == "timmy")
        {
                inicio = 1;
		ROS_INFO("timmy detected");
                               
        }
     /*   else if (::comando_voz.data == "sleep")
        {
                inicio = 0;
                               
        }
*/
        else if (inicio == 1)
        {
         			if(::comando_voz.data == "follow me"){
					
			//		sleepok(5, n);
					std_msgs::Bool shouldFollow;
					shouldFollow.data = 1;
					follow_it.publish(shouldFollow);
					inicio=0;
					
				}
				else if(::comando_voz.data == "sleep")
				{
					std_msgs::Bool shouldFollow;
					shouldFollow.data = 0;
					follow_it.publish(shouldFollow);
					inicio=0;
					stop=0;
				}
				else if(::comando_voz.data == "register")
				{
					//c.data = 0;
					std_msgs::String registerName;
					registerName.data = "john";
				//	register_face_pub.publish(c);
				}
                                                       
                                                                                                              
        }
  }
     
  int main(int argc, char **argv)
  {
         
        ros::init(argc, argv, "control_voz");  

  	ros::NodeHandle n;  
 
        ros::Subscriber speech_sub_= n.subscribe("/recognizer/output", 1, speech);
       
         
        ros::Publisher move_base_pub_=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

	follow_it=n.advertise<std_msgs::Bool>("follow_command", 1);

	register_face_pub = n.advertise<std_msgs::String>("register_face", 1);
       
        ros::Rate loop_rate(10);
       
        geometry_msgs::Twist mover_base;
       
        sound_play::SoundClient voz_robot;
       
        sleepok(4, n); 
     
       
        while (ros::ok())
        {              
                        mover_base.linear.x = ::linear_vel;
                        mover_base.angular.z = ::angular_vel;
                       
                        move_base_pub_.publish(mover_base);
                       
                        if (::comando_voz.data == "timmy" && ::start == 0)
                        {
                                voz_robot.say("yes sir");
				ROS_INFO("Ass slam aly kum sir. How can I be of assistance");
                               
                                sleepok(4, n);
                               
                                ::start = 1;
                                ::stop = 0;
                        }
                        else if (::comando_voz.data == "sleep" && ::stop == 0)
                        {
                                voz_robot.say("Good Bye Sir");
				ROS_INFO("Good Bye Sir");
                               std_msgs::Bool shouldFollow;
				shouldFollow.data = 0;
				follow_it.publish(shouldFollow);
					

                                sleepok(4, n);
                               
                                ::stop = 1;
                                ::start = 0;
                        }                      
                       
                        ros::spinOnce();
       
                        loop_rate.sleep();                     
       
                }                    
       
        ros::spin();  
 
        return 0;
  }
