//
//  Camera.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Camera.h"

glm::mat4 Camera::view, Camera::projection;
glm::mat4 Camera::vp;

void Camera::init(float width, float height, const glm::vec3& position, const glm::vec3& target) {
    view = glm::lookAt(position, target, glm::vec3(0, 1, 0));
    projection = glm::perspective(45.0f, (float) width / (float) height, 0.1f, 1000.0f);
    Camera::update();
}