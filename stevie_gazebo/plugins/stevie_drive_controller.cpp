#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

namespace gazebo
{

  class StevieDrivePlugin : public ModelPlugin
  {
  public:
    void Load(physics::ModelPtr _parent, sdf::ElementPtr){
      ros::init(0, NULL, "Stevie Drive Plugin");
      this->rosnode = new ros::NodeHandle();

      this->model = _parent;

      this->rightWheelJoint = this->model->GetJoint("wheel_right_joint");
      this->leftWheelJoint = this->model->GetJoint("wheel_left_joint");

      this->sub = this->rosnode->subscribe("/stevie/cmd_vel", 10, &StevieDrivePlugin::ROSCallback, this);

      this->updateConnection = event::Events::ConnectWorldUpdateStart(boost::bind(&StevieDrivePlugin::OnUpdate, this));
    }

    void ROSCallback(const geometry_msgs::Twist::ConstPtr& msg){
      this->target_vel.linear.x = msg.linerar.x
      this->target_vel.linear.y = msg.linerar.y
      this->target_vel.linear.z = msg.linerar.z
      this->target_vel.angular.x = msg.angular.x
      this->target_vel.angular.y = msg.angular.y
      this->target_vel.angular.z = msg.angular.z
    }

    void OnUpdate(){

    }

  private:
    ros::NodeHandle rosnode;
    JointPtr rightWheelJoint, leftWheelJoint;
    ros::Subscriber sub;
    geometry_msgs::Twist target_vel;
  };

  GZ_REGISTER_MODEL_PLUGIN(StevieDrivePlugin)
}
