#include "UberShader.h"
#include "GL/glew.h"

static GLchar* LoadShaderFile(string filePath);
static void PrintShaderLog(GLuint shader);
static void PrintProgramLog(GLuint program);

UberShader::UberShader(string name)
{
	m_name = name;
	m_uid = -1;
	m_vertex = NULL;
	m_fragment = NULL;
}

UberShader::UberShader(string name, string vertFilePath, string fragFilePath)
{
	m_name = name;
	Load(vertFilePath, fragFilePath);
}

UberShader::~UberShader()
{
	m_attributes.clear();
	m_uniforms.clear();
	delete[] m_vertex;
	delete[] m_fragment;
}

void UberShader::Load(string vertFilePath, string fragFilePath)
{
	m_vertex = LoadShaderFile(vertFilePath);
	m_fragment = LoadShaderFile(fragFilePath);

	Setup();
}

void UberShader::Setup()
{
	if (m_vertex == NULL || m_fragment == NULL)
	{
		printf("Unable to load shader %s", m_name.c_str());
	}

	unsigned int pProgram;
	pProgram = glCreateProgram();

	GLint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &m_vertex, NULL);
	glCompileShader(vShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (!vShaderCompiled)
	{
		printf("Unable to compile vertex shader.");
		PrintShaderLog(vShader);
		getchar();
	}
	GLint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fShader, 1, &m_fragment, NULL);
	glCompileShader(fShader);
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (!fShaderCompiled)
	{
		printf("Unable to compile fragment shader.");
		PrintShaderLog(fShader);
		getchar();
	}

	glAttachShader(pProgram, vShader);
	glAttachShader(pProgram, fShader);

	glLinkProgram(pProgram);
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(pProgram, GL_LINK_STATUS, &programSuccess);
	if (!programSuccess)
	{
		printf("Error linking program %d", pProgram);
		PrintProgramLog(pProgram);
		getchar();
	}

	m_uid = pProgram;
}

void UberShader::Bind() const
{
	glUseProgram(m_uid);
}

unsigned int UberShader::GetAttributeID(string name) const
{
	return m_attributes.at(name);
}

unsigned int UberShader::GetUniformID(string name) const
{
	return m_uniforms.at(name);
}

bool UberShader::HasAttribute(string name) const
{
	std::unordered_map<string, int>::const_iterator got = m_attributes.find(name);
	if (got == m_attributes.end())
	{
		return false;
	}

	return true;
}

bool UberShader::HasUniform(string name) const
{
	std::unordered_map<string, int>::const_iterator got = m_uniforms.find(name);
	if (got == m_uniforms.end())
	{
		return false;
	}

	return true;
}

void UberShader::BindAttribute(GLuint bufferID, string name, GLenum type, GLuint size, GLuint stride)
{
	GLuint attributeID = GetAttributeID(name);
	glEnableVertexAttribArray(attributeID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glVertexAttribPointer(attributeID, size, type, GL_FALSE, stride, NULL);
}

void UberShader::UnbindAttribute(string name)
{
	glDisableVertexAttribArray(GetAttributeID(name));
}

void UberShader::BindTexture(GLuint textureID, string samplerName)
{
	//Set Texture unit 0 as the current texture unit
	glActiveTexture(GL_TEXTURE0);

	//bind our texture to the current texture unit
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Set our sampler to sample the current texure unit
	TransmitUniform(samplerName, 0);
}

static GLchar* LoadShaderFile(string filePath)
{
	int fileLength;
	FILE* shader;
	fopen_s(&shader, filePath.c_str(), "rb");

	if (shader == NULL)
	{
		printf("Could not open file %s", filePath.c_str());
	}
	//Seek to the end of the file
	fseek(shader, 0, SEEK_END);
	//ftell to return position of file pointer
	fileLength = ftell(shader);
	//Seek back to start of file
	fseek(shader, 0, SEEK_SET);
	char* data = new char[fileLength + 1];
	fread(data, 1, fileLength, shader);
	data[fileLength] = NULL;

	return data;
}

static void PrintShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//UberShader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}

static void PrintProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}



