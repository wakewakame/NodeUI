#include "keyboard.h"

namespace nui {
	bool Keydoard::getKey(int key) {
		return glfwGetKey(Window::getGLFWHwnd(), key);
	}
}