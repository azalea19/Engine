#include "Types.h"

class AffineTransformable
{
private:
  vec3 m_translation;
  quat m_orientation;
  vec3 m_scale;

public:


  vec3 const& GetTranslation() const;
  void SetTranslation(vec3 const& translation);
  void SetTranslation(float x, float y, float z);

  quat const& GetOrientation() const;
  void SetOrientation(quat const& orientation);
  void SetOrientation(float yaw, float pitch, float roll);
  float GetYaw() const;
  void SetYaw(float yaw);
  float GetPitch() const;
  void SetPitch(float pitch);
  float GetRoll() const;
  void SetRoll(float roll);

  vec3 const& GetScale() const;
  void SetScale(vec3 const& scale);

  mat4 GetTransform() const;
  void SetTransform(mat4 const& transform);
  void SetTransform(vec3 const& translation, quat const& orientation, vec3 const& scale);

};
