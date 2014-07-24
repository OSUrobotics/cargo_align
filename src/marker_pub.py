#!/usr/bin/env python

# ROS data types
from visualization_msgs.msg import Marker
# ROS Libraries
import rospy
import tf


if __name__ == '__main__':
	rospy.init_node('marker_pub')
	pub = rospy.Publisher("visualization_marker", Marker)
	rate = rospy.Rate(10)

	while not rospy.is_shutdown():
		mark 						= Marker()
		mark.header.frame_id 		= "base_link"
		mark.header.stamp 			= rospy.Time.now()
		mark.ns 					= "my_namespace"
		mark.id 					= 0
		mark.type 					= 1
		mark.action 				= 0
		mark.pose.position.x		= 4
		mark.pose.position.y 		= 0
		mark.pose.position.z 		= 0
		mark.pose.orientation.x 	= 0.0
		mark.pose.orientation.y 	= 0.0
		mark.pose.orientation.z 	= 0.0
		mark.pose.orientation.w 	= 1.0
		mark.scale.x 				= 0.1
		mark.scale.y 				= 9.14
		mark.scale.z 				= 0.1
		mark.color.a 				= 1.0
		mark.color.r 				= 0.0
		mark.color.g 				= 1.0
		mark.color.b 				= 0.0

		pub.publish(mark)
		rate.sleep()