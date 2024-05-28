#include "Headers/Renderer.h"

#include "Headers/VertexBuffer.h"
using GameEngine::VertexBuffer;
#include "Headers/IndexBuffer.h"
using GameEngine::IndexBuffer;

#include "Headers/VertexArray.h"
using GameEngine::VertexArray;
using GameEngine::VertexBufferLayout;

#include <GL/glew.h>
#include <GLFW/glfw3.h>



#include <fstream>
using std::ifstream;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cout;

static ShaderProgramSource ParseShader(const string& filePath)
{
   ifstream stream(filePath);

   enum class ShaderType
   {
      None = -1,

      Vertex = 0,

      Fragment = 1
   };

   string line;
   stringstream ss[2];

   ShaderType type = ShaderType::None;

   while (getline(stream, line))
   {
      if (line.find("#shader") != std::string::npos)
      {
         //Set mode to vertex
         if (line.find("vertex") != std::string::npos)
         {
            type = ShaderType::Vertex;
         }
         //Set mode to fragment
         else if (line.find("fragment") != std::string::npos)
         {
            type = ShaderType::Fragment;
         }

      }
      else
      {
         ss[(int)type] << line << '\n';
      }
   }

   return { ss[0].str(), ss[1].str() };
}

//Complie a shader using source string and GL shader type
static unsigned int CompileShader(const std::string& source, unsigned int type)
{
   //Reference to the comppiled shader
   unsigned int id = glCreateShader(type);

   //Pointer for the shader source code
   const char* src = source.c_str();

   //Store the source code of the shader ot the id
   GLCall(glShaderSource(id, 1, &src, nullptr));
   //Compile the source code for the shader
   GLCall(glCompileShader(id));

   //Store the result
   int result;
   //Get the reuslt of the shader compilation
   GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

   //Check if the shader compiled properly, if not run the code inside the if statement
   if (result == GL_FALSE)
   {
      //Store the length of the shader compile log
      int length;

      //Get the length of the shader compilation log
      GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

      //Create a char and allocate memory on the stack based on length
      char* message = (char*)malloc(length * sizeof(char));

      //Get the message error from the info log
      GLCall(glGetShaderInfoLog(id, length, &length, message));

      //Display an error message
      cout << "Failed to compile " <<
         (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
         << "shader!" << std::endl;
      cout << message << std::endl;

      //Delete the failed shader
      GLCall(glDeleteShader(id));

      return 0;
   }

   return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
   //The complete shader
   unsigned int program = glCreateProgram();
   //Compile the vertex shader
   unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
   //Compile the fragment shader
   unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

   //Attach the compiled vertex and fragment shaders to the program value
   GLCall(glAttachShader(program, vs));
   GLCall(glAttachShader(program, fs));

   //Link the two shaders to the respective types
   GLCall(glLinkProgram(program));

   GLCall(glValidateProgram(program));

   //Delete the two shaders source codes as they are no longer needed
   GLCall(glDeleteShader(vs));
   GLCall(glDeleteShader(fs));

   return program;
}

int Draw(void)
{
   GLFWwindow* window;

   /* Initialize the library */
   if (!glfwInit())
      return -1;

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   /* Create a windowed mode window and its OpenGL context */
   window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   /* Make the window's context current */
   glfwMakeContextCurrent(window);

   glfwSwapInterval(1);

   //Check if GLEW is initillailized
   if (glewInit() != GLEW_OK)
   {
      cout << "Error; glewInit not initillaized" << std::endl;
   }

   cout << glGetString(GL_VERSION) << std::endl;

   //Set the positions for our vertex position attribute
   float positions[] =
   {
       -0.5f, -0.5f,
       0.5f, -0.5f,
       0.5f, 0.5f,
       -0.5f, 0.5f
   };

   unsigned int indices[] = {
       0, 1, 2,
       2, 3, 0
   };

   unsigned int vao;
   GLCall(glGenVertexArrays(1, &vao));
   GLCall(glBindVertexArray(vao));


   VertexArray va;

   VertexBuffer vb(positions, 4 * 2 * sizeof(float));

   VertexBufferLayout layout;
   layout.Push<float>(2);
   va.AddBuffer(vb, layout);

   IndexBuffer ib(indices, 6);

   ShaderProgramSource source = ParseShader("Res/Shaders/Basic.shader");

   cout << source.VertexSource << std::endl;
   cout << source.FragmentSource << std::endl;

   unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

   GLCall(glUseProgram(shader));

   int location = glGetUniformLocation(shader, "u_Color");
   ASSERT(location != -1);
   glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);


   GLCall(glBindVertexArray(0));
   GLCall(glUseProgram(0));
   //Bind the buffer
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
   //Bind the buffer
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

   float r = 0.0f, increment = 0.05f;

   /* Loop until the user closes the window */
   while (!glfwWindowShouldClose(window))
   {
      /* Render here */
      GLCall(glClear(GL_COLOR_BUFFER_BIT));

      GLCall(glUseProgram(shader));

      va.Bind();
      //Bind the buffer
      ib.Bind();

      //glDrawArrays(GL_TRIANGLES, 0, 3);

      glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
      GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

      if (r > 1.0f)
         increment = -0.05f;
      else if(r < 0.0f)
         increment = 0.05f;

      r += increment;

      /* Swap front and back buffers */
      GLCall(glfwSwapBuffers(window));

      /* Poll for and process events */
      GLCall(glfwPollEvents());
   }

   glDeleteProgram(shader);

   glfwTerminate();
   return 0;
}