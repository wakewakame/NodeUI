#pragma once
#pragma comment(lib, "opengl32.lib")

//�R���\�[����\����
#ifndef NUI_DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include "common\draw\draw.h"