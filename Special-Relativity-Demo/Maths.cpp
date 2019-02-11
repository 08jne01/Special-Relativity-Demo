#include "Maths.h"

glm::mat4 makeTransMatrix(const Camera& camera)

{
	glm::mat4 matrix(1.0);
	matrix = glm::translate(matrix, camera.pos);
	return matrix;
}

glm::mat4 makeViewMatrix(const Camera& camera)

{
	glm::mat4 matrix(1.0);
	matrix = glm::rotate(matrix, glm::radians(camera.rot.z), { 0, 0, 1 });
	matrix = glm::rotate(matrix, glm::radians(camera.rot.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rot.x), { 1, 0, 0 });
	//matrix = glm::translate(matrix, camera.pos);
	return matrix;
}