#ifndef AffineTransformable_h__
#define AffineTransformable_h__

#include "Types.h"

/**
* @file AffineTransformable.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with an affine transformable object.
*
*/



class AffineTransformable
{
private:

  /// <summary>
  /// The translation
  /// </summary>
  vec3 m_translation;

  /// <summary>
  /// The yaw
  /// </summary>
  float m_yaw;

  /// <summary>
  /// The pitch
  /// </summary>
  float m_pitch;

  /// <summary>
  /// The roll
  /// </summary>
  float m_roll;

  /// <summary>
  /// The scale
  /// </summary>
  vec3 m_scale;

public:

  /// <summary>
  /// Initializes a new instance of the <see cref="AffineTransformable"/> class.
  /// </summary>
  AffineTransformable();

  /// <summary>
  /// Initializes a new instance of the <see cref="AffineTransformable"/> class.
  /// </summary>
  /// <param name="translation">The translation.</param>
  /// <param name="yaw">The yaw.</param>
  /// <param name="pitch">The pitch.</param>
  /// <param name="roll">The roll.</param>
  /// <param name="scale">The scale.</param>
  AffineTransformable(vec3 const& translation, float yaw, float pitch, float roll, vec3 const& scale);

  /// <summary>
  /// Gets the translation.
  /// </summary>
  /// <returns>vec3</returns>
  vec3 const& GetTranslation() const;

  /// <summary>
  /// Sets the translation.
  /// </summary>
  /// <param name="translation">The translation.</param>
  void SetTranslation(vec3 const& translation);

  /// <summary>
  /// Sets the translation.
  /// </summary>
  /// <param name="x">The x.</param>
  /// <param name="y">The y.</param>
  /// <param name="z">The z.</param>
  void SetTranslation(float x, float y, float z);

  /// <summary>
  /// Gets the orientation.
  /// </summary>
  /// <returns>mat4</returns>
  mat4 const& GetOrientation() const;

  /// <summary>
  /// Sets the orientation.
  /// </summary>
  /// <param name="degYaw">The yaw in degrees.</param>
  /// <param name="degPitch">The pitch in degrees.</param>
  /// <param name="degRoll">The roll in degrees.</param>
  void SetOrientation(float degYaw, float degPitch, float degRoll);

  /// <summary>
  /// Gets the yaw.
  /// </summary>
  /// <returns>float</returns>
  float GetYaw() const;

  /// <summary>
  /// Sets the yaw.
  /// </summary>
  /// <param name="degYaw">The yaw in degrees.</param>
  void SetYaw(float degYaw);

  /// <summary>
  /// Gets the pitch.
  /// </summary>
  /// <returns>float</returns>
  float GetPitch() const;

  /// <summary>
  /// Sets the pitch.
  /// </summary>
  /// <param name="degPitch">The pitch in degrees.</param>
  void SetPitch(float degPitch);

  /// <summary>
  /// Gets the roll.
  /// </summary>
  /// <returns>float</returns>
  float GetRoll() const;

  /// <summary>
  /// Sets the roll.
  /// </summary>
  /// <param name="degRoll">The deg roll.</param>
  void SetRoll(float degRoll);

  /// <summary>
  /// Gets the scale.
  /// </summary>
  /// <returns>vec3</returns>
  vec3 const& GetScale() const;
  
  /// <summary>
  /// Sets the scale.
  /// </summary>
  /// <param name="scale">The scale.</param>
  void SetScale(vec3 const& scale);

  /// <summary>
  /// Gets the transform.
  /// </summary>
  /// <returns></returns>
  mat4 GetTransform() const;
  
  /// <summary>
  /// Sets the transform.
  /// </summary>
  /// <param name="transform">The transform.</param>
  void SetTransform(mat4 const& transform);

  /// <summary>
  /// Sets the transform.
  /// </summary>
  /// <param name="translation">The translation.</param>
  /// <param name="yaw">The yaw.</param>
  /// <param name="pitch">The pitch.</param>
  /// <param name="roll">The roll.</param>
  /// <param name="scale">The scale.</param>
  void SetTransform(vec3 const& translation, float yaw, float pitch, float roll, vec3 const& scale);

};
#endif // AffineTransformable_h__
