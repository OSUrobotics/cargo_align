#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class JoystickTeleop
{
public:
	JoystickTeleop();

private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	
	ros::NodeHandle nh_;

	int linear_x, linear_y, angular_;
	double l_scale_, a_scale_;
	ros::Publisher vel_pub_;
	ros::Subscriber joy_sub_;
	
};


JoystickTeleop::JoystickTeleop():
	linear_x(1),
	linear_y(0),
	angular_(2),
	a_scale_(2),
	l_scale_(2)
{

	nh_.param("axis_linear_x", linear_x, linear_x);
	nh_.param("axis_linear_y", linear_y, linear_y);
	nh_.param("axis_angular", angular_, angular_);
	nh_.param("scale_angular", a_scale_, a_scale_);
	nh_.param("scale_linear", l_scale_, l_scale_);


	vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);


	joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &JoystickTeleop::joyCallback, this);

}

void JoystickTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	geometry_msgs::Twist vel;

	vel.angular.x = 0;
	vel.angular.y = 0;
	vel.angular.z = a_scale_ * joy->axes[angular_];
	vel.linear.x = l_scale_ * joy->axes[linear_x];
	vel.linear.y = l_scale_ * joy->axes[linear_y];
	vel.linear.z = 0;
	vel_pub_.publish(vel);
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "joystick_teleop");
	JoystickTeleop joystick_teleop;

	ros::spin();
}