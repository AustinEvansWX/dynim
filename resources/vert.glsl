#version 410

layout(location = 0) in vec4 position;

uniform vec2 transform;

void main() {
  gl_Position = vec4(position.xy + transform, 0.0f, 1.0f);
}
