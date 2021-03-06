#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LoadShaders.h"
#define _USE_MATH_DEFINES //required to use M_PI
#include <math.h>
#include <vector>

typedef std::vector<GLfloat> GLvec;

GLuint VertexArrays[3];
GLuint Buffers[3][2];
GLuint active_vao = 0;	//index for the active vertex array object
GLvec vertices[3];		//2D vertex list
GLvec colors[3];		//vertex color (r,g,b) list

//Callback functions
void keyboard(unsigned char key, int x, int y);		//key-Pressed key value, x,y - x,y coordinates of a mouse pointer
void display();
void init();
int build_program();
void get_circle_2d(GLvec& p, int sectors, GLfloat radius);
void get_rect_2d(GLvec& p, GLfloat width, GLfloat height);
void get_vertex_color(GLvec& color, GLuint n, GLfloat r, GLfloat g, GLfloat b);
void bind_buffer(GLint buffer, GLvec& vec, int program, const GLchar* attri_name, GLint attri_size);

void share_buffer(GLint buffer, int program, const GLchar* attri_name, GLint attri_size);

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("VAO example");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error : %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard); //Register the keyboard callback function in GLUT
	glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
	//Let the GLUT redraw the screen by calling display()
	switch (key)
	{
	case '1': active_vao = 0; glutPostRedisplay(); break;	//Magenta circle
	case '2': active_vao = 1; glutPostRedisplay(); break;	//Yellow Rectangle
	case '3': active_vao = 2; glutPostRedisplay(); break;	//Blue Circle
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VertexArrays[active_vao]);
	glDrawArrays(active_vao == 1 ? GL_TRIANGLES : GL_TRIANGLE_FAN, 0, vertices[active_vao].size() / 2);
	glFlush();
}

void init() 
{
	int program = build_program();
	//Generate vertex positions and colors.
	get_circle_2d(vertices[0], 50, 0.5f);		//50-# of sectors, 0.5f-radius
	get_rect_2d(vertices[1], 1.0f, 0.8f);		//1.0f, 0.8f-width&height
	get_circle_2d(vertices[2], 50, 0.5f);		//50-# of sectors, 0.5f-radius
	get_vertex_color(colors[0], vertices[0].size() / 2, 0.8f, 0.2f, 0.5f);		//vertices[0].size() / 2 - # of vertices, RGB color
	get_vertex_color(colors[1], vertices[1].size() / 2, 0.9f, 0.9f, 0.1f);		//vertices[1].size() / 2 - # of vertices, RGB color
	get_vertex_color(colors[2], vertices[2].size() / 2, 0.3f, 0.3f, 1.0f);		//vertices[2].size() / 2 - # of vertices, RGB color

	glGenVertexArrays(3, VertexArrays);
	
	glBindVertexArray(VertexArrays[0]);
	glGenBuffers(2, Buffers[0]);
	bind_buffer(Buffers[0][0], vertices[0], program, "vPosition", 2);
	bind_buffer(Buffers[0][1], colors[0], program, "vColor", 3);

	glBindVertexArray(VertexArrays[1]);
	glGenBuffers(2, Buffers[1]);
	bind_buffer(Buffers[1][0], vertices[1], program, "vPosition", 2);
	bind_buffer(Buffers[1][1], colors[1], program, "vColor", 3);

	glBindVertexArray(VertexArrays[2]);
	glGenBuffers(1, Buffers[2]);
	share_buffer(Buffers[0][0], program, "vPosition", 2);
	bind_buffer(Buffers[2][0], colors[2], program, "vColor", 3);
}

int build_program()
{
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "vao_example.vert"},
		{GL_FRAGMENT_SHADER, "vao_example.frag"},
		{GL_NONE, NULL}
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	return program;
}

#define VSET2(v,a,b)do {(v)[0]=(a); (v)[1]=(b);} while(0)
#define VSET2PP(v,a,b)do {VSET2(v,a,b); v+=2;} while(0)

void get_circle_2d(GLvec& p, int sectors, GLfloat radius)
{
	p.resize((sectors + 2) * 2);
	GLfloat* data = p.data();

	//Push the center of a circle
	VSET2PP(data, 0, 0);

	//Push all circular points that constructs the circle
	for (int i = 0; i <= sectors; ++i)
	{
		GLfloat phi = (GLfloat)(2 * M_PI*i / sectors);
		GLfloat x = radius * cos(phi);
		GLfloat y = radius * sin(phi);
		VSET2PP(data, x, y);
	}
}

void get_rect_2d(GLvec& p, GLfloat width, GLfloat height)
{
	GLfloat w2 = width / 2;
	GLfloat h2 = height / 2;

	p.resize(12);
	GLfloat* data = p.data();

	//first triangle
	VSET2PP(data, -w2, -h2);
	VSET2PP(data, +w2, -h2);
	VSET2PP(data, -w2, +h2);

	//second triangle
	VSET2PP(data, +w2, -h2);
	VSET2PP(data, +w2, +h2);
	VSET2PP(data, -w2, +h2);
	VSET2PP(data, -w2, -h2);
}

void get_vertex_color(GLvec& color, GLuint n, GLfloat r, GLfloat g, GLfloat b)
{
	color.resize(n * 3);
	for (GLuint i = 0; i < n; ++i) 
	{
		color[i * 3 + 0] = r;
		color[i * 3 + 1] = g;
		color[i * 3 + 2] = b;
	}
}

void bind_buffer(GLint buffer, GLvec& vec, int program, const GLchar* attri_name, GLint attri_size)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vec.size(), vec.data(), GL_STATIC_DRAW);

	GLuint location = glGetAttribLocation(program, attri_name);
	glVertexAttribPointer(location, attri_size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}

//Share a buffer object with another VAO
void share_buffer(GLint buffer, int program, const GLchar* attri_name, GLint attri_size)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	GLuint location = glGetAttribLocation(program, attri_name);
	glVertexAttribPointer(location, attri_size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(location);
}