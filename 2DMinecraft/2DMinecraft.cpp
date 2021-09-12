#include <GL3\gl3w.h>
#include <GLFW\glfw3.h>
#include "LoadShaders.h"
#include <iostream>
#include "2dMinecraft.h"

void init();
void createBlocks();
void display();
void close();
void setFrameBufferSizeCallback(GLFWwindow* window, int width, int height);

/*static const GLfloat blockVertices[] =
{
	0.025f, 0.025f, 0.0f, 1.0f,//upper right
	-0.025f, 0.025f, 0.0f, 1.0f,//upper left
	0.025f, -0.025f, 0.0f, 1.0f, //down right
	-0.025f, 0.025f, 0.0f, 1.0f,//upper left
	-0.025f, -0.025f, 0.0f, 1.0f,//down left
	0.025f, -0.025f, 0.0f, 1.0f, //down right
	0.075f, 0.075f, 0.0f, 1.0f,//upper right
	0.025f, 0.075f, 0.0f, 1.0f,//upper left
	0.075f, 0.025f, 0.0f, 1.0f, //down right
	0.025f, 0.075f, 0.0f, 1.0f,//upper left
	0.025f, 0.025f, 0.0f, 1.0f,//down left
	0.075f, 0.025f, 0.0f, 1.0f //down right
};

static const GLfloat blockColors[] =
{
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f
};*/

/*static const GLfloat  blockVertices[6][2] = {
{ -0.90f, -0.90f },{ 0.85f, -0.90f },{ -0.90f,  0.85f },  // Triangle 1
{ 0.90f, -0.85f },{ 0.90f,  0.90f },{ -0.85f,  0.90f }   // Triangle 2
};*/

GLFWwindow* window;
GLuint program;

GLuint VAOids[1];
GLuint VBOids[1];

float black[] = { 1.0f, 1.0f, 1.0f, 1.0f };

//array of block ids
BlockIds** blocks;

GLfloat* blockVertices;
int* verticesColorsSize;

GLfloat* blockColors;

int main(int argc, char** argv)
{
	glfwInit();

	window = glfwCreateWindow(Settings::SCREEN_SIZE_WIDTH, Settings::SCREEN_SIZE_HEIGHT, "2D Minecraft", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, setFrameBufferSizeCallback);

	gl3wInit();

	init();

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	close();

	return 0;
}

void init()
{
	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "Shaders\\vertexshaderone.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders\\fragmentshaderone.frag" },
		{ GL_NONE, NULL }
	};

	program = LoadShaders(shaders);
	glUseProgram(program);

	createBlocks();

	glGenVertexArrays(1, VAOids);
	glBindVertexArray(VAOids[0]);

	glGenBuffers(1, VBOids);
	glBindBuffer(GL_ARRAY_BUFFER, VBOids[0]);
	glBufferData(GL_ARRAY_BUFFER, (2 * *verticesColorsSize * sizeof(GLfloat)), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, (*verticesColorsSize * sizeof(GLfloat)), blockVertices);
	glBufferSubData(GL_ARRAY_BUFFER, (*verticesColorsSize * sizeof(GLfloat)), (*verticesColorsSize * sizeof(GLfloat)), blockColors);
	

	/*glBufferData(GL_ARRAY_BUFFER, sizeof(blockColors) + sizeof(blockVertices), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(blockVertices), blockVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(blockVertices), sizeof(blockColors), blockColors);*/

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(0));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(*verticesColorsSize * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void createBlocks() 
{
	blocks = createTerrain(20394);

	verticesColorsSize = new int;

	blockVertices = new GLfloat[Settings::SCREEN_BLOCKS_WIDTH * Settings::SCREEN_BLOCKS_HEIGHT * 6 * 4];
	blockColors = new GLfloat[Settings::SCREEN_BLOCKS_WIDTH * Settings::SCREEN_BLOCKS_HEIGHT * 6 * 4];

	createBlockVertices(blocks, blockVertices, blockColors, verticesColorsSize);
}

void display()
{
	//glClearBufferfv(GL_COLOR, 0, black);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClearBufferfv(GL_COLOR, 0, black);

	glClearColor(0, 0, 0, 1);
	glBindVertexArray(VAOids[0]);

	int sizeGLfloat = sizeof(GLfloat);

	glDrawArrays(GL_TRIANGLES, 0, Settings::SCREEN_BLOCKS_WIDTH * Settings::SCREEN_BLOCKS_HEIGHT * 6);

	/*for (int x = 0; x < *verticesColorsSize / 6; x++) 
	{
		glDrawArrays(GL_TRIANGLE_STRIP, (x * 6) * sizeGLfloat, 6);
	}*/
}

void close()
{
	//delete blocks array
	for (int x = 0; x < Settings::SCREEN_BLOCKS_WIDTH; x++) 
	{
		delete[] blocks[x];
	}

	delete[] blocks;

	delete verticesColorsSize;
	//delete blockVerties and blockColors

	//clean up glfw stuff
	glfwDestroyWindow(window);
	glfwTerminate();
}

void setFrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
