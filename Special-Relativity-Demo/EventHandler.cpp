#include "EventHandler.h"

EventHandler::EventHandler(Camera& cam) : camera(cam), speed(0.1), arrowUp(0), arrowRight(0), arrowPressedRight(0), arrowPressedUp(0) //0.001

{

}

void EventHandler::update()

{
	arrowUp += 0.01*(float)arrowPressedUp;
	arrowRight += 0.01*(float)arrowPressedRight;
}

void EventHandler::keyHandler(int action, int button)

{



	if (action == GLFW_PRESS)

	{
		switch (button)

		{
		case GLFW_KEY_W:
		{
			camera.setVel(2, 1.0);
			break;
		}

		case GLFW_KEY_A:
		{
			camera.setVel(0, 1.0);
			break;
		}

		case GLFW_KEY_S:
		{
			camera.setVel(2, -1.0);
			break;
		}

		case GLFW_KEY_D:
		{
			camera.setVel(0, -1.0);
			break;
		}

		case GLFW_KEY_LEFT_SHIFT:
		{
			camera.speed = 10 * speed;
			break;
		}

		case GLFW_KEY_SPACE:
		{
			camera.setVel(1, -1.0);
			break;
		}

		case GLFW_KEY_LEFT_CONTROL:
		{
			camera.setVel(1, 1.0);
			break;
		}

		case GLFW_KEY_LEFT:

		{
			std::cout << "Right Arrow Value: " << arrowRight << std::endl;
			arrowPressedRight = -1;
			break;
		}

		case GLFW_KEY_RIGHT:

		{
			std::cout << "Right Arrow Value: " << arrowRight << std::endl;
			arrowPressedRight = 1;
			break;
		}

		case GLFW_KEY_UP:

		{
			std::cout << "Up Arrow Value: " << arrowUp << std::endl;
			arrowPressedUp = 1;
			break;
		}

		case GLFW_KEY_DOWN:

		{
			std::cout << "Up Arrow Value: " << arrowUp << std::endl;
			arrowPressedUp = -1;
			break;
		}
		}
	}

	if (action == GLFW_RELEASE)

	{
		switch (button)

		{
		case GLFW_KEY_W:
		{
			camera.setVel(2, 0.0);
			break;
		}

		case GLFW_KEY_A:
		{
			camera.setVel(0, 0.0);
			break;
		}

		case GLFW_KEY_S:
		{
			camera.setVel(2, 0.0);
			break;
		}

		case GLFW_KEY_D:
		{
			camera.setVel(0, 0.0);
			break;
		}

		case GLFW_KEY_LEFT_SHIFT:
		{
			camera.speed = speed;
			break;
		}

		case GLFW_KEY_SPACE:
		{
			camera.setVel(1, 0.0);
			break;
		}

		case GLFW_KEY_LEFT_CONTROL:
		{
			camera.setVel(1, 0.0);
			break;
		}

		case GLFW_KEY_LEFT:

		{
			std::cout << "Right Arrow Value: " << arrowRight << std::endl;
			arrowPressedRight = 0;
			break;
		}

		case GLFW_KEY_RIGHT:

		{
			std::cout << "Right Arrow Value: " << arrowRight << std::endl;
			arrowPressedRight = 0;
			break;
		}

		case GLFW_KEY_UP:

		{
			std::cout << "Up Arrow Value: " << arrowUp << std::endl;
			arrowPressedUp = 0;
			break;
		}

		case GLFW_KEY_DOWN:

		{
			std::cout << "Up Arrow Value: " << arrowUp << std::endl;
			arrowPressedUp = 0;
			break;
		}
		}
	}


}

void EventHandler::scrollHandler(double yoffset)

{
	camera.cameraSetSpeed(yoffset);
}

void EventHandler::mouseHandler(double xpos, double ypos)

{
	camera.setAngVel(xpos, ypos);
}

void EventHandler::mouseButtonHandler(int action, int button)

{
	if (action == GLFW_PRESS)

	{
		switch (button)

		{
		case GLFW_MOUSE_BUTTON_1:

		{
			camera.speed *= 1.1;
			break;
		}

		case GLFW_MOUSE_BUTTON_2:

		{
			camera.speed /= 1.1;
			break;
		}
		}
	}

}