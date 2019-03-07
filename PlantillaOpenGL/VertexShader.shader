#version 330 core
//La primera linea SIEMPRE es la version

//Atributos de entrada (vienen desde c++)
in vec3 posicion;
in vec4 color;

//Atributos de salida (van hacia el fragment shader)
out vec4 fragmentColor;

//Funcion main
void main() {
	//Es la posicion de salida del vertice
	//Es del tipo vec4 
	gl_Position.xyz = posicion;
	gl_Position.w = 1.0;

	//Establecer valores de atributos de salida
	fragmentColor = color;
}