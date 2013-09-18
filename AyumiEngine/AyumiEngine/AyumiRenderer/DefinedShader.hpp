/**
 * File contains definition of defined in-engine shader for canvas/sprite and defined
 * geometry rendering.
 * @file    DefinedShader.hpp
 * @author  Szymon "Veldrin" Jab³oñski
 * @date    2011-08-27
 */

#ifndef DEFINEDSHADER_HPP
#define DEFINEDSHADER_HPP

static const char* spriteVertexShader = 
	"#version 330 core\n" \
	"uniform mat4 projectionMatrix;\n" \
	"uniform mat4 modelViewMatrix;\n" \
	"in vec4 vertex;\n" \
	"in vec2 texCoord;\n" \
	"out vec2 TexCoord;\n" \
	"void main()\n" \
	"{\n" \
	"	gl_Position = projectionMatrix*modelViewMatrix*vertex;\n" \
	"	TexCoord = texCoord;\n" \
	"}\n";

static const char* spriteFragmentShader =
	"#version 330 core\n" \
	"uniform samplerRect ColorMapSampler;\n" \
	"uniform float alpha;\n" \
	"in vec2 TexCoord;\n" \
	"out vec4 fragColor;\n" \
	"void main()\n" \
	"{\n" \
	"	fragColor = texture(ColorMapSampler, TexCoord);\n" \
	"	if(fragColor.a < 0.5f)\n" \
	"		discard; \n"\
	"	fragColor.a = alpha;\n" \
	"}\n";

static const char* boxVertexShader =
	"#version 330 core\n" \
	"uniform mat4 modelViewMatrix;\n" \
	"uniform mat4 projectionMatrix;\n" \
	"in vec4 vertex;\n" \
	"void main()\n" \
	"{\n" \
	"	gl_Position = projectionMatrix*modelViewMatrix*vertex;\n" \
	"}\n";
	
static const char* boxFragmentShader =
	"#version 330 core\n" \
	"out vec4 fragColor;\n" \
	"void main()\n" \
	"{\n" \
	"	fragColor = vec4( 1.0, 1.0, 1.0, 1.0 );\n" \
	"}\n";

static const char* renderToDepthVertex =
	"#version 330 core\n" \
	"uniform mat4 projectionMatrix;\n" \
	"uniform mat4 modelViewMatrix;\n" \
	"in vec4 vertex;\n" \
	"void main()\n" \
	"{\n" \
	"	gl_Position = projectionMatrix*modelViewMatrix*vertex;\n" \
	"}\n";

static const char* renderToDepthFragment =
	"#version 330 core\n" \
	"out vec4 fragColor;\n" \
	"void main()\n" \
	"{\n" \
	"	fragColor = vec4( 1.0, 1.0, 1.0, 1.0 );\n" \
	"}\n";
#endif
