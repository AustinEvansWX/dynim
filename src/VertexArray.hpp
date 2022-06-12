namespace Dynim {

class VertexArray {
public:
  VertexArray(const void *vertices, unsigned int size, const unsigned int *indices, unsigned int count);
  ~VertexArray();

  void Bind() const;
  void Unbind() const;
  inline unsigned int GetCount() const { return m_Count; }

private:
  unsigned int m_Id;
  unsigned int m_Count;
};

} // namespace Dynim
