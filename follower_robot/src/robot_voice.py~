#!/usr/bin/env python
import rospy, os, sys
from sound_play.msg import SoundRequest
from sound_play.libsoundplay import SoundClient
from std_msgs.msg import String

soundhandle = 0

def sleep(t):
	try:
		rospy.sleep(t)
	except:
		pass

def voice_play_callback(data):
	global soundhandle
	s = soundhandle.voiceSound(data.data)
	s.play()
	sleep(2)
	
	

if __name__ == '__main__':
	rospy.init_node('robot_voice_node', anonymous=True)
	rospy.Subscriber("robot_voice", String, voice_play_callback)
	global soundhandle
	soundhandle = SoundClient()
	rospy.sleep(1)
	soundhandle.stopAll()
	soundhandle.play(SoundRequest.NEEDS_PLUGGING)
	sleep(1)
	global soundhandle
	s = soundhandle.voiceSound('Ass slam aly kum sir. How can I be of assistance')
	s.play()
	sleep(3)
	rospy.spin()
