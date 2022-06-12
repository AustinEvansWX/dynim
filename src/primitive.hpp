#include <GL/gl.h>
#include <vector>

namespace Dynim {

class Primitive {
public:
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  unsigned int vao;
  unsigned int vbo;
  unsigned int ibo;

  void Initialize();
  void Draw();
};

class Triangle : public Primitive {
public:
  Triangle();
};

class Quad : public Primitive {
public:
  Quad();
};

} // namespace Dynim
