/*

[Keyboard�N���X]
	[��`]
		�L�[�ԍ�:http://www.glfw.org/docs/3.0/group__keys.html

	[�֐�]
		bool getKey(int key)
			�����Ɏw�肳�ꂽ�L�[�ԍ��̃L�[�̓��͏�Ԃ��擾����
			�L�[�����͂���Ă���Ԃ͏��1
			����1:�L�[�ԍ�
			�߂�l:��:0,��:1

*/

#pragma once

namespace nui {
	class Keydoard {
	public:
		static bool getKey(int key) {
			return glfwGetKey(Window::getGLFWHwnd(), key);
		}
	};
}