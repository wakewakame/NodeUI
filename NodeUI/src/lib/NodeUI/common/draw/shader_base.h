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

#include "../gl/gl.h"
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
			ERROR_MESSAGE();
		};
	protected:
		static PROGRAM now; // ���ݎw�肳��Ă���v���O������ID
		static ERROR_MESSAGE error; // �G���[����p
		static SHADER createShader(SHADER_CODE code, GLenum Type);
		static void deleteShader(SHADER s);
	public:
		static PROGRAM createProgram(SHADER_CODE vs, SHADER_CODE fs);
		static bool setProgram(PROGRAM p);
		static inline PROGRAM getNowProgram();
		static inline ERROR_MESSAGE getError();
	};
}