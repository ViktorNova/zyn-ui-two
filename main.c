#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "nanovg/nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg/nanovg_gl.h"
#include "draw.h"
#include "view.h"
//#include "perf.h"

static void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    printf("Key event...\n");
}

int main()
{
	GLFWwindow* window;
    NVGcontext *vg;

    if(!glfwInit()) {
        fprintf(stderr, "Failed to start glfw\n");
        return -1;
    }

	
    //Set OpenGL Revision
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
    //Create Window
	window = glfwCreateWindow(1000, 600, "NanoVG", NULL, NULL);
	if (!window) {
        fprintf(stderr, "Failed to make window\n");
		glfwTerminate();
		return -1;
	}


    //Setup Context
    glfwSetKeyCallback(window, key);
	glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to start GLEW\n");
        return -1;
    }

    vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    nvgCreateFont(vg, "sans", "Roboto-Regular.ttf");
	nvgCreateFont(vg, "icons", "entypo.ttf");
	
    glfwSwapInterval(0);

	glfwSetTime(0);
	long prevt = glfwGetTime();


	while (!glfwWindowShouldClose(window))
	{
		double mx, my, t, dt;
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;

		glfwGetCursorPos(window, &mx, &my);
		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);
        //glClearColor(0x06/255.0, 0x27/255.0, 0x37/255.0, 1.0f);
        glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

        //viewReverb(vg, 0,0, winWidth, winHeight);
        viewModule(vg, "afilter", 0,0,winWidth, winHeight);
        //viewLFO(vg, 0,0, winWidth, winHeight);
        //viewFilterEnv(vg, 0,0, winWidth, winHeight);
                       //y   x    y   x     y    x    y   x   y   x
        //float in[10] = {0.0, 0.0, 0.5, 0.2, 0.3, 0.7,-0.9,0.8,0.0,1.0};
        //drawEnvEdit(vg, in, 5, 3, 0, 0, winWidth, winHeight);

#if 0
        dial_t dial = {60, 0, 0, 100, "label"};
        renderDial(vg, dial);
        drawButton(vg, "banana", 100, 25, 100, 50);
        drawOptButton(vg, "opt", 200, 25, 100, 50);
        drawButtonGrid(vg, 4,4, 300, 0, 100, 100);
        drawAltDial(vg, 400, 0, 100, 100);
        drawGrid(vg, 8, 8, 500, 0, 200, 200);
        drawSin(vg,  500, 0, 200, 200);
#endif

		nvgEndFrame(vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	nvgDeleteGL2(vg);
	glfwTerminate();
	return 0;
}
