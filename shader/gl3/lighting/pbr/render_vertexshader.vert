#version 330 core

{$DEFINITIONS}

// standard layouts
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_UV1;

// normal mapping
layout (location = 4) in vec3 a_Tangent;
layout (location = 5) in vec3 a_Bitangent;

// instanced rendering
layout (location = 6) in mat4 a_ModelMatrix;

// effect colors
layout (location = 10) in vec4 a_EffectColorMul;
layout (location = 11) in vec4 a_EffectColorAdd;

// render groups
layout (location = 12) in vec3 a_Origin;

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

out vec4 v_EffectColorMul;
out vec4 v_EffectColorAdd;

uniform mat4 u_ViewProjectionMatrix;

#if defined(HAVE_FOLIAGE)
	uniform float time;
	uniform float speed;
	uniform float amplitudeDefault;
	uniform float amplitudeMax;
#elif defined(HAVE_TREE)
	uniform float time;
	uniform float speed;
#endif

{$FUNCTIONS}

void main() {
	mat4 _modelMatrix = a_ModelMatrix;
	#if defined(HAVE_TREE)
		mat4 shaderTransformMatrix = createTreeTransformMatrix(
			a_Origin,
			a_Position * mat3(_modelMatrix),
			vec3(_modelMatrix[3][0], _modelMatrix[3][1], _modelMatrix[3][2])
		);
	#elif defined(HAVE_FOLIAGE)
		mat4 shaderTransformMatrix = createFoliageTransformMatrix(
			a_Origin,
			a_Position * mat3(_modelMatrix),
			vec3(_modelMatrix[3][0], _modelMatrix[3][1], _modelMatrix[3][2]));
	#else
		mat4 shaderTransformMatrix = mat4(1.0);
	#endif

	vec4 position = a_ModelMatrix * shaderTransformMatrix * vec4(a_Position, 1.0);
	v_Position = vec3(position.xyz) / position.w;

	mat4 normalMatrix = mat4(transpose(inverse(mat3(a_ModelMatrix * shaderTransformMatrix))));

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

	#if defined(HAS_VERTEX_COLOR_VEC3)
		v_Color = a_Color;
	#endif
	#if defined(HAS_VERTEX_COLOR_VEC4)
		v_Color = a_Color;
	#endif

	v_EffectColorMul = a_EffectColorMul;
	v_EffectColorAdd = a_EffectColorAdd;

	gl_Position = u_ViewProjectionMatrix * position;
}
