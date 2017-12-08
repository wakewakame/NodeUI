/*

[DrawBase�N���X]
	[��`]
		using VAR_TYPE = float
		struct POINTS {
			std::vector<VAR_TYPE> points; // ���_�z��
			unsigned int dim; // ���_�̎�����
		}

	[�֐�]
		bool init(unsigned int set_max_point = 512)
			�������֐�
			Draw�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
			�ق��̊֐����g�p����O�ɂ��̊֐������s����
			����1:1�x�ɒǉ��ł��钸�_�̍ő吔(�f�t�H���g��512��)
			�߂�l:����:0,�G���[:1

		void setColor(float r, float g, float b, float a = 1.0f)
			�F�w��֐�
			����1:R�l
			����2:G�l
			����3:B�l
			����4:A�l

		bool addPoint(float set_x, float set_y)
			���_�ǉ��֐�
			���W�P�ʂ�px
			�E�B���h�E��������_�Ƃ��A�E�������̕���
			����1:x���W
			����2:y���W
			�߂�l:����:0,�G���[:1

		void drawPoint(GLenum Type)
			���_�`��֐�
			�ǉ����ꂽ���_��Type���[�h�Ńo�b�t�@�ɕ`�悷��
			�o�b�t�@���E�B���h�E�ɔ��f����ɂ�render�֐����g�p����
			����1:�`�惂�[�h(�ȉ��̂����ꂩ)
				GL_POINTS
				GL_LINE_STRIP
				GL_LINE_LOOP
				GL_LINES
				GL_LINE_STRIP_ADJACENCY
				GL_LINES_ADJACENCY
				GL_TRIANGLE_STRIP
				GL_TRIANGLE_FAN
				GL_TRIANGLES
				GL_TRIANGLE_STRIP_ADJACENCY
				GL_TRIANGLES_ADJACENCY
				GL_PATCHES

		void clear()
			�o�b�t�@�N���A�֐�
			�o�b�t�@�𔒂ɓh��Ԃ�

		bool render()
			�o�b�t�@���E�B���h�E�ɔ��f����֐�

		void exit()
			�I�����Ɏ��s���ׂ��֐�
			Draw�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢

*/

#pragma once

#include <vector>

#include "../gl/gl.h"
#include "shader.h"

namespace nui {
	class DrawBase {
	public:
		using VAR_TYPE = float;
		struct POINTS {
			std::vector<VAR_TYPE> points;
			unsigned int dim;
			POINTS();
			POINTS(unsigned int set_num_points, unsigned int set_dim);
			inline unsigned int DrawBase::POINTS::size() {
				return sizeof(VAR_TYPE)*points.size();
			}
			inline void DrawBase::POINTS::set(unsigned int set_index, unsigned int set_dim, VAR_TYPE val) {
				points[set_index*dim + set_dim] = val;
			}
		};

	private:
		static GLuint vao; // Vertex Array Object
		static GLuint vbo; // Vertex Buffer Object
		static GLuint cbo; // Color Array Object
		static POINTS vertex;
		static POINTS color;
		static unsigned int num_point;
		static glm::vec4 default_color;
		static unsigned int max_point;
		static bool createBuffers();
		static bool setArray(GLuint Location, POINTS &set_array);

	public:
		static bool init(unsigned int set_max_point = 512);

		static void setColor(float r, float g, float b, float a = 1.0f);

		static bool addPoint(float set_x, float set_y);

		static void drawPoint(GLenum Type);

		static void clear();

		static bool render();

		static void exit();
	};
}