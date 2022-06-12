#version 410

void main() {
  int line_width = 2;

  if (mod(gl_FragCoord.x + 1, 60) <= line_width || mod(gl_FragCoord.y + 1, 60) <= line_width) {
    gl_FragColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);
  }

  if (abs(gl_FragCoord.x - 300) <= line_width - 1) {
    gl_FragColor = vec4(0.0f, 0.35f, 0.65f, 1.0f);
  }

  if (abs(gl_FragCoord.y - 300) <= line_width - 1) {
    gl_FragColor = vec4(0.63f, 0.18f, 0.18f, 1.0f);
  }
}
