/*                                                                            *\
**           _____  __  _____  __     ____                                    **
**          / ___/ / / /____/ / /    /    \    FieldKit                       **
**         / ___/ /_/ /____/ / /__  /  /  /    (c) 2009, field.io             **
**        /_/        /____/ /____/ /_____/     http://www.field.io            **
\*                                                                            */
/* created October 27, 2009 */

#include "Vision.h"

namespace field
{
	Vision::Vision() {
		isInitialized = false;
		isStarted = false;
		width = VISION_DEFAULT_WIDTH;
		height = VISION_DEFAULT_HEIGHT;
		fps = VISION_DEFAULT_FPS;
	}
	
	Vision::~Vision()
	{
		stop();
		camera->close();
		delete camera;	
		delete processor;
	}

	// -------------------------------------------------------------------------
	// SETTERS
	// -------------------------------------------------------------------------
	void Vision::setSize(int width, int height) {
		if(isStarted) {
			LOG_ERR("Vision: Cannot set size, since vision is already started.");
			return;
		}
		this->width = width;
		this->height = height;
	}
	
	void Vision::setFramerate(int fps) {
		if(isStarted) {
			LOG_ERR("Vision: Cannot set framerate, since camera is already started.");
			return;
		}
		this->fps = fps;
	}
	
	void Vision::setCamera(Camera *camera) { 
		if(isStarted) {
			LOG_ERR("Vision: Cannot set camera, since camera is already started.");
			return;
		}		
		this->camera = camera; 
	}
	
	void Vision::setProcessor(CVFrameProcessor *processor) {
		if(isStarted) {
			LOG_ERR("Vision: Cannot set frame processor, since camera is already started.");
			return;
		}		
		this->processor = processor; 
	}
	
	
	// -------------------------------------------------------------------------
	// INIT
	// -------------------------------------------------------------------------
	int Vision::init()
	{
		// initialize camera
		if(camera == NULL) {
			LOG_ERR("Vision: Cannot initialize, since there is no camera set yet.");
			return FK_ERROR;
		}
		camera->setSize(width, height);
		camera->setFramerate(fps);

		int err;
		err = camera->init();
		if(err != FK_SUCCESS) return err;

		// initialize frame processor
		if(processor == NULL) {
			LOG_ERR("Vision: Cannot initialize, since there is no frame processor set yet.");
			return FK_ERROR;
		}

		processor->setSize(width, height);
		processor->setROI(0, 0, width, height);
		
		err = processor->init();
		
		if(err == FK_SUCCESS) isInitialized = true;
		
		return err;
	}

	// -------------------------------------------------------------------------
	// START
	// -------------------------------------------------------------------------
	int Vision::start()
	{
		// check if we need to initialize first
		if(!isInitialized) {
			//LOG("need to initialize");
			err = this->init();
			if(err != FK_SUCCESS) return err;
		}
		
		// all good, begin grabbing frames
		err = camera->start();
		
		if(err == FK_SUCCESS) isStarted = true;
		return err;
	}

	// -------------------------------------------------------------------------
	// STOP
	// -------------------------------------------------------------------------
	int Vision::stop()
	{
		if(!isStarted) return FK_ERROR;

		err = camera->stop();
		
		if(err == FK_SUCCESS) isStarted = false;
		return err;
	}
	
	// -------------------------------------------------------------------------
	// UPDATE
	// -------------------------------------------------------------------------
	int Vision::update()
	{
		if(!isStarted) {
			LOG_ERR("Vision: Cannot update, since vision is not started yet.");
			return FK_SUCCESS;
		}
		
		err = camera->update();
		if(err != FK_SUCCESS) return err;
		
		err = processor->update(camera);
		if(err != FK_SUCCESS) return err;
		
		return FK_SUCCESS;
	};
};