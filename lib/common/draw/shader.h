/*

[Shader�N���X] �p����:ShaderBase
	[��`]
		[default vertex shader]
			#version xxx core // OpenGL�̃o�[�W�����w��(�f�t�H���g��450)
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
			#version xxx core // OpenGL�̃o�[�W�����w��(�f�t�H���g��450)
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

#pragma once

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
		static bool init();
		static bool loop();
		// �o�[�e�b�N�X�V�F�[�_�̂ݐ���
		static PROGRAM createVSProgram(SHADER_CODE vs);
		// �t���O�����g�V�F�[�_�̂ݎw��
		static PROGRAM createFSProgram(SHADER_CODE fs);
		static inline Shader::PROGRAM Shader::getNormalProgram() { return normal; }
		static inline GLuint Shader::getVertexLocation() { return pos_s; }
		static inline GLuint Shader::getColorLocation() { return col_s; }
		static bool setProgram(PROGRAM p);
	};
}