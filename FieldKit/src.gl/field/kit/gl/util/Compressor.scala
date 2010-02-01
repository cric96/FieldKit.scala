/*                                                                            *\
**           _____  __  _____  __     ____     FieldKit                       **
**          / ___/ / / /____/ / /    /    \    (c) 2009, field                **
**         / ___/ /_/ /____/ / /__  /  /  /    http://www.field.io            **
**        /_/        /____/ /____/ /_____/                                    **
\*                                                                            */
/* created May 19, 2009 */
package field.kit.gl.util

import field.kit._
import scala.actors.Actor

/**
 * an actor based image compressor uses an actor per cpu core to parallize compression of BufferedImages via ImageIO
 */
object Compressor extends Actor with Logger {
  import scala.actors.Actor._
  import scala.collection.mutable.ArrayBuffer
  
  import java.io.File
  import java.nio.ByteBuffer
  import java.awt.image.DataBufferByte
  import java.awt.image.BufferedImage

  // fields
  val threads = Runtime.getRuntime.availableProcessors
  val processors = new Array[ProcessorState](threads)
  val images = new ArrayBuffer[ImageState]()
  val master = this
  
  protected var isInitialized = false
  
  start
  
  /** requests an image and buffer with the given dimensions */
  def init(width:Int, height:Int, alpha:Boolean) = {
    val list = images filter (s => s.isAvailable)
    val is = if(list.size == 0 ) {
      val is = new ImageState
      images += is
      is
    } else {
      list(0)
    }
    
    // check if we need to (re)create the image and its buffer
    is.init(width, height, alpha)
    
    // mark image as in use
    is.busy  
    (is.image, is.buffer)
  }
  
  def act {
    for(i <- 0 until processors.size) 
      processors(i) = new ProcessorState(new Processor(i))
    
    isInitialized = true
    
    loop {
      react {
        case Done(image) => 
          processors filter (_.processor == sender) foreach (_.free)
          images filter (_.image == image) foreach(_.free)
      }
    }
  }
  
  /**
   * queues another image for compression
   */
  def apply(image:BufferedImage, format:String, file:File) = {
    // wait until this object is properly initialized 
    while(!isInitialized) {
      Thread.sleep(1)
    }
    
    // process image
    var isProcessing = false
    do {
      val p = processors filter (_.isAvailable)
      if(p.size > 0) {
        p(0).busy
        p(0).processor ! Compress(image, format, file)
        isProcessing = true
      } else {
        Thread.sleep(1)
      }
    } while(!isProcessing)
  }
  
  // ------------------------------------------------------------------------------------
  /** tells an image processor to get going*/
  case class Compress(image:BufferedImage, format:String, file:File)
  
  case class Done(image:BufferedImage)

  // ------------------------------------------------------------------------------------
  /** holds the availability state for the given element */
  abstract class StateRecord {
    var isAvailable = true
    def busy = isAvailable = false
    def free = isAvailable = true
  }
  
  protected class ProcessorState(var processor:Processor) extends StateRecord
  
  protected class ImageState extends StateRecord {
    var image:BufferedImage = null
    var buffer:ByteBuffer = null
    
    def init(width:Int, height:Int, alpha:Boolean) {
      var reinit = false
      if(image == null || image.getWidth != width || image.getHeight != height) {
        reinit = true
      }
      if(reinit) {
        val format = if(alpha) BufferedImage.TYPE_4BYTE_ABGR else BufferedImage.TYPE_3BYTE_BGR
        image = new BufferedImage(width, height, format)
        buffer = ByteBuffer.wrap((image.getRaster.getDataBuffer.asInstanceOf[DataBufferByte]).getData)
      }
    }
  }
  
  // ------------------------------------------------------------------------------------
  /** represents a single image processor that does the actual encoding work */
  protected class Processor(id:Int) extends Actor with Logger {
    import com.sun.opengl.util.ImageUtil
    import javax.imageio.ImageIO
    
    logName = "Processor("+ id +")"
    
    start
    
    def act {
      loop {
        react {
          case Compress(image, format, file) =>
            info(file, "...")
            ImageUtil.flipImageVertically(image)
            ImageIO.write(image, format, file)
            master ! Done(image)
        }
      }
    }
  }
}