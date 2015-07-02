#!/usr/bin/env python
import rospy, os, sys
from std_msgs.msg import String
from std_msgs.msg import Bool
from geometry_msgs.msg import Twist

vel_pub = 0
setup_pub = 0

def android_data_callback(str_msg):
        if str_msg.data == "f": 
		driveDirect(200, 200)
        if str_msg.data == "b": 
		driveDirect(-200, -200)
        if str_msg.data == "s": 
		driveDirect(0, 0)
        if str_msg.data == "r":
		driveDirect(200, -200)
        if str_msg.data == "l":
		driveDirect(-200, 200);
	if str_msg.data == "a":
		global setup_pub
		print 'restarting roomba'
		mbool = Bool()
		setup_pub.publish(mbool)
		
		

def driveDirect(left, right):
	global vel_pub
	vel = Twist()
	vel.linear.x = right
	vel.linear.y = left
	vel_pub.publish(vel)

if __name__ == '__main__':
	global vel_pub
	global setup_pub
	rospy.init_node('android_interface_node', anonymous=True)
	rospy.Subscriber("recognizer/output", String, android_data_callback)
	vel_pub = rospy.Publisher('robot_velocity', Twist, queue_size=10)
	setup_pub = rospy.Publisher('setup_roomba_command', Bool, queue_size=10)
	rospy.spin()
