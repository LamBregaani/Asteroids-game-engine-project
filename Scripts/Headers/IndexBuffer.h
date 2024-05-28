#ifndef ASTEROIDS_INDEX_BUFFER_H
#define ASTEROIDS_INDEX_BUFFER_H

namespace GameEngine
{
   class IndexBuffer
   {
      unsigned int m_RendererID;
      unsigned int m_count;

   public:
      IndexBuffer(const unsigned int *data, unsigned int count);
      ~IndexBuffer();

      void Bind() const;
      void Unbind() const;

      inline unsigned int GetCount() const
      {
         return m_count;
      }
   };
}

#endif
