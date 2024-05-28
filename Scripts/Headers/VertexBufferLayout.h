#ifndef ASTEROIDS_VERTEX_BUFFER_lAYOUT_H
#define ASTEROIDS_VERTEX_BUFFER_lAYOUT_H

#include <vector>
using std::vector;

#include <stdexcept>
using std::runtime_error;

#include "GL/glew.h"

#include "Renderer.h"

namespace GameEngine
{
   struct VertexBufferElement
   {
      unsigned int type;
      unsigned int count;

      unsigned char normalized;

      static unsigned int GetSizeOfType(unsigned int type)
      {
         switch (type)
         {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
         }
         ASSERT(false);
         return 0;
      }

      VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized)
         :type(type),
         count(count),
         normalized(normalized)
      {}
   };


   class VertexBufferLayout
   {
   private:
      vector<VertexBufferElement> m_elements;

      unsigned int m_stride;

   public:

      VertexBufferLayout()
         : m_stride(0) {}

      template<typename T>
      void Push(unsigned int count)
      {
         runtime_error(false);
      }

      template<>
      void Push<float>(unsigned int count)
      {
         m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
         m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
      }

      template<>
      void Push<unsigned int>(unsigned int count)
      {
         m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
         m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
      }

      template<>
      void Push<unsigned char>(unsigned int count)
      {
         m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
         m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
      }

      inline const vector<VertexBufferElement> GetElements() const { return m_elements; }

      inline unsigned int GetStride() const { return m_stride; }
   };
}


#endif
