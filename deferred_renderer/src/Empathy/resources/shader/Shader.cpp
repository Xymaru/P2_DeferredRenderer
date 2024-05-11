#include "Shader.h"

#include <glad/glad.h>

#include <Empathy/Debug.h>
#include <Empathy/filesystem/FileSystem.h>

namespace EM {
    void Shader::loadUniforms()
    {
        i32 size;
        u32 type;

        const i32 buf_size = 16;
        char name[buf_size];
        i32 name_len;

        i32 u_count;

        glGetProgramiv(m_ProgramId, GL_ACTIVE_UNIFORMS, &u_count);

        Uniform uniform;

        for (i32 i = 0; i < u_count; i++) {
            glGetActiveUniform(m_ProgramId, (u32)i, buf_size, &name_len, &size, &type, name);

            uniform.name = name;
            uniform.type = (UniformType)type;
            uniform.location = glGetUniformLocation(m_ProgramId, name);

            m_Uniforms.emplace_back(uniform);
        }
    }

    bool Shader::Load(const char* file)
    {
        EM::Memory shader_mem = EM::FileSystem::ReadAll(file);

        if (shader_mem.IsEmpty()) {
            return false;
        }

        const char* version = "#version 430\n";
        const char* vertexDefine = "#define VERTEX_SHADER\n";
        const char* fragmentDefine = "#define FRAGMENT_SHADER\n";

        const char* vertexShaderSource[] = {
            version,
            vertexDefine,
            shader_mem.getBlock()
        };

        const i32 vertexShaderLengths[] = {
            (i32)strlen(version),
            (i32)strlen(vertexDefine),
            (i32)shader_mem.size()
        };

        const char* fragmentShaderSource[] = {
            version,
            fragmentDefine,
            shader_mem.getBlock()
        };

        const i32 fragmentShaderLengths[] = {
            (i32)strlen(version),
            (i32)strlen(fragmentDefine),
            (i32)shader_mem.size()
        };

        i32 success = 0;
        const int infoLogSize = 256;
        char infoLog[infoLogSize];
        i32 infoSize = 0;

        u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, ARRAY_COUNT(vertexShaderSource), vertexShaderSource, vertexShaderLengths);
        glCompileShader(vertex_shader);

        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_shader, infoLogSize, &infoSize, infoLog);
            EM_ERROR("Compile vertex shader at [{0}] failed: {1}", file, infoLog);
            return false;
        }

        u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, ARRAY_COUNT(fragmentShaderSource), fragmentShaderSource, fragmentShaderLengths);
        glCompileShader(fragment_shader);

        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader, infoLogSize, &infoSize, infoLog);
            EM_ERROR("Compile fragment shader at [{0}] failed: {1}", file, infoLog);
            return false;
        }

        m_ProgramId = glCreateProgram();
        glAttachShader(m_ProgramId, vertex_shader);
        glAttachShader(m_ProgramId, fragment_shader);
        glLinkProgram(m_ProgramId);

        glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ProgramId, infoLogSize, &infoSize, infoLog);
            EM_ERROR("Link program at [{0}] failed: {1}", file, infoLog);
            return false;
        }

        glDetachShader(m_ProgramId, vertex_shader);
        glDetachShader(m_ProgramId, fragment_shader);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        loadUniforms();

        return true;
    }

    void Shader::Bind()
    {
        glUseProgram(m_ProgramId);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    Uniform* Shader::getUniform(const char* name) {
        for (size_t i = 0; i < m_Uniforms.size(); i++) {
            if (m_Uniforms[i].name == name) {
                return &m_Uniforms[i];
            }
        }

        return nullptr;
    }
}