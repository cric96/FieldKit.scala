/*                                                                            *\
**           _____  __  _____  __     ____                                    **
**          / ___/ / / /____/ / /    /    \    FieldKit                       **
**         / ___/ /_/ /____/ / /__  /  /  /    (c) 2009, field.io             **
**        /_/        /____/ /____/ /_____/     http://www.field.io            **
\*                                                                            */
/* created October 27, 2009 */

#ifndef CV_BLOB_DETECTOR_H
#define CV_BLOB_DETECTOR_H

#include <OpenCV/cvcompat.h>
#include "CVFrameProcessor.h"
#include "Blob.h"

namespace field 
{
	//
	// OpenCV Blob Detector
	//
	class CVBlobDetector : public CVFrameProcessor
	{
	#pragma mark -- public --
	public:
		// ---------------------------------------------------------------------------------------
		// Constants
		// ---------------------------------------------------------------------------------------
		enum Image {
			IMAGE_INPUT,
			IMAGE_INPUT_RESIZED,
			IMAGE_SRC32F,
			IMAGE_DST32F,
			IMAGE_SRC8U,
			IMAGE_DST8U,
			IMAGE_BG
		};
		
		enum StageName { STAGE_INPUT, 
						 STAGE_WARP, 
						 STAGE_BACKGROUND, 
						 STAGE_DIFFERENCE,
						 STAGE_THRESHOLD, 
						 STAGE_DILATE, 
						 STAGE_ERODE,
						 STAGE_CONTOUR,
						 STAGE_DETECTION, 
						 STAGE_TRACKING, 
						 STAGE_MAX 
		};
		
		enum SliderName { SLIDER_BACKGROUND, 
						  SLIDER_THRESHOLD, 
						  SLIDER_DILATE, 
						  SLIDER_ERODE, 
						  SLIDER_CONTOUR_MIN, 
						  SLIDER_CONTOUR_MAX, 
						  SLIDER_CONTOUR_REDUCE,
						  SLIDER_TRACK_RANGE, 
						  SLIDER_MAX 
		};
		
		enum Mode { MODE_8U,
					MODE_32F
		};
		
		// ---------------------------------------------------------------------------------------
		// Public Methods
		// ---------------------------------------------------------------------------------------
		CVBlobDetector();
		~CVBlobDetector();
		
		Error init();
		Error update(Camera *camera);
		Error deinit();
		
		// getters
		Blob** getBlobs();
		int getBlobNum() { return blobNum; };
		
		// setters
		void setCameraSource(int source) { cameraSource = source; };
		void setWarp(float sx1, float sy1,
					 float sx2, float sy2,
					 float sx3, float sy3,
					 float sx4, float sy4);	

	#pragma mark -- protected --
	protected:
		// ---------------------------------------------------------------------------------------
		// Fields
		// ---------------------------------------------------------------------------------------
		int cameraSource;

		// only used for drawing the blobs
		CvFont font;
		
		// references to the 8U or 32F image variants
		// depends on the image mode
		IplImage* srcImage;
		IplImage* dstImage;

		IplImage* srcImage8U;
		IplImage* dstImage8U;
		IplImage* srcImage32F;
		IplImage* dstImage32F;
		
		// image mode
		Mode mode;
		
		// warp
		CvMat* warpMatrix;
		bool warpEnabled;
		
		// flags
		bool doResetBackground;;
		bool useAdaptiveTresholding;
		
		// blobs, contours & finger
		CvMemStorage *contourStorage;
		CvSeq *contourFirst;
		CvPoint center;
		Blob **foundBlobs;
		Blob **trackedBlobs;
		int blobNum;

		// ---------------------------------------------------------------------------------------
		// Helper & Utiltiy Methods
		// ---------------------------------------------------------------------------------------
		// contours
		void findContours();
		void drawContours();
		
		// blobs
		void findBlobs();
		void trackBlobs();
		void drawBlobs(int stage, Blob* blobs[]);
		
		// helpers
		void setMode(Mode mode); // sets the image format during the analysis process
		void swap();
		
	#pragma mark -- private --
	private:
		Error err;	
	};
};
#endif