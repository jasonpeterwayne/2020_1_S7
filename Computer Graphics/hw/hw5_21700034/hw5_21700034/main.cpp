//
//  main.cpp
//  hw5_21700034
//
//  Created by 곽영혜 on 2020/04/05.
//  Copyright © 2020 곽영혜. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include "LoadShaders.h"
#define _USE_MATH_DEFINES //required to use M_PI
#include <math.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

typedef std::vector<GLfloat> GLvec;

const GLuint num_of_models = 3;

const char* obj_filepath[num_of_models] = {
    "/Users/gwag-yeonghye/hw5_21700034/hw5_21700034/house.obj",
    "/Users/gwag-yeonghye/hw5_21700034/hw5_21700034/sphere.obj",
    "/Users/gwag-yeonghye/hw5_21700034/hw5_21700034/teapot.obj"
};

GLvec vertices[num_of_models];
std::vector<GLuint> faces[num_of_models];

GLuint vao[num_of_models];
GLuint vbo[num_of_models][2];

int program;
GLuint active_vao = 0; //You need to change its value according to user's keyboard input.




//Callback functions
void keyboard(unsigned char key, int x, int y);
//key-Pressed key value, x,y - x,y coordinates of a mouse pointer
void display();
void init();
int build_program();
void bind_buffer(GLint buffer, GLvec& vec, int program, const GLchar* attri_name, GLint attri_size);
void bind_buffer(GLint buffer, std::vector<GLuint>& vec, int program);
bool load_obj(GLvec& vertices, std::vector<GLuint>& faces, const char* filepath);


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|
    GLUT_DEPTH|GLUT_3_2_CORE_PROFILE); // Add this line.
    glutInitWindowSize(512, 512);
    glutCreateWindow(argv[0]);
    
    glewExperimental = GL_TRUE; // Add this line.
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Error : %s\n", glewGetErrorString(err));
        exit(-1);
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
    case '1': active_vao = 0; glutPostRedisplay(); break;
    case '2': active_vao = 1; glutPostRedisplay(); break;
    case '3': active_vao = 2; glutPostRedisplay(); break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao[active_vao]);
    
    using namespace glm;
    GLint location;
    GLfloat theta = 0.00001f * clock();

    location = glGetUniformLocation(program, "active_vao");
    glUniform1i(location, active_vao);
    
    mat4 T(1.0f);
    T = rotate(T, theta, vec3(0.0f, 1.0f, 0.0f));
    T = scale(T, vec3(1.0f));
              
    location = glGetUniformLocation(program, "T");
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(T));
    
    glDrawElements(GL_TRIANGLES, faces[active_vao].size(), GL_UNSIGNED_INT, (void*)0);
    glFlush();
       
    glutSwapBuffers(); // Add this line.
    glutPostRedisplay();
}

void init()
{
    srand(clock());
    program = build_program();

    for(int i = 0; i < num_of_models; ++i){
        load_obj(vertices[i], faces[i], obj_filepath[i]); //Load OBJ files

        glGenVertexArrays(1, &vao[i]);
        glBindVertexArray(vao[i]);
        glGenBuffers(2, vbo[i]);
        
        bind_buffer(vbo[i][0], vertices[i], program, "vPosition", 3);
        bind_buffer(vbo[i][1], faces[i], program); //Make element array buffers to store vertex indices of each face.
    }

    glEnable(GL_DEPTH_TEST); //Enable depth test
    glDepthFunc(GL_LESS); //Accept fragment if it is closer to the camera than the existing one
    
    //Set polygon drawing mode to line drawing (GL_LINE) with thickness of 1.0.
    //(default mode : GL_FILL)
    glLineWidth(1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //Enable back-face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

int build_program()
{
    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "/Users/gwag-yeonghye/hw5_21700034/hw5_21700034/vao_example.vert"},
        {GL_FRAGMENT_SHADER, "/Users/gwag-yeonghye/hw5_21700034/hw5_21700034/vao_example.frag"},
        {GL_NONE, NULL}
    };
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);
    return program;
}

void bind_buffer(GLint buffer, GLvec& vec, int program, const GLchar* attri_name, GLint attri_size)
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vec.size(), vec.data(), GL_STATIC_DRAW);

    GLuint location = glGetAttribLocation(program, attri_name);
    glVertexAttribPointer(location, attri_size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
}

void bind_buffer(GLint buffer, std::vector<GLuint>& vec, int program)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) *vec.size(), vec.data(), GL_STATIC_DRAW);
}

bool load_obj(GLvec& vertices, std::vector<GLuint>& faces, const char* filepath)
{
    char countWord[128]; // read the first word of the line

    FILE * file = fopen(filepath, "r");
    
    if (file == NULL) {
        printf("Impossible to open the file!\n");
        return false;
    }

    while (!feof(file)) {
        fscanf(file, "%s", countWord);
        
        if(strcmp(countWord, "v") == 0) {
            GLfloat tmp_x, tmp_y, tmp_z;
            fscanf(file, "%f %f %f", &tmp_x, &tmp_y, &tmp_z);
            
            vertices.push_back(tmp_x);
            vertices.push_back(tmp_y);
            vertices.push_back(tmp_z);
        }
        else if(strcmp(countWord, "f") == 0) {
            GLuint temp_x, temp_y, temp_z;
            GLuint temp_A[3], temp_B[3];
            
            if(filepath == "/Users/gwag-yeonghye/hw5_21700034/hw5_21700034/house.obj") {
                fscanf(file, "%d %d %d\n", &temp_x, &temp_y, &temp_z);
            printf("%d %d %d\n", temp_x, temp_y, temp_z);
            }
           else {
                fscanf(file, "%d/%d %d/%d %d%d\n", &temp_x, &temp_A[0], &temp_y, &temp_A[1], &temp_z, &temp_A[2]);
            printf("%d~%d~%d\n", temp_x, temp_y, temp_z);
            }
            
            faces.push_back(temp_x-1);
            faces.push_back(temp_y-1);
            faces.push_back(temp_z-1);
        }
        else{
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }
//    for(int i=0; i<vertices.size(); i++) {
//        std::cout<<vertices.at(i)<<std::endl;
//    }

    fclose(file);
    return true;
}

