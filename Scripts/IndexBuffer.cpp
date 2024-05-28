#include "Headers/IndexBuffer.h"
using GameEngine::IndexBuffer;

#include "Headers/Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
   :m_count(count)
{

   ASSERT(sizeof(unsigned int) == sizeof(GLuint))

   //Create a buffer
   unsigned int buffer;
   //Generate a buffer
   GLCall(glGenBuffers(1, &m_RendererID));
   //Bind the buffer
   GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
   //Create the buffer data
   GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer()
{
   GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
   //Bind the buffer
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void IndexBuffer::Unbind() const
{
   //Unbind the buffer
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}