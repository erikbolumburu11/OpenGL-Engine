#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol; 
  
out vec4 vertexColor; // specify a color output to the fragment shader
out vec4 vertexPosition;

void main()
{
    vertexPosition = vec4(aPos, 1.0);
    gl_Position = vertexPosition;
    vertexColor = vec4(aCol, 1.0); // set the output variable to a dark-red color
}