#ifndef AffineTransformable_h__
#define AffineTransformable_h__

#include "Types.h"

class AffineTransformable
{
private:
  vec3 m_translation;
  float m_yaw;
  float m_pitch;
  float m_roll;
  vec3 m_scale;

public:
  AffineTransformable();
  AffineTransformable(vec3 const& translation, float yaw, float pitch, float roll, vec3 const& scale);

  vec3 const& GetTranslation() const;
  void SetTranslation(vec3 const& translation);
  void SetTranslation(float x, float y, float z);

  mat4 const& GetOrientation() const;
  void SetOrientation(float degYaw, float degPitch, float degRoll);
  float GetYaw() const;
  void SetYaw(float degYaw);
  float GetPitch() const;
  void SetPitch(float degPitch);
  float GetRoll() const;
  void SetRoll(float degRoll);

  vec3 const& GetScale() const;
  void SetScale(vec3 const& scale);

  mat4 GetTransform() const;
  void SetTransform(mat4 const& transform);
  void SetTransform(vec3 const& translation, float yaw, float pitch, float roll, vec3 const& scale);

};
#endif // AffineTransformable_h__
