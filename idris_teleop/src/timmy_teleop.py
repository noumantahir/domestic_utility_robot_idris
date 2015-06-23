#!/usr/bin/env python
import rospy, os, sys
from geometry_msgs.msg import Twist
import math

vel_pub = 0


def turtle_teleop_callback(data):
	global vel_pub
	rospy.loginfo('Interrupt Received for teleop')
	speed = 200
	twist = Twist()
	if data.linear.x == 2.0:
		twist.linear.x = speed
		twist.linear.y = speed
	if data.linear.x == -2.0:
		twist.linear.x = -speed
		twist.linear.y = -speed
	if data.angular.z == 2.0:
		twist.linear.x = -speed
		twist.linear.y = speed
	if data.angular.z == -2.0:
		twist.linear.x = speed
		twist.linear.y = -speed	

	rospy.loginfo(twist.linear.x)	
	rospy.loginfo(twist.linear.y)	

	vel_pub.publish(twist)

def initTeleop():
	global vel_pub
	rospy.init_node('timmy_teleop', anonymous=True)
	vel_pub = rospy.Publisher('robot_velocity', Twist, queue_size=10)
	rospy.Subscriber("/turtle1/cmd_vel", Twist, turtle_teleop_callback)
	rospy.loginfo('Teleop Node Initialised...')
	rospy.spin()


 
if __name__ == '__main__':
	initTeleop()
