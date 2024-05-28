#ifndef ASTEROIDS_VERTEX_BUFFER_H
#define ASTEROIDS_VERTEX_BUFFER_H

namespace GameEngine
{
   class VertexBuffer
   {
      unsigned int m_RendererID;

   public:
      VertexBuffer(const void *data, unsigned int size);
      ~VertexBuffer();

      void Bind() const;
      void Unbind() const;
   };
}

#endif