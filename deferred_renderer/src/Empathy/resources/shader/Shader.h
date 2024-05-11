#pragma once

#include <Empathy/SimpleTypes.h>
#include <string>
#include <vector>

namespace EM {
	enum UniformType : u32 {
		UT_FLOAT = 0x1406,
		UT_VEC2 = 0x8B50,
		UT_VEC3,
		UT_VEC4,
		UT_INT = 0x1404,
		UT_MAT4 = 0x8B5C,
		UT_TEX2D = 0x8B5E
	};

	struct Uniform {
		std::string name;
		UniformType type;
		u32 location;
	};

	class Shader {
	private:
		std::vector<Uniform> m_Uniforms;

		u32 m_ProgramId;

		void loadUniforms();
	public:
		Shader() : m_ProgramId(0)
		{}

		bool Load(const char* file);

		void Bind();

		void Unbind();

		Uniform* getUniform(const char* name);
	};
}