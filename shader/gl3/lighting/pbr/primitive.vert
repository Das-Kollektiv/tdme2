#version 330 core

{$DEFINITIONS}

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_UV1;
layout (location = 4) in vec3 a_Tangent;
layout (location = 5) in vec3 a_Bitangent;

out vec3 v_Position;
out mat3 v_TBN;

#ifdef HAS_UV_SET2
attribute vec2 a_UV2;
#endif

out vec2 v_UVCoord1;
out vec2 v_UVCoord2;

#ifdef HAS_VERTEX_COLOR_VEC3
attribute vec3 a_Color;
out vec3 v_Color;
#endif

#ifdef HAS_VERTEX_COLOR_VEC4
attribute vec4 a_Color;
out vec4 v_Color;
#endif

uniform mat4 u_ViewProjectionMatrix;
layout (location = 6) in mat4 u_ModelMatrix;

void main()
{
    vec4 pos = u_ModelMatrix * vec4(a_Position, 1.0);
    v_Position = vec3(pos.xyz) / pos.w;

    mat4 normalMatrix = mat4(transpose(inverse(mat3(u_ModelMatrix))));

    vec4 tangent = vec4(a_Tangent, 0.0);
    vec3 normalW = normalize(vec3(normalMatrix * vec4(a_Normal, 0.0)));
    vec3 tangentW = normalize(vec3(normalMatrix * vec4(a_Tangent, 0.0)));
    vec3 bitangentW = normalize(vec3(normalMatrix * vec4(a_Bitangent, 0.0)));
    v_TBN = mat3(tangentW, bitangentW, normalW);

    v_UVCoord1 = a_UV1;
    v_UVCoord2 = vec2(0.0, 0.0);

    #ifdef HAS_UV_SET2
    v_UVCoord2 = a_UV2;
    #endif

    #if defined(HAS_VERTEX_COLOR_VEC3) || defined(HAS_VERTEX_COLOR_VEC4)
    v_Color = a_Color;
    #endif

    gl_Position = u_ViewProjectionMatrix * pos;
}
