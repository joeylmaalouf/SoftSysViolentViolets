#include "camera.h"
#include "util.h"
#include <SOIL.h>
#include "Shader.h"


const GLchar* vertexShaderSource = "#version 120\n"
    "in vec3 position;\n"
    "in vec3 color;\n"
    "in vec3 texCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0f);\n"
    "ourColor = color;\n"
    "TexCoord = texCoord;\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 120\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;"
    "out vec4 color;\n"
    "uniform sampler2D ourTexture;\n"
    "void main()\n"
    "{\n"
    "color = texture(ourTexture, TexCoord);\n"
    "}\n\0";


void drawBox() {
    GLuint vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
GLint success;
GLchar infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}

GLuint fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
GLuint shaderProgram;
shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
     GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    glGenVertexArraysAPPLE(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArrayAPPLE(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArrayAPPLE(0); // Unbind VAO


   GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
  int width, height;
  unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
 // Bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // Activate shader

        glUseProgram(shaderProgram);
        // Draw container
        glBindVertexArrayAPPLE(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArrayAPPLE(0);

}

void drawCube (vector<int> pos, vector<int> col, int size, int draw_flag) {
  float x = static_cast<float>(pos[0]);
  float y = static_cast<float>(pos[1]);
  float z = static_cast<float>(pos[2]);

  glPushMatrix();
  glTranslatef(x, y, z);
  glColor4b(col[0], col[1], col[2], 127);

  if (draw_flag == GL_LINES) {
    glEnable(GL_BLEND);
    glutWireCube(size);
  } else {
    glDisable(GL_BLEND);
    glutSolidCube(size);
  }

  glPopMatrix();
}

void Camera::display (World *world) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  aspect = w / h;
  gluPerspective(fovy, aspect, zNear, zFar);

  // Set up the model matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

  // Set the camera rotation
  glRotated(rotationX, 1.0, 0.0, 0.0);
  glRotated(rotationY, 0.0, 1.0, 0.0);
  glRotated(rotationZ, 0.0, 0.0, 1.0);

  drawBox();
  // Draw the voxels and cursor in the world
  map<vector<int>, Voxel *> grid = world->getGrid();
  for (const auto &p : grid) {
    drawCube(p.first, p.second->getColor(), 1, GL_POLYGON);
  }

  Cursor *cursor = world->getCursor();
  int radius = cursor->getSize();
  drawCube(cursor->getPosition(), cursor->getColor(), 2 * radius - 1, GL_LINES);

  // Animation uses double-buffering
  glutSwapBuffers();
}

void Camera::rotateX (int degrees) {
    rotationX = fmod(rotationX + degrees, 360);
}

void Camera::rotateY (int degrees) {
    rotationY = fmod(rotationY + degrees, 360);
}

void Camera::rotateZ (int degrees) {
    rotationZ = fmod(rotationZ + degrees, 360);
}

void Camera::zoom (double scalar) {
    eyeX *= scalar;
    eyeY *= scalar;
    eyeZ *= scalar;
}

void Camera::reset () {
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
}
