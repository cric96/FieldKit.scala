/*                                                                            *\
**           _____  __  _____  __     ____                                    **
**          / ___/ / / /____/ / /    /    \    FieldKit                       **
**         / ___/ /_/ /____/ / /__  /  /  /    (c) 2009, field.io             **
**        /_/        /____/ /____/ /_____/     http://www.field.io            **
\*                                                                            */
/* created October 27, 2009 */

#include "OpenCVCamera.h"

namespace field 
{
	OpenCVCamera::OpenCVCamera(int cameraIndex) {
		this->cameraIndex = cameraIndex;
	}
	
	// -------------------------------------------------------------------------
	// INIT
	// -------------------------------------------------------------------------
	int OpenCVCamera::init()
	{
		if(isStarted) {
			LOG_ERR("OpenCVCamera: Cannot initialize, since camera is already started.");
			return FK_ERROR;
		}
				
		capture = cvCreateCameraCapture(cameraIndex);
		
		if(!capture) {
			LOG_ERR("OpenCVCamera: Couldnt create camera capture.");
			return FK_ERROR;
		}
		
		//printf("OpenCVCamera: requested %i x %i\n", width, height);
		
		// only seems to be implemented in the opencv linux (ffmpeg or gstreamer based) versions
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, width);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, height);
		cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, fps);

		// grab one frame to figure out the actual dimensions of the camera image
		update();
		
		width = getImage()->width;
		height = getImage()->height;
		
		//printf("OpenCVCamera: actual %i x %i\n", width, height);
		
		return super::init();
	}
	
	// -------------------------------------------------------------------------
	// CLOSE
	// -------------------------------------------------------------------------
	int OpenCVCamera::close()
	{
		cvReleaseCapture(&capture);
		return super::close();
	}
	
	// -------------------------------------------------------------------------
	// UPDATE
	// -------------------------------------------------------------------------
	int OpenCVCamera::update()
	{
		if(cvGrabFrame(capture)) return FK_SUCCESS;
		return FK_ERROR;
	}
	
	// -------------------------------------------------------------------------
	// HELPERS
	// -------------------------------------------------------------------------
	#pragma mark -- Helpers --
	IplImage* OpenCVCamera::getImage(int channel)
	{
		return cvRetrieveFrame(capture);
	}
}