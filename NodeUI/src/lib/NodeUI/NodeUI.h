#pragma once
#pragma comment(lib, "opengl32.lib")

//コンソール非表示化
#ifndef NUI_DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include "common\draw\draw.h"