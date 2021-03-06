// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "Shader.h"
#include "Vertice.h"

using namespace std;

Shader *shader;
GLuint posicionID;
GLuint colorID;

vector<Vertice> triangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

vector<Vertice> cuadrado;
GLuint vertexArrayCuadradoID;
GLuint bufferCuadradoID;

void inicializarCuadrado() 
{

	//Escalon 1
	Vertice v1 = 
	{
		vec3(-0.8, -0.8, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v2 = 
	{
		vec3(0.8, -0.8, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v3 = 
	{
		vec3(0.8, -0.95, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v4 = 
	{
		vec3(-0.8, -0.95, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);

	//Escalon 1
	Vertice v5 = 
	{
		vec3(-0.75, -0.65, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v6 = 
	{
		vec3(0.75, -0.65, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v7 = 
	{
		vec3(0.75, -0.8, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v8 = 
	{
		vec3(-0.75, -0.8, 0.0),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	cuadrado.push_back(v5);
	cuadrado.push_back(v6);
	cuadrado.push_back(v7);
	cuadrado.push_back(v8);
}


void inicializarTriangulo() 
{
	Vertice v1 = 
	{
		vec3(0.0f, 0.3f, 0.0f),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v2 = 
	{
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	Vertice v3 = 
	{
		vec3(0.3f, -0.3f, 0.0f),
		vec4(0.9101f, 0.875f, 0.8164f, 1.0f)
	};
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}

void dibujar() 
{
	//Elegir el shader
	shader->enlazar();
	//Elegir un vertex array 
	glBindVertexArray(vertexArrayTrianguloID);
	//dibujar 
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

	//Cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_QUADS, 0, cuadrado.size());

	//soltar el vertex array
	glBindVertexArray(0);
	//soltar el shader
	shader->desenlazar();
}

void actualizar() 
{

}

int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) 
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) 
	{
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	inicializarTriangulo();
	inicializarCuadrado();

	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	//Desenlazar el shader
	shader->desenlazar();

	//crear un vertex array
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);
	//crear vertex buffer
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);
	//llenar el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);

	//Habilitar atributos de shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	//especificar a OpenGL como se va a comunicar
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Vertex array y buffer para cuadrado
	//crear un vertex array
	glGenVertexArrays(1, &vertexArrayCuadradoID);
	glBindVertexArray(vertexArrayCuadradoID);
	//crear vertex buffer
	glGenBuffers(1, &bufferCuadradoID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID);
	//llenar el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data(), GL_STATIC_DRAW);

	//Habilitar atributos de shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	//especificar a OpenGL como se va a comunicar
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice),  (void*)sizeof(vec3));

	//soltar vertex array y buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) 
	
{
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

