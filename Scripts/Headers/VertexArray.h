#ifndef ASTEROIDS_VERTEX_ARRAY_H
#define ASTEROIDS_VERTEX_ARRAY_H

#include "VertexBuffer.h"

#include "VertexBufferLayout.h"

namespace GameEngine
{
   class VertexArray
   {
   private:
      unsigned int m_rendererID;
   public:
      VertexArray();
      ~VertexArray();

      void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

      void Bind() const;

      void Unbind() const;
   };
}


#endif