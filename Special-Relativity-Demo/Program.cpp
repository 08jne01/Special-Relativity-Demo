#include "Program.h"

Program::Program(int w, int h) : width(w), height(h), timestep(0.02), camera(0.02), eventHandler(camera)

{

}

int Program::mainLoop()

{
	if (!glfwInit())

	{
		std::cout << "GLFW did not init!" << std::endl;
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Totally Accurate Sam Simulator", NULL, NULL);

	if (!window)

	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))

	{
		std::cout << "Failed to init GLAD!" << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Needed for mousecontrol

	glfwSetWindowUserPointer(window, this);
	glfwSwapInterval(1);
	glClearColor(0.3, 0.8, 0.8, 1.0);

	Shader vertexShader(GL_VERTEX_SHADER, "Resources/Shaders/RayMarchingVertex.shader");
	Shader fragmentShader(GL_FRAGMENT_SHADER, "Resources/Shaders/RayMarchingFrag.shader");

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader.getID());
	glAttachShader(shaderProgram, fragmentShader.getID());
	glLinkProgram(shaderProgram);

	//vertexShader.deleteShader();
	//fragmentShader.deleteShader();

	float vertices[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};
	unsigned int indices[] =

	{
		0, 1, 2,
		0, 3, 2
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Projectile projectile(timestep);

	while (!glfwWindowShouldClose(window))

	{
		projectile.update();
		camera.update();
		eventHandler.update();

		glClear(GL_COLOR_BUFFER_BIT);

		int res = glGetUniformLocation(shaderProgram, "res");
		glUniform2f(res, width, height);

		int arrows = glGetUniformLocation(shaderProgram, "arrows");
		glUniform2f(arrows, eventHandler.arrowRight, eventHandler.arrowUp);

		int view = glGetUniformLocation(shaderProgram, "cam_rot");
		glm::mat4 viewMat = makeViewMatrix(camera);
		glUniformMatrix4fv(view, 1, GL_FALSE, &viewMat[0][0]);

		int trans = glGetUniformLocation(shaderProgram, "cam_trans");
		glm::mat4 transMat = makeTransMatrix(camera);
		glUniformMatrix4fv(trans, 1, GL_FALSE, &transMat[0][0]);

		int pos = glGetUniformLocation(shaderProgram, "pos");
		glm::vec3 positionVec = projectile.getPosition();
		glUniform3f(pos,positionVec.x, positionVec.y, positionVec.z);

		int vel = glGetUniformLocation(shaderProgram, "vel");
		glm::vec3 velVec = projectile.getVelocity();
		//std::cout << glm::normalize(velVec).x << glm::normalize(velVec).y << glm::normalize(velVec).z << std::endl;
		glUniform3f(vel, velVec.x, velVec.y, velVec.z);


		int camVel = glGetUniformLocation(shaderProgram, "cam_vel");
		glm::vec3 cameraVel = camera.coordVel;
		glUniform3f(camVel, cameraVel.x, cameraVel.y, cameraVel.z);

		std::cout << cameraVel.x << " + " << velVec.x << " = " << cameraVel.x + velVec.x << std::endl;

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}

void Program::framebuffer_size_callback(GLFWwindow* window, int w, int h)

{
	glViewport(0, 0, w, h);
	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);
	kptr->width = w;
	kptr->height = h;
}

void Program::key_callback(GLFWwindow* window, int button, int scancode, int action, int mods)

{
	if (action == GLFW_PRESS && button == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, true);



	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);
	kptr->eventHandler.keyHandler(action, button);
}

void Program::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)

{
	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);
	kptr->eventHandler.mouseHandler(xpos, ypos);
}

void Program::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)

{
	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);
	kptr->eventHandler.mouseButtonHandler(action, button);
}

void Program::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)

{
	void* ptr = glfwGetWindowUserPointer(window);
	Program *kptr = static_cast<Program*>(ptr);
	kptr->eventHandler.scrollHandler(yoffset);
}