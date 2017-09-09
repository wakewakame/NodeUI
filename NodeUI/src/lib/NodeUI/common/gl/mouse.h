/*

[Mouse�N���X]
	[��`]
		using CURSOR = glm::dvec2
		struct CLICK {
			bool l; // ���N���b�N
			bool r; // �E�N���b�N
			bool w; // �z�C�[���N���b�N
			CLICK() {
				l = 0;
				r = 0;
				w = 0;
			}
		}
		using WHEEL = glm::dvec2

	[�֐�]
		static bool loop()
			���t���[�����s���ׂ��֐�
			GLManagement�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢�B
			�߂�l:����:0,�G���[:1

		static inline CURSOR getCursor()
			���݂̃}�E�X�J�[�\���̍��W���擾
			�߂�l:���݂̃}�E�X�J�[�\���̍��W

		static inline CURSOR getCursorMove()
			1�O�̃t���[������̃}�E�X�J�[�\���̈ړ��ʂ��擾
			�߂�l:1�O�̃t���[������̃}�E�X�J�[�\���̈ړ���

		static inline CURSOR getDragFrom()
			���A�E�A�z�C�[���̂����ꂩ���N���b�N���ꂽ�u�Ԃ̃J�[�\�����W���擾(�h���b�O�p)
			�߂�l:���A�E�A�z�C�[���̂����ꂩ���N���b�N���ꂽ�u�Ԃ̃J�[�\�����W

		static inline CLICK getClickA()
			������Ă���Ԃ�����1�̃N���b�N�����擾
			�߂�l:������Ă���Ԃ�����1�̃N���b�N���

		static inline CLICK getClickB()
			�����ꂽ�t���[���̂�1�̃N���b�N�����擾
			�߂�l:�����ꂽ�t���[���̂�1�̃N���b�N���

		static inline WHEEL getWheel()
			1�t���[���Ԃɔ��������z�C�[����]�ʂ��擾
			�߂�l:1�t���[���Ԃɔ��������z�C�[����]�ʂ��擾

*/

#pragma once

namespace nui {
	class Mouse {
	public:
		using CURSOR = glm::dvec2; // �J�[�\�����W
		struct CLICK {
			bool l; // ���N���b�N
			bool r; // �E�N���b�N
			bool w; // �z�C�[���N���b�N
			CLICK() {
				l = 0;
				r = 0;
				w = 0;
			}
		};
		using WHEEL = glm::dvec2; // �z�C�[����]��

	private:
		static CURSOR cursor; // ���݂̃}�E�X�J�[�\�����W
		static CURSOR cursor_buf; // 1�O��cursor�̏��
		static CURSOR cursor_move; // 1�t���[���Ԃ̃J�[�\���̈ړ���
		static CURSOR drag_from; // ���A�E�A�z�C�[���̂����ꂩ���N���b�N���ꂽ�u�Ԃ̃J�[�\�����W(�h���b�O�p)
		static CLICK click_a; // ������Ă���Ԃ�����1�̃N���b�N���
		static CLICK click_a_buf; // 1�O��click_a�̏��
		static CLICK click_b; // �����ꂽ�t���[���̂�1�̃N���b�N���
		static WHEEL wheel; // 1�t���[���Ԃɔ��������z�C�[����]��
		static WHEEL wheel_buf; // 1�t���[���Ԃɔ��������z�C�[����]�ʂ�~����ׂ̕ϐ�
		static bool init_flag; // ������������Ă��Ȃ����1
		// �z�C�[���C�x���g�����p
		static void wheel_func(GLFWwindow *window, double x, double y) {
			wheel_buf.x += x;
			wheel_buf.y += y;
		}
		// �������֐�
		static void init() {
			glfwSetScrollCallback(Window::getGLFWHwnd(), wheel_func);
		}

	public:
		static bool loop() {
			// ������������Ă��Ȃ���Ώ�����
			if (init_flag) init();

			// �J�[�\�����W�擾
			cursor_buf = cursor;
			glfwGetCursorPos(Window::getGLFWHwnd(), &cursor.x, &cursor.y);
			cursor_move = cursor - cursor_buf;

			// click_a�擾
			click_a_buf = click_a;
			click_a.l = (glfwGetMouseButton(Window::getGLFWHwnd(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
			click_a.r = (glfwGetMouseButton(Window::getGLFWHwnd(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
			click_a.w = (glfwGetMouseButton(Window::getGLFWHwnd(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);

			// click_b�擾
			click_b.l = ((click_a.l) && (!click_a_buf.l));
			click_b.r = ((click_a.r) && (!click_a_buf.r));
			click_b.w = ((click_a.w) && (!click_a_buf.w));
			if (click_b.l || click_b.r || click_b.w) drag_from = cursor;

			// �z�C�[����]�ʎ擾
			wheel = wheel_buf;
			wheel_buf = glm::dvec2(0.0, 0.0);

			return 0;
		}
		static inline CURSOR getCursor() {return cursor;}
		static inline CURSOR getCursorMove() {return cursor_move;}
		static inline CURSOR getDragFrom() { return drag_from; }
		static inline CLICK getClickA() {return click_a;}
		static inline CLICK getClickB() {return click_b;}
		static inline WHEEL getWheel() {return wheel;}
	};
	Mouse::CURSOR Mouse::cursor = glm::dvec2(0.0, 0.0);
	Mouse::CURSOR Mouse::cursor_buf = cursor;
	Mouse::CURSOR Mouse::cursor_move = glm::dvec2(0.0, 0.0);
	Mouse::CURSOR Mouse::drag_from = glm::dvec2(0.0, 0.0);
	Mouse::CLICK Mouse::click_a;
	Mouse::CLICK Mouse::click_a_buf;
	Mouse::CLICK Mouse::click_b;
	Mouse::WHEEL Mouse::wheel = glm::dvec2(0.0, 0.0);
	Mouse::WHEEL Mouse::wheel_buf = glm::dvec2(0.0, 0.0);
	bool Mouse::init_flag = 1;
}