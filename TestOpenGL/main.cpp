#include <iostream>
#include <vector>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

#include "Camera.h"
#include "Triangle.h"
#include "Square.h"
#include "Line.h"
#include "Wall.h"

#include "Text.h"

#include "AgentActor.h"
#include "Collision.h"

void processInput(GLFWwindow *window);
void mouseCall(GLFWwindow* window, double xPos, double yPos);
void WallAvoidance(Collision::LineCollision* wallCollision);

const GLuint WIDTH = 1280;
const GLuint HEIGHT = 720;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;

Text text;
AgentActor actor;
AgentActor target;
Line line;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
	glm::vec2 pt1 = glm::vec2(100.0f, 100.0f);
	glm::vec2 pt2 = glm::vec2(0.0f, 0.0f);

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create windows

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);

	int screenWidth;
	int screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window " << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouseCall);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW " << std::endl;
		return EXIT_FAILURE;
	}

	text.LoadFont("Fonts/arial.ttf");
	glViewport(0, 0, screenWidth, screenHeight);
	text.SetPixelSize(0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Shader textShader("Shaders/vShaderText.vs", "Shaders/fShaderText.fs");
	Shader shader("Shaders/vShaderSimple.vs", "Shaders/fShaderSimple.fs");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
	textShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(textShader.id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	text.LoadCharacter();
	text.Done();
	text.InitBuffer();

	std::string rad;
	std::string pos;

	actor.InitBuffer();
	actor.CreateShader("Shaders/vShaderSimple.vs", "Shaders/fShaderSimple.fs");
	actor.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	//actor.rotation = 3.02f;

	target.InitBuffer();
	target.CreateShader("Shaders/vShaderSimple.vs", "Shaders/fShaderSimple.fs");
	target.SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

	target.rotation = 1.57;
	target.position = glm::vec2(0.0f, -0.6f);
	target.state = 0;

	line.InitBuffer();

	std::string acc;

	Wall w;
	w.InitBuffer();

	Square* squareArray = new Square[4];
	glm::vec3* translationArray = new glm::vec3[4];

	for (int i = 0; i < 4; i++)
	{
		squareArray[i].InitBuffer();
	}

	//Seek(glm::vec2(-0.229620039,-0.0897666216));
	//Seek(glm::vec2(-0.459240079, -0.179533243));

	translationArray[0] = glm::vec3(-0.75f, 0.8f, 0.0f);
	//translationArray[1] = glm::vec3(-0.25f, 0.8f, 0.0f);
	//translationArray[0] = glm::vec3(-0.229620039f, -0.0897666216f, 0.0f);
	translationArray[1] = glm::vec3(-0.459240079f, -0.179533243f, 0.0f);
	translationArray[2] = glm::vec3(0.25f, 0.8f, 0.0f);
	translationArray[3] = glm::vec3(0.75f, 0.8f, 0.0f);

	glm::vec2 positionTarget = glm::vec2(0.0f, -0.6f);
	glm::vec2 positionAim = glm::vec2(-0.459240079f, -0.179533243f);

	/*p(T) = Po + tVL = Po + t(p1-po) = (1-t)po + tP1*/

	glm::vec2 direction;
	direction.x = (0.5) * positionTarget.x + 0.5 * positionAim.x;
	direction.y = (0.5) * positionTarget.y + 0.5 * positionAim.y;

	translationArray[0] = glm::vec3(direction.x, direction.y, 0.0f);


	actor.visibleTargetVector = true;
	target.visibleTargetVector = true;

	std::vector<Shape*> staticObject;
	staticObject.push_back(&w);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		actor.actorShader->Use();
		glBindVertexArray(actor.actor.vao);

		actor.Update(deltaTime, target);
		actor.Draw();

		target.actorShader->Use();
		glBindVertexArray(target.actor.vao);

		target.Update(deltaTime, actor);
		target.Draw();

		shader.Use();
		glm::mat4 transform;

		glBindVertexArray(w.vao);
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.0f, -0.3f, 0.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 1.0f, 1.0f));
		w.transform = transform;
		shader.SetMatrix("transform", transform);
		shader.SetVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
		w.Draw();

		//Hack pas bien
		if (target.state == 4)
		{
			target.FollowPath(translationArray, 4);
		}

		target.CheckCollision(staticObject[0]->GetEntityCollision(), 1);

		/*if(Collision::IntersectTriangleLine(actor.GetEntityCollision(), target.GetTargetVector(), pt1) == 1)
		{
			target.UpdateNearestCollision(pt1,0);
		}*/

		//Waypoint
		for (int i = 0; i < 4; i++)
		{
			glBindVertexArray(squareArray[i].vao);
			transform = glm::mat4(1.0f);
			transform = glm::translate(transform, translationArray[i]);
			shader.SetMatrix("transform", transform);
			shader.SetVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
			squareArray[i].Draw();
		}

		textShader.Use();

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//rad = "rad " + std::to_string(actor.rotation);
		acc = "state " + target.GetStateLabel(target.state);
		rad = "nearest " + std::to_string(target.nearestTargetActor.x) + " : " + std::to_string(target.nearestTargetActor.y);
		pos = "pos " + std::to_string(pt1.x) + " : " + std::to_string(pt1.y);

		text.RenderText(textShader, acc, 25.0f, 75.0f, 0.5f, glm::vec3(0.5f, 0.8f, 0.2f));
		text.RenderText(textShader, pos, 25.0f, 50.0f, 0.5f, glm::vec3(0.5f, 0.8f, 0.2f));
		text.RenderText(textShader, rad, 25.0f, 25.0f, 0.5f, glm::vec3(0.5f, 0.8f, 0.2f));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		actor.UpdatePosition(glm::vec2(0.0015f * glm::cos(actor.rotation), 0.0015f * glm::sin(actor.rotation)));
		//actor.UpdateAcceleration(0.25f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		actor.UpdatePosition(glm::vec2(-0.0015f * glm::cos(actor.rotation), -0.0015f * glm::sin(actor.rotation)));
		//actor.UpdateAcceleration(-0.25f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		actor.UpdateAngle(0.005f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		actor.UpdateAngle(-0.005f);
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		target.state = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		target.state = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		target.state = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		target.state = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		target.state = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		target.state = 5;
	}


}

void mouseCall(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos; // Reverse because y corod go from bottom to top
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
