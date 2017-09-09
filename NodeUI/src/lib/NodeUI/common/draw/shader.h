#pragma once

/*

[Shader�N���X] �p����:ShaderBase
	[��`]
		[default vertex shader]
			in vec2 pos; // ���͒��_�z��
			in vec4 col; // ���͐F�z��
			out vec4 fragmentColor; // �o�͐F�z��
			uniform vec2 reso; // �𑜓x
			vec2 position; // ���_���W�ꎞ����p

			void main(){
				position = pos; // �ꎞ���
				// Window���W -> OpenGL���W �ɕϊ�
				position.x /= reso.x;
				position.y /= reso.y;
				position.y = 1.0 - position.y;
				position *= 2.0;
				position -= vec2(1.0, 1.0);
				// ���_�z��o��
				gl_Position.xyz = vec3(position, 0.0);
				gl_Position.w = 1.0;
				// �F�z��o��
				fragmentColor = col;
			}

		[default fragment shader]
			in vec4 fragmentColor; // ���͐F�z��
			out vec4 color; // �o�͐F�z��
			void main(){
				color = fragmentColor;
			}

	[�֐�]
		static bool init()
			�������֐�
			DrawBase�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
			�ق��̊֐����g�p����O�ɂ��̊֐������s����
			�߂�l:����:0,�G���[:1

		static bool loop()
			���t���[�����s���ׂ��֐�
			DrawBase�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
			�߂�l:����:0,�G���[:1

		static PROGRAM createVSProgram(SHADER_CODE vs)
			�o�[�e�b�N�X�V�F�[�_�̃R���p�C���֐�
			�t���O�����g�V�F�[�_�̓f�t�H���g�̂��̂��g��
			����1:�o�[�e�b�N�X�V�F�[�_�̃\�[�X�R�[�h
			�߂�l:�v���O����ID
			�R���p�C���Ɏ��s�����ꍇ��0���Ԃ�

		static PROGRAM createFSProgram(SHADER_CODE fs)
			�t���O�����g�V�F�[�_�R���p�C���֐�
			�o�[�e�b�N�X�V�F�[�_�̓f�t�H���g�̂��̂��g��
			����1:�t���O�����g�V�F�[�_�̃\�[�X�R�[�h
			�߂�l:�v���O����ID
			�R���p�C���Ɏ��s�����ꍇ��0���Ԃ�

		static inline PROGRAM getNormalProgram()
			�f�t�H���g�̃V�F�[�_�̃v���O����ID���擾����
			�߂�l:�v���O����ID

		static inline GLuint getVertexLocation()
			���݂̃V�F�[�_�̒��_�z�񂪊i�[�����ϐ��̃��P�[�V����ID�擾
			�߂�l:���݂̃V�F�[�_�̒��_�z�񂪊i�[�����ϐ��̃��P�[�V����ID

		static inline GLuint getColorLocation()
			���݂̃V�F�[�_�̐F�z�񂪊i�[�����ϐ��̃��P�[�V����ID�擾
			�߂�l:���݂̃V�F�[�_�̐F�z�񂪊i�[�����ϐ��̃��P�[�V����ID

		static bool setProgram(PROGRAM p)
			�V�F�[�_���w�肷��
			����1:�v���O����ID
			�߂�l:����:0,�G���[:1

*/

#include "shader_base.h"

namespace nui{
	class Shader : public ShaderBase {
	private:
		static SHADER_CODE version_code_string; // �V�F�[�_�̐擪�ɂ���o�[�W�����w��R�[�h
		static SHADER_CODE normal_vs; // �m�[�}���o�[�e�b�N�X�V�F�[�_�̃R�[�h
		static SHADER_CODE normal_fs; // �m�[�}���t���O�����g�V�F�[�_�̃R�[�h
		static GLuint pos_s; // shader��pos�ϐ���ID
		static GLuint col_s; // shader��col�ϐ���ID
		static GLuint reso_s; // shader��reso�ϐ���ID
		static PROGRAM normal; // �m�[�}���v���O�����̃v���O����ID
	public:
		static bool init() {
			version_code_string =
				"#version " +
				std::to_string(GLManagement::getVersion().major) +
				std::to_string(GLManagement::getVersion().minor) +
				std::to_string(0) +
				" core\n";
			normal_vs =
				version_code_string +
				R"(
in vec2 pos;
in vec4 col;
out vec4 fragmentColor;
uniform vec2 reso;
vec2 position;

void main(){
	position = pos;
	position.x /= reso.x;
	position.y /= reso.y;
	position.y = 1.0 - position.y;
	position *= 2.0;
	position -= vec2(1.0, 1.0);
	gl_Position.xyz = vec3(position, 0.0);
	gl_Position.w = 1.0;
	fragmentColor = col;
}
				)";
			normal_fs =
				version_code_string +
				R"(
in vec4 fragmentColor;
out vec4 color;
void main(){
	color = fragmentColor;
}
				)";
			normal = createProgram(normal_vs, normal_fs);
			if (normal == GL_FALSE) return 1;
			return 0;
		}
		static bool loop() {
			// �����v���O�������w�肳��Ă��Ȃ���Ώ����I��
			if (now == GL_FALSE) return 0;
			// �V�F�[�_�ɉ𑜓x�𑗐M
			if (Window::getResizeFlag()) {
				glUniform2f(reso_s, (float)Window::getSize().x, (float)Window::getSize().y);
			}
			return 0;
		}
		// �o�[�e�b�N�X�V�F�[�_�̂ݐ���
		static PROGRAM createVSProgram(SHADER_CODE vs) {
			return createProgram(vs, normal_fs);
		}
		// �t���O�����g�V�F�[�_�̂ݎw��
		static PROGRAM createFSProgram(SHADER_CODE fs) {
			return createProgram(normal_vs, fs);
		}
		static inline PROGRAM getNormalProgram() { return normal; }
		static inline GLuint getVertexLocation() { return pos_s; }
		static inline GLuint getColorLocation() { return col_s; }
		static bool setProgram(PROGRAM p) {
			if (ShaderBase::setProgram(p)) return 1;
			pos_s = glGetAttribLocation(now, "pos");
			col_s = glGetAttribLocation(now, "col");
			reso_s = glGetUniformLocation(now, "reso");
			glUniform2f(reso_s, (float)Window::getSize().x, (float)Window::getSize().y);
			return 0;
		}
	};
	Shader::SHADER_CODE Shader::version_code_string;
	Shader::SHADER_CODE Shader::normal_vs;
	Shader::SHADER_CODE Shader::normal_fs;
	GLuint Shader::pos_s;
	GLuint Shader::col_s;
	GLuint Shader::reso_s;
	Shader::PROGRAM Shader::normal;
}