#pragma once
#include <glm/ext.hpp>
#include "Camera.h"

glm::mat4 makeTransMatrix(const Camera& camera);
glm::mat4 makeViewMatrix(const Camera& camera);