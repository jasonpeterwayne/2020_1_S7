#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LoadShaders.h"
//Built-in header file which defines utiluty functions for loading shaders

//Variation Declarations
const GLsizei NumVertices = 6;
GLfloat vertices[NumVertices][2] = {{-0.90f, -0.90f}, {0.85f, -0.90f}, {-0.90f, 0.85f}, {0.90f, -0.85f}, {0.90f, 0.90f}, {-0.85f, 0.90f}};
GLuint Buffers[1], VertexArrays[1];

void init() //initializes OpenGL for drawing triangles.
{
  //Generate vertex array objects(VAOs) and specify the current active VAO.
  //Vertex Array Object(VAO) : An object which contains one or more Vertex Buffer Objects (VBOs)
	glGenVertexArrays(1, VertexArrays);
	glBindVertexArray(VertexArrays[0]);

	glGenBuffers(1, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //Compile shaders and produce a program to which the compiled shaders are attached.
  //Then, register the program in OpenGL.
	ShaderInfo shaders[] = {
	{GL_VERTEX_SHADER, "triangles.vert"},
	{GL_FRAGMENT_SHADER, "triangles.frag"},
	{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

  //Finds the location(or identifier) of a specified vertex attribute.
	GLuint location = glGetAttribLocation(program, "vPosition");
  //Specifies how to read the buffer data through the attribute
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, 0);
  //Enable the attribute.
	glEnableVertexAttribArray(location);
}

void display() //Draws trianlges with OpenGL
{
  //Clear the buffers for color writing.
	glClear(GL_COLOR_BUFFER_BIT);
  //Specifies the current active VAO.
	glBindVertexArray(VertexArrays[0]);
  //Issues a drawing command.
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
  //Forces the execution of OpenGL commands in finite time.
	glFlush();
}

void main(int argc, char** argv)
{
  //Initialize GLUT to make a window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);

  //Initialize GLEW to load OpenGL extensions.
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

  //Register a "display" callback function and enter the GLUT event processing loop.
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}
