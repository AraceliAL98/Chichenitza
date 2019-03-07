#version 330 core
//Primera linea SIEMPRE es la versión

//Atributos de entrada (Vienen desde el Vertex Shader)
in vec4 fragmentColor;

//Atributos de salida
out vec4 salidaColor;

//funcon main()
void main() {
	salidaColor = fragmentColor;
}