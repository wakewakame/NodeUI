/*

[ShaderBase�N���X]
[��`]
using PROGRAM = GLuint
using SHADER = GLuint
using SHADER_CODE = std::string
struct ERROR {
std::string vertex; // �o�[�e�b�N�X�V�F�[�_�G���[���e
std::string fragment; // �t���O�����g�V�F�[�_�G���[���e
std::string link; // �����N�G���[���e
}

[�֐�]
PROGRAM createProgram(SHADER_CODE vs, SHADER_CODE fs)
�V�F�[�_�R���p�C���֐�
����1:�o�[�e�b�N�X�V�F�[�_�̃\�[�X�R�[�h
����2:�t���O�����g�V�F�[�_�̃\�[�X�R�[�h
�߂�l:�v���O����ID
�R���p�C���Ɏ��s�����ꍇ��0���Ԃ�

bool setProgram(PROGRAM p)
�V�F�[�_���w�肷��
����1:�v���O����ID
�߂�l:����:0,�G���[:1

PROGRAM getNowProgram()
���ݎw�肳��Ă���V�F�[�_���擾����
�߂�l:���ݎw�肳��Ă���v���O����ID

ERROR getError()
�G���[���e���擾����

*/

#pragma once

#include <string>
#include <vector>

namespace nui {
	class ShaderBase {
	public:
		using PROGRAM = GLuint;
		using SHADER = GLuint;
		using SHADER_CODE = std::string;
		struct ERROR_MESSAGE {
			std::string vertex;
			std::string fragment;
			std::string link;
			ERROR_MESSAGE() {
				vertex = "";
				fragment = "";
				link = "";
			}
		};
	protected:
		static PROGRAM now; // ���ݎw�肳��Ă���v���O������ID
		static ERROR_MESSAGE error; // �G���[����p
		static SHADER createShader(SHADER_CODE code, GLenum Type) {
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
		static void deleteShader(SHADER s) {
			glDeleteShader(s);
		}
	public:
		static PROGRAM createProgram(SHADER_CODE vs, SHADER_CODE fs) {
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
		static bool setProgram(PROGRAM p) {
			glUseProgram(p);
			now = p;
			return 0;
		}
		static inline PROGRAM getNowProgram() { return now; }
		static inline ERROR_MESSAGE getError() { return error; }
	};
	ShaderBase::PROGRAM ShaderBase::now;
	ShaderBase::ERROR_MESSAGE ShaderBase::error;
}