#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "Common.h"
#include "Model.h"
#include "Camera.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "OBJManager.h"
#include "Light.h"

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei length,
	const GLchar* msg, const void* data)
{
    std::string _source;
	std::string _type;
	std::string _severity;

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		_source = "API";
		break;

	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "WINDOW SYSTEM";
		break;

	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "SHADER COMPILER";
		break;

	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "THIRD PARTY";
		break;

	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "APPLICATION";
		break;

	case GL_DEBUG_SOURCE_OTHER:
		_source = "UNKNOWN";
		break;

	default:
		_source = "UNKNOWN";
		break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;

	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "DEPRECATED BEHAVIOR";
		break;

	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "UDEFINED BEHAVIOR";
		break;

	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "PORTABILITY";
		break;

	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "PERFORMANCE";
		break;

	case GL_DEBUG_TYPE_OTHER:
		_type = "OTHER";
		break;

	case GL_DEBUG_TYPE_MARKER:
		_type = "MARKER";
		break;

	default:
		_type = "UNKNOWN";
		break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "MEDIUM";
		break;

	case GL_DEBUG_SEVERITY_LOW:
		_severity = "LOW";
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "NOTIFICATION";
		break;

	default:
		_severity = "UNKNOWN";
		break;
	}

	std::cerr << id << ": " << _type << " of " << _severity << " severity, raised from " << _source << ": " << msg << std::endl;

}

void processInputCamera(GLFWwindow* window, Camera& camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.moveFront();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveBack();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveRight();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	// enable debugging
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simple 3D Scene Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	// Need to be created after an OpenGL context
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "ERROR: Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// DEBUG: get openGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// DEBUG: set debug error callback
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugMessageCallback, NULL);

	// fix mouse cursor to the middle
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	Renderer renderer;
	
	ShaderProgram shaderProgram("Resource/Shaders/Vertex.shader", "Resource/Shaders/Fragment.shader");
	ShaderProgram skyboxShader("Resource/Shaders/SkyboxVertex.shader", "Resource/Shaders/SkyboxFragment.shader");
	Camera camera;

	Skybox skybox;
	Light lightSource(-100.0f,100.0f,-10.0f,1.0f,1.0f,1.0f);

	// helper variables for motion
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	float currentFrame = 0.0f;

	// camera callback
	//glfwSetCursorPosCallback(window, mouseCallback);
	double offsetX = 0;
	double offsetY = 0;
	double lastX = WINDOW_WIDTH / 2;
	double lastY = WINDOW_HEIGHT / 2;
	double xpos = 0, ypos = 0;
	bool firstMouse = true;

	// test for model imports
	//Model* cube = OBJManager::getModelFromObj("Resource/Model/SampleCube/cube.obj");
	Model* island = OBJManager::getModelFromObj("Resource/Model/IslandBase/island_base.obj");
	Model* building = OBJManager::getModelFromObj("Resource/Model/Building/building.obj");
	Model* windmill = OBJManager::getModelFromObj("Resource/Model/Windmill/windmill3.obj");
	Model* tree = OBJManager::getModelFromObj("Resource/Model/Tree/tree.obj");
	//Model* dragon = OBJManager::getModelFromObj("Resource/Model/Dragon/dragon.obj");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// mouse camera adjustment
		glfwGetCursorPos(window, &xpos, &ypos);
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		// compute camera looks
		offsetX = xpos - lastX;
		offsetY = lastY - ypos;
		lastX = xpos;
		lastY = ypos;
		camera.lookTo(offsetX, offsetY);
		
		// compute delta for smooth movements in different machines
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera.setDelta(deltaTime);

		// process the input and perform warping in the camera object
		processInputCamera(window, camera);
		
		{
			renderer.prepare();
			glm::mat4 viewMatrix = camera.getCameraTransform();

			renderer.drawRotatingModel(*windmill, viewMatrix, shaderProgram, lightSource);
			renderer.drawModel(*tree, viewMatrix, shaderProgram, lightSource);
			renderer.drawModel(*building, viewMatrix, shaderProgram, lightSource);
			renderer.drawModel(*island, viewMatrix, shaderProgram, lightSource);
			//renderer.drawModel(*cube, viewMatrix, shaderProgram, lightSource);

			renderer.drawSkybox(skybox, viewMatrix, skyboxShader);
		}
		
		// render ui
		ImGui_ImplGlfwGL3_NewFrame();
		{
			ImGui::Begin("Status");
			ImGui::SetWindowPos(ImVec2(ImGui::GetWindowWidth() - 340, ImGui::GetWindowHeight() - 60));
			ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	// cleanups
	delete island;
	delete building;
	delete windmill;
	delete tree;
	//delete cube;
	//delete dragon;

	glfwTerminate();
	return 0;
}