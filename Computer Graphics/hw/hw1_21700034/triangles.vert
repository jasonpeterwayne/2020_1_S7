#version 430 //GLSL version to use

in vec4 vPosition; //Declaration of a shader's input attribute(read_only)
//vec4 : 4D-vector data type

void main()
{
	gl_Position = vPosition;
	//gl_Position : Built-in 4D vector representing the final processed vertex position
}
