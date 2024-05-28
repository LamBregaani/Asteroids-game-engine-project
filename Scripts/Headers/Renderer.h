#ifndef ASTEROIDS_Renderer_H
#define ASTEROIDS_Renderer_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>



#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using std::cout;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
   while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
   while (GLenum error = glGetError())
   {
      cout << "[OpenGL Error (" << error << "):" << function << " " << file << ":" << line << std::endl;
      return false;
   }

   return true;
}

struct ShaderProgramSource
{
   std::string VertexSource;
   std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath);

//Complie a shader using source string and GL shader type
static unsigned int CompileShader(const std::string& source, unsigned int type);

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

int Render(void);
#endif
