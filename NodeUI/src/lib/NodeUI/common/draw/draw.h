#pragma once

#include "../gl/gl.h"

namespace nui {
	class Draw {
	private:
		static GLuint VertexArrayID; // VAO
		static GLuint vertexbuffer; // VBO

	public:
		static bool init() {
			// GLManagement�N���X�̏�����
			if (nui::GLManagement::init()) return 1;

			// VAO�̐���
			static const GLfloat g_vertex_buffer_data[] = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f,  1.0f, 0.0f,
			};
			glGenVertexArrays(1, &VertexArrayID);
			glGenBuffers(1, &vertexbuffer);
			glBindVertexArray(VertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

			return 0;
		}

		static bool draw() {
			if (nui::GLManagement::loop()) return 1;
			//�C�x���g����������܂őҋ@
			glfwPollEvents();

			//��ʏ�����
			glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // ����0�F0�ɓ��ɗ��R�͂���܂���B�������A�V�F�[�_����layout�Ƃ��킹�Ȃ��Ƃ����܂���B
				3,                  // �T�C�Y
				GL_FLOAT,           // �^�C�v
				GL_FALSE,           // ���K���H
				0,                  // �X�g���C�h
				(void*)0            // �z��o�b�t�@�I�t�Z�b�g
			);

			// �O�p�`��`���܂��I
			glDrawArrays(GL_TRIANGLES, 0, 3); // ���_0����n�܂�܂��B���v3�̒��_�ł��B&rarr;1�̎O�p�`�ł��B

			glDisableVertexAttribArray(0);

			//�o�b�t�@�ɕ`��
			glFlush();
			//�J���[�o�b�t�@�����ւ���
			glfwSwapBuffers(nui::Window::getGLFWHwnd());

			return 0;
		}

		static void exit() {
			glDeleteVertexArrays(1, &VertexArrayID);

			nui::GLManagement::exit();
		}
	};
	GLuint Draw::VertexArrayID = GL_FALSE;
	GLuint Draw::vertexbuffer = GL_FALSE;
}