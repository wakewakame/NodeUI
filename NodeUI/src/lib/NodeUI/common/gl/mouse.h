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
#include "gl.h"

namespace nui {
	class Mouse {
	public:
		using CURSOR = glm::dvec2; // �J�[�\�����W
		struct CLICK {
			bool l; // ���N���b�N
			bool r; // �E�N���b�N
			bool w; // �z�C�[���N���b�N
			CLICK();
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
		static void wheel_func(GLFWwindow *window, double x, double y);
		// �������֐�
		static void init();

	public:
		static bool loop();
		static inline Mouse::CURSOR Mouse::getCursor() { return cursor; }
		static inline Mouse::CURSOR Mouse::getCursorMove() { return cursor_move; }
		static inline Mouse::CURSOR Mouse::getDragFrom() { return drag_from; }
		static inline Mouse::CLICK Mouse::getClickA() { return click_a; }
		static inline Mouse::CLICK Mouse::getClickB() { return click_b; }
		static inline Mouse::WHEEL Mouse::getWheel() { return wheel; }
	};
}