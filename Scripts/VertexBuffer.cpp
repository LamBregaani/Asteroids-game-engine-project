#include "Headers/VertexBuffer.h"
using GameEngine::VertexBuffer;

#include "Headers/Renderer.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
   //Create a buffer
   unsigned int buffer;
   //Generate a buffer
   GLCall(glGenBuffers(1, &m_RendererID));
   //Bind the buffer
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
   //Create the buffer data
   GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer()
{
   GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
   //Bind the buffer
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}
void VertexBuffer::Unbind() const
{
   //Unbind the buffer
   GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}