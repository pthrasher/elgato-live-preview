#ifndef _FRAME_RENDERER_SHADER_H_
#define _FRAME_RENDERER_SHADER_H_

static const char* YUV420P_VERTEX_SHADER = ""
    "uniform mat4 mvp;\n"
    "attribute vec2 pos;\n"
    "attribute vec2 uv;\n"
    "varying vec2 texcoord;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = mvp * vec4(pos, 0.0, 1.0);\n"
    "    texcoord = uv;\n"
    "}\n";

static const char* YUV420P_FRAGMENT_SHADER = ""
    "uniform sampler2D yTexture;\n"
    "uniform sampler2D uTexture;\n"
    "uniform sampler2D vTexture;\n"
    "varying vec2 texcoord;\n"
    "\n"
    "float stepW = 1.0 / 1920.0;\n"
    "float stepH = 1.0 / 1080.0;\n"
    "\n"
    "vec4 getRGB(vec2 uv) {\n"
    "    float y = texture2D(yTexture, uv).r;\n"
    "    float u = texture2D(uTexture, uv).r;\n"
    "    float v = texture2D(vTexture, uv).r;\n"
    "    u = -0.436 + 0.872*u;\n"
    "    v = -0.615 + 1.23*v;\n"
    "    float r = y + 1.28033 * v;\n"
    "    float g = y - 0.21482 * u - 0.38059 * v;\n"
    "    float b = y + 2.12798 * u;\n"
    "    return vec4(r, g, b, 0.0);\n"
    "}\n"
    "\n"
    "void main() {\n"
    "    vec2 offset[5];\n"
    "    offset[0] = vec2(texcoord.x, texcoord.y - stepH);\n"
    "    offset[1] = vec2(texcoord.x - stepW, texcoord.y);\n"
    "    offset[2] = vec2(texcoord.x, texcoord.y);\n"
    "    offset[3] = vec2(texcoord.x + stepW, texcoord.y);\n"
    "    offset[4] = vec2(texcoord.x, texcoord.y + stepH);\n"
    "\n"
    "    float kernel[5];\n"
    "    kernel[0] = -0.75;\n"
    "    kernel[1] = -0.75;\n"
    "    kernel[2] = 4.;\n"
    "    kernel[3] = -0.75;\n"
    "    kernel[4] = -0.75;\n"
    "\n"
    "    vec4 sum = vec4(0.0);\n"
    "    int i;\n"
    "    for (i = 0; i < 5; i++) {\n"
    "        vec4 color = getRGB(offset[i]);\n"
    "        sum += color * kernel[i];\n"
    "    }\n"
    "\n"
    "    gl_FragColor = sum;\n"
    "}\n";

#endif