/*                                                                            *\
**           _____  __  _____  __     ____                                    **
**          / ___/ / / /____/ / /    /    \    FieldKit                       **
**         / ___/ /_/ /____/ / /__  /  /  /    (c) 2009, field.io             **
**        /_/        /____/ /____/ /_____/     http://www.field.io            **
\*                                                                            */
/* created October 27, 2009 */

#include "Camera.h"

namespace field {
	// -------------------------------------------------------------------------
	// CON- & DESTRUCTORS
	// -------------------------------------------------------------------------
	Camera::Camera() {
		isInitialized = false;
		isStarted = false;
		color = false;
		width = VISION_DEFAULT_WIDTH;
		height = VISION_DEFAULT_HEIGHT;
		fps = VISION_DEFAULT_FPS;
	}
	
	Camera::~Camera() {
		this->close();
	}
	
	// -------------------------------------------------------------------------
	// SETTERS
	// -------------------------------------------------------------------------
	void Camera::setSize(int width, int height) {
		if(isStarted) {
			LOG_ERR("Camera: Cannot set size, since camera is already started.");
			return;
		}
		this->width = width;
		this->height = height;
	}
	
	void Camera::setFramerate(int fps) {
		if(isStarted) {
			LOG_ERR("Camera: Cannot set framerate, since camera is already started.");
			return;
		}
		this->fps = fps;
	}

	// -------------------------------------------------------------------------
	// INIT
	// -------------------------------------------------------------------------
	int Camera::init() {
		isInitialized = true;
		return SUCCESS;
	}
	
	// -------------------------------------------------------------------------
	// START
	// -------------------------------------------------------------------------
	int Camera::start() {
		// check if we need to initialize first
		if(!isInitialized) {
			err = this->init();
			if(err != SUCCESS) return err;
		}
		
		isStarted = true;
		
		return SUCCESS;
	}
	
	// -------------------------------------------------------------------------
	// UPDATE
	// -------------------------------------------------------------------------
	int Camera::update() {
		return SUCCESS;
	}
	
	// -------------------------------------------------------------------------
	// STOP
	// -------------------------------------------------------------------------
	int Camera::stop() {
		isStarted = false;
		return SUCCESS;
	}
	
	// -------------------------------------------------------------------------
	// CLOSE
	// -------------------------------------------------------------------------
	int Camera::close() {
		if(isStarted) 
			this->stop();
			
		isInitialized = false;
		return SUCCESS;
	}

	// -------------------------------------------------------------------------
	// GET IMAGE
	// -------------------------------------------------------------------------
	IplImage* Camera::getImage(int channel) {
		return NULL;
	}
}