#include "Shader.h"
#include "GL/glew.h"

static GLchar* loadShaderFile(string filePath);
static void printShaderLog(GLuint shader);
static void printProgramLog(GLuint program);

Shader::Shader(string name)
{
	m_name = name;
	m_uid = -1;
	m_vertex = NULL;
	m_fragment = NULL;
}

Shader::Shader(string name, string vertFilePath, string fragFilePath, std::vector<string> attributes, std::vector<string> uniforms)
{
	m_name = name;
	load(vertFilePath, fragFilePath, attributes, uniforms);
}

Shader::~Shader()
{
	m_attributes.clear();
	m_uniforms.clear();
	delete[] m_vertex;
	delete[] m_fragment;
}

void Shader::load(string vertFilePath, string fragFilePath, std::vector<string> attributes, std::vector<string> uniforms)
{
	m_vertex = loadShaderFile(vertFilePath);
	m_fragment = loadShaderFile(fragFilePath);

	setup();
	setupLocations(attributes, uniforms);
}

void Shader::setup()
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
		printShaderLog(vShader);
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
		printShaderLog(fShader);
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
		printProgramLog(pProgram);
		getchar();
	}

	m_uid = pProgram;
}

void Shader::bind() const
{
	glUseProgram(m_uid);
}

void Shader::setupLocations(std::vector<string> custom_attributes, std::vector<string> custom_uniforms)
{
	bind();

	for (uint32_t i = 0; i < custom_attributes.size(); i++)
	{
		m_attributes.emplace(custom_attributes[i], glGetAttribLocation(m_uid, custom_attributes[i].c_str()));
	}
	for (uint32_t j = 0; j < custom_uniforms.size(); j++)
	{
		m_uniforms.emplace(custom_uniforms[j], glGetUniformLocation(m_uid, custom_uniforms[j].c_str()));
	}
}

string Shader::getName() const
{
	return m_name;
}

unsigned int Shader::attribute(string name) const
{
	return m_attributes.at(name);
}

unsigned int Shader::uniform(string name) const
{
	return m_uniforms.at(name);
}

bool Shader::hasAttribute(string name) const
{
	std::unordered_map<string, int>::const_iterator got = m_attributes.find(name);
	if (got == m_attributes.end())
	{
		return false;
	}

	return true;
}

bool Shader::hasUniform(string name) const
{
	std::unordered_map<string, int>::const_iterator got = m_uniforms.find(name);
	if (got == m_uniforms.end())
	{
		return false;
	}

	return true;
}

static GLchar* loadShaderFile(string filePath)
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

static void printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
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

static void printProgramLog(GLuint program)
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


