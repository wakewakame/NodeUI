//コンソール非表示化
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include <iostream>

#include "lib/NodeUI.h"

int main() {
	if (nui::Draw::init()) return 1;

	while (true) {
		nui::Draw::clear();

		//nui::Draw::setFill(0);
		nui::Shader::setProgram(
			nui::Shader::createFSProgram(
				R"(
					#version 450 core
					in vec4 fragmentColor;
					out vec4 color;
					void main(){
						if ((int(gl_FragCoord.x+gl_FragCoord.y)%60) < 30){
							color = fragmentColor;
						}
						else{
							color = vec4(0.0);
						}
					}
				)"
			)
		);

		nui::Draw::setColor(0.0f, 0.5f, 0.78f, 1.0f);
		nui::Draw::circle(
			nui::Mouse::getCursor().x,
			nui::Mouse::getCursor().y,
			100
		);


		nui::Draw::drawPoint(GL_LINE_STRIP);

		if (nui::Draw::render()) break;
	}

	nui::Draw::exit();
	return 0;
}