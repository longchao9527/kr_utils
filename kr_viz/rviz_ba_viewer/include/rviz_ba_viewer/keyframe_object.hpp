/*
 * keyframe_object.hpp
 *
 * Copyright (c) 2014 Gareth Cross, Chao Qu. All rights reserved.
 */
#ifndef KEYFRAME_OBJECT_HPP
#define KEYFRAME_OBJECT_HPP

#include <OGRE/OgreTexture.h>
#include <OGRE/OgreMaterial.h>
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreVector4.h>
#include <OGRE/OgreQuaternion.h>

#include <opencv2/opencv.hpp>

#include <image_geometry/pinhole_camera_model.h>

namespace Ogre {
class SceneManager;
class SceneNode;
class ManualObject;
}

class KeyFrameObject {
public:
  typedef std::shared_ptr<KeyFrameObject> Ptr;
  
  KeyFrameObject(Ogre::SceneManager * scene_manager, int id);
  virtual ~KeyFrameObject();
  
  /**
   * @brief ID of the key-frame.
   * @return 
   */
  const int& id() const { return id_; }
  
  /**
   * @brief OGRE SceneNode to which all camera geometry is attached.
   * @return 
   */
  Ogre::SceneNode* sceneNode() const { return scene_node_; }
  
  /**
   * @brief Set camera image.
   * @param image
   */
  void setImage(const cv::Mat& image);
  
  /**
   * @brief Set camera information.
   * @param model
   * @param width
   * @param height
   */
  void setCameraModel(const image_geometry::PinholeCameraModel& model,
                      int width, int height);
  
  /**
   * @brief Set pose in R3.
   * @param position
   * @param orientation
   */
  void setPose(const Ogre::Vector3& position,
               const Ogre::Quaternion& orientation);
  
  /**
   * @brief Set color of the frustum.
   * @param color
   */
  void setColor(const Ogre::Vector4& color);
  
  /**
   * @brief Enable or disable image rendering.
   * @param imageEnabled
   */
  void setImageEnabled(bool imageEnabled);
  
  /**
   * @brief Create objects for rendering. Only call from update().
   */
  void createGeometry();
  
private:
  
  const int id_;
  cv::Mat image_;
  image_geometry::PinholeCameraModel cam_model_;
  float width_{0}, height_{0};
  Ogre::Vector4 color_{1,1,1,1};
  bool imageEnabled_{true};
  bool dirty_{true};
  
  /// Ogre objects
  Ogre::SceneManager * scene_manager_;
  Ogre::SceneNode    * scene_node_;
  Ogre::ManualObject * frustum_object_;
  Ogre::ManualObject * plane_object_;
  Ogre::TexturePtr     texture_;
  Ogre::MaterialPtr    frustum_material_;
  Ogre::MaterialPtr    material_;
};

#endif // KEYFRAME_OBJECT_HPP
