#include <glad/glad.h> //gladͷ�ļ�һ��Ҫ������ǰ�治Ȼ�ᱨ��
#include <GLFW\glfw3.h>
#include <iostream>
//������ɫ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.3f, 0.7f, 0.2f, 1.0f);\n"
"}\n\0";
/*����opengl�Ӵ��Ĵ�С*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
/*����input������Esc��*/
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
int main()
{
	glfwInit(); //��ʼ��GLFW
	//����GLFW�� glfwWindowHint�����ĵ�һ����������ѡ������ƣ��ڶ�����������һ�����ͣ������������ѡ���ֵ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core_profile����ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//����һ����ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//�������ɫ��Դ�븽�ӵ���ɫ�������ϣ�����
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//�жϱ����Ƿ�ɹ�
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//����Ƭ����ɫ������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//����
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//�ж�Ƭ����ɫ�������Ƿ�ɹ�
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//�����������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//������ɫ��
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//��֤�Ƿ�ɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//�������ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//�����εĶ�������
	float vertices[] = {
	-0.2f, -0.5f, 0.0f,
	 0.2f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	//����һ��VBO����
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//����һ��VAO����
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//��VAO
	glBindVertexArray(VAO);
	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//���Ӷ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//������Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ����
		processInput(window);

		// ��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// ��鲢�����¼�����������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}