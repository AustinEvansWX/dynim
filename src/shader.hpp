#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace Dynim {

GLuint CreateShaderProgram(string vertex_source_path, string fragment_source_path);
string ReadShaderSource(string path);
GLuint CompileShader(GLenum shader_type, const string &shader_source);
GLuint LinkShaders(vector<GLuint> &shaders);

} // namespace Dynim
