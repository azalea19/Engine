#ifndef IShader_h__
#define IShader_h__

class IShader
{

public:

  /// <summary>
  /// Binds this instance.
  /// </summary>
  virtual void Bind() const = 0;

  /// <summary>
  /// Gets the name.
  /// </summary>
  /// <returns></returns>
  virtual string const& GetName() const = 0;

  /// <summary>
  /// Determines whether the specified shader has attribute.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>
  ///   <c>true</c> if the specified name has attribute; otherwise, <c>false</c>.
  /// </returns>
  virtual bool HasAttribute(string const& name) const = 0;

  /// <summary>
  /// Determines whether the specified shader has uniform.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns>
  ///   <c>true</c> if the specified name has uniform; otherwise, <c>false</c>.
  /// </returns>
  virtual bool HasUniform(string const& name) const = 0;

  /// <summary>
  /// Returns the specified attribute ID
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns></returns>
  virtual unsigned int Attribute(string const& name) const = 0;

  /// <summary>
  /// Returns the specified uniform ID.
  /// </summary>
  /// <param name="name">The name.</param>
  /// <returns></returns>
  virtual unsigned int Uniform(string const& name) const = 0;

 
  /// <summary>
  /// Transmits the uniform.
  /// </summary>
  /// <param name="uniformID">The uniform identifier.</param>
  /// <param name="value">The value.</param>
  virtual void TransmitUniform(string const& uniformID, float const& value) const = 0;

  /// <summary>
  /// Transmits the uniform.
  /// </summary>
  /// <param name="uniformID">The uniform identifier.</param>
  /// <param name="value">The value.</param>
  virtual void TransmitUniform(string const& uniformID, int const& value) const = 0;

  /// <summary>
  /// Transmits the uniform.
  /// </summary>
  /// <param name="uniformID">The uniform identifier.</param>
  /// <param name="vector">The vector.</param>
  virtual void TransmitUniform(string const& uniformID, vec2 const& vector) const = 0;

  /// <summary>
  /// Transmits the uniform.
  /// </summary>
  /// <param name="uniformID">The uniform identifier.</param>
  /// <param name="vector">The vector.</param>
  virtual void TransmitUniform(string const& uniformID, vec3 const& vector) const = 0;

  /// <summary>
  /// Transmits the uniform array.
  /// </summary>
  /// <param name="uniformID">The uniform identifier.</param>
  /// <param name="matrix">The matrix.</param>
  /// <param name="count">The count.</param>
  virtual void TransmitUniformArray(string const& uniformID, mat4* matrix, int count) const = 0;

  /// <summary>
  /// Transmits the uniform.
  /// </summary>
  /// <param name="uniformID">The uniform identifier.</param>
  /// <param name="matrix">The matrix.</param>
  virtual void TransmitUniform(string const& uniformID, mat4 const& matrix) const = 0;

}; 


#endif // IShader_h__
