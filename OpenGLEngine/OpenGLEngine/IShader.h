#ifndef IShader_h__
#define IShader_h__

class IShader
{

public:

  virtual void Bind() const = 0;
  virtual string const& GetName() const = 0;

  virtual bool HasAttribute(string const& name) const = 0;

  virtual bool HasUniform(string const& name) const = 0;

  virtual unsigned int Attribute(string const& name) const = 0;

  virtual unsigned int Uniform(string const& name) const = 0;

 
  virtual void TransmitUniform(string const& uniformID, float const& value) const = 0;

  virtual void TransmitUniform(string const& uniformID, int const& value) const = 0;

  virtual void TransmitUniform(string const& uniformID, vec2 const& vector) const = 0;

  virtual void TransmitUniform(string const& uniformID, vec3 const& vector) const = 0;

  virtual void TransmitUniformArray(string const& uniformID, mat4* matrix, int count) const = 0;

  virtual void TransmitUniform(string const& uniformID, mat4 const& matrix) const = 0;

}; 


#endif // IShader_h__
