// DesktopOGLwSDL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GLFW/glfw3.h>
//#include <GLFW/glfw3native.h>


void loadObject(void){
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< GLfloat > temp_vertices;
    std::vector< GLfloat > temp_uvs;
    std::vector< GLfloat > temp_normals;

    FILE * file = NULL;
    fopen_s(&file,"../../Resources/3DObject/cube.obj", "r");
    if (file == NULL){
        printf("Impossible to open the file !\n");
        return;
    }

    while (1){

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf_s(file, "%s\n", lineHeader, sizeof(lineHeader));
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0){
            GLfloat vertex_x, vertex_y, vertex_z;
            fscanf_s(file, "%f %f %f\n", &vertex_x, &vertex_y, &vertex_z);
            temp_vertices.push_back(vertex_x);
            temp_vertices.push_back(vertex_y);
            temp_vertices.push_back(vertex_z);


        }


        //else if (strcmp(lineHeader, "vt") == 0){
        //    glm::vec2 uv;
        //    fscanf(file, "%f %f\n", &uv.x, &uv.y);
        //    temp_uvs.push_back(uv);

        //}
        //else if (strcmp(lineHeader, "vn") == 0){
        //    glm::vec3 normal;
        //    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
        //    temp_normals.push_back(normal);

        //}
        else if (strcmp(lineHeader, "f") == 0){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf_s(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
            if (matches != 6){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
        }

        //    uvIndices.push_back(uvIndex[0]);
        //    uvIndices.push_back(uvIndex[1]);
        //    uvIndices.push_back(uvIndex[2]);
        //    normalIndices.push_back(normalIndex[0]);
        //    normalIndices.push_back(normalIndex[1]);
        //    normalIndices.push_back(normalIndex[2]);
        //}
    }

    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    //glScalef(1 / 200, 1 / 299, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState(GL_VERTEX_ARRAY);

    GLfloat vertex[] = { 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        0.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 0.0, 0.0
    };

    std::vector <GLfloat> verts = { -1.0, -1.0, 0.0,
        -1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        -1.0, -1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, -1.0, 0.0
    };

    glVertexPointer(3, GL_FLOAT, 0, verts.data());
    glVertexPointer(3, GL_FLOAT, 0, temp_vertices.data());
    //glVertexPointer(3, GL_FLOAT, 0, &vertex[0]);
    glTranslatef(0.0f, 0.0f, -1.5f);
    glDrawArrays(GL_TRIANGLES, 0, 8);
    //glDrawElements(GL_TRIANGLES, 0, GL_FLOAT, &vertexIndices[0]);
}

int _tmain(int argc, _TCHAR* argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        loadObject();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



