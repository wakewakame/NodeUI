#include "shader_base.h"

namespace nui {
	ShaderBase::ERROR_MESSAGE::ERROR_MESSAGE() {
			vertex = "";
			fragment = "";
			link = "";
		}
	ShaderBase::SHADER ShaderBase::createShader(SHADER_CODE code, GLenum Type) {
		// �V�F�[�_�̐���
		GLuint ShaderID = glCreateShader(Type);
		// �V�F�[�_�̃R���p�C��
		char const *SourcePointer = code.c_str();
		glShaderSource(ShaderID, 1, &SourcePointer, NULL);
		glCompileShader(ShaderID);
		// �G���[�`�F�b�N
		GLint Result = GL_FALSE;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
		if (Result == GL_FALSE) {
			int InfoLogLength;
			glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			std::vector<char> ErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ErrorMessage[0]);
			switch (Type) {
			case GL_VERTEX_SHADER:
				error.vertex = std::string(ErrorMessage.data());
				break;
			case GL_FRAGMENT_SHADER:
				error.fragment = std::string(ErrorMessage.data());
				break;
			}
			return GL_FALSE;
		}
		// �V�F�[�_ID�o��
		return ShaderID;
	}
	void ShaderBase::deleteShader(SHADER s) {
		glDeleteShader(s);
	}
	ShaderBase::PROGRAM ShaderBase::createProgram(SHADER_CODE vs, SHADER_CODE fs) {
		// �V�F�[�_�̃R���p�C��
		SHADER vs_id = createShader(vs, GL_VERTEX_SHADER);
		SHADER fs_id = createShader(fs, GL_FRAGMENT_SHADER);
		if (vs_id == GL_FALSE || fs_id == GL_FALSE) return GL_FALSE;
		// �v���O�����̐���
		PROGRAM ProgramID = glCreateProgram();
		glAttachShader(ProgramID, vs_id);
		glAttachShader(ProgramID, fs_id);
		glLinkProgram(ProgramID);
		// �V�F�[�_�j��
		deleteShader(vs_id);
		deleteShader(fs_id);
		// �G���[�`�F�b�N
		GLint Result = GL_FALSE;
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		if (Result == GL_FALSE) {
			int InfoLogLength;
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			std::vector<char> ErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ErrorMessage[0]);
			error.link = std::string(ErrorMessage.data());
			return GL_FALSE;
		}
		// �v���O����ID�o��
		return ProgramID;
	}
	bool ShaderBase::setProgram(PROGRAM p) {
		glUseProgram(p);
		now = p;
		return 0;
	}
	inline ShaderBase::PROGRAM ShaderBase::getNowProgram() { return now; }
	inline ShaderBase::ERROR_MESSAGE ShaderBase::getError() { return error; }
	ShaderBase::PROGRAM ShaderBase::now;
	ShaderBase::ERROR_MESSAGE ShaderBase::error;
}