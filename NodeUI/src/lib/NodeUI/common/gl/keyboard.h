/*

[Keyboardクラス]
	[定義]
		キー番号:http://www.glfw.org/docs/3.0/group__keys.html

	[関数]
		bool getKey(int key)
			引数に指定されたキー番号のキーの入力状態を取得する
			キーが入力されている間は常に1
			引数1:キー番号
			戻り値:離:0,押:1

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