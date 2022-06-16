#pragma once

namespace Dynim {

class Mesh {
public:
  Mesh();
  Mesh(const void *vertices, unsigned int size, const unsigned int *indices, unsigned int count);
  ~Mesh();

  void Bind() const;
  void Unbind() const;
  inline unsigned int GetCount() const { return m_Count; }

private:
  unsigned int m_Vao;
  unsigned int m_Vbo;
  unsigned int m_Ibo;
  unsigned int m_Count = 0;
};

} // namespace Dynim
