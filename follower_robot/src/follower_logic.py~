#!/usr/bin/env python
import rospy, os, sys
from geometry_msgs.msg import Twist
from std_msgs.msg import String
from std_msgs.msg import Int8
from std_msgs.msg import Bool
import math
import tf
from tf.transformations import euler_from_quaternion


userID = 0
isCallibrated = False
shouldFollow = False
voice_pub = 0
vel_pub = 0



def callibration_id_callback(data):
	rospy.loginfo('Interrupt Received for user ID ' + str(data.data))
	global userID
	global shouldFollow
	global voice_pub
	voice_pub.publish('callibration complete')
	if shouldFollow:
		voice_pub.publish('i m now following you')
	else:
		voice_pub.publish('please say follow me ')
	userID = data.data




def user_lost_id_callback(data):
	global userID
	global shouldFollow
	global vel_pub
	if userID == data.data:
		rospy.loginfo('User Lost Abandoning Follow')
		global voice_pub
		userID = 0
		iscallibrated = False
		twist = Twist()
		twist.linear.x = 0
		twist.linear.y = 0		
		vel_pub.publish(twist)
		voice_pub.publish('i m unable to identify you')	
		if shouldFollow:
			shouldFollow = False
			voice_pub.publish('giving up on following')



 
def follow_command_callback(data):
	rospy.loginfo('Interrupt Received for follow_command ' + str(data.data))
	global shouldFollow
	global voice_pub
	global vel_pub
	shouldFollow = data.data
	if shouldFollow:
		if not isCallibrated:
			voice_pub.publish('please stand in psi pose for callibration')
		else:
			voice_pub.publish('i m now following you')
	else:
		
		twist = Twist()
		twist.linear.x = 0
		twist.linear.y = 0		
		vel_pub.publish(twist)
		voice_pub.publish('i would not follow you now')


def publishVelocity(twist):
		#should robot follow or not
		if not shouldFollow:
			twist.linear.x = 0
			twist.linear.y = 0
		
		#inverting velocities
		tmp = Twist()
		tmp.linear.y = twist.linear.x
		tmp.linear.x = twist.linear.y

		vel_pub.publish(tmp)



def getVelocity(trans):
		global shouldFollow
		global vel_pub

		rospy.loginfo('publishing velocity')

		#conversion to millimeters
		pose_x = trans[0]*1000
		pose_x = pose_x
		pose_y = trans[1]*1000
		pose_y = pose_y

		#printing data on terminal
        	print 'Torso X: ',int(pose_x) ,"  Torso Y: ", int(pose_y)
		twist = Twist()

		#setting velocity parameters
		robot_radius = 150.0
		vel = 100.0
		kd = 3.0
		kp = 0.005
		target_dist = 1000.0

		

		#velocity control
		ep = pose_x - target_dist
		vel = (kp * ep) * vel
		radius = ((pose_x * pose_x) + (pose_y * pose_y)) / (2 * pose_y)
		factor = (robot_radius * kd)/radius

		if vel > 350:
			vel = 350
		elif vel < 50 and vel > 0:
			vel = 50
		elif vel > -50 and vel < 0:
			vel = -50
		elif vel < -350:
			vel = -350


		#setting rest band
		if ep < 100 and ep > -100:
			vel = 0

		#setting left and right wheel velocities
		if vel > 0:
			if pose_y == 0:
				vel_left = vel
				velright = vel
			else:			
				vel_left = vel * (1 - factor ) 
				vel_right = vel * (1 + factor)

		elif vel < 0:
			if pose_y == 0:
				vel_left = vel
				velright = vel
			else:
				vel_left = vel * (1 + factor ) #reverse drive circle inverses
				vel_right = vel * (1 - factor)
		else:
		#spinning robot to catch user
			lim = 60
			if pose_y > lim:
				vel_right = 50
				vel_left = -50
			elif pose_y < -lim:
				vel_right = -50
				vel_left = 50
			if pose_y <= lim and pose_y >= -lim:
				vel_right = 0
				vel_left = 0

		#setting upper and lower speed limits
		if vel_left > 400:
			vel_left = 400
		elif vel_left < 50 and vel_left > 0:
			vel_left = 50
		elif vel_left < -400:
			vel_left = -400
		elif vel_left > -50 and vel_left < 0:
			vel_left = -50

		if vel_right > 400:
			vel_right = 400
		elif vel_right < 50 and vel_right > 0:
			vel_right = 50
		elif vel_right < 0 and vel_right > -50:
			vel_right = -50
		elif vel_right < -400:
			vel_right = -400
		
		print 'Speed L: ',int(vel_left) ,"  Speed R: ", int(vel_right)
		#feeding speed to message
		twist.linear.x = int(vel_left)
		twist.linear.y = int(vel_right)

		return twist
	
 
def startFollower():
	global voice_pub
	global vel_pub
	global isCallibrated
	rospy.init_node('follower_logic', anonymous=True)
	vel_pub = rospy.Publisher('robot_velocity', Twist, queue_size=10)
	voice_pub = rospy.Publisher('robot_voice', String, queue_size=10)
	rospy.Subscriber("callibration_ID", Int8, callibration_id_callback)
	rospy.Subscriber("lostUser_ID", Int8, user_lost_id_callback)
	rospy.Subscriber("follow_command", Bool, follow_command_callback)
	rate = rospy.Rate(10.0)
	#The tf package provides an implementation of a tf.TransformListener to help make the task of receiving transforms easier. 
	listener = tf.TransformListener()
	#Here, we create a tf.TransformListener object. Once the listener is created, it starts receiving tf transformations over the wire, and buffers them for up to 10 seconds. 

	rospy.loginfo('Node Initialised...')
    	while not rospy.is_shutdown():
		torsoID = 'torso_' + str(userID)
		try:
			(trans, rot) = listener.lookupTransform('openni_depth_frame', torsoID, rospy.Time(0)) 

			#1.We want the transform from this frame ...
			#2... to this frame.
			#3.The time at which we want to transform. Providing rospy.Time(0) will just get us the latest available transform. 
			
			#rospy.loginfo("checking for torso")

		except (tf.LookupException, tf.ConnectivityException):
			#rospy.loginfo('unable to get torso tf value')
	
            		continue
		
		#updated callibration flag
		isCallibrated = True
		vel = getVelocity(trans)
	
		publishVelocity(vel)
		rate.sleep()

         
 
if __name__ == '__main__':
	
	startFollower()
