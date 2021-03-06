/*                                                                            *\
**           _____  __  _____  __     ____                                    **
**          / ___/ / / /____/ / /    /    \    FieldKit                       **
**         / ___/ /_/ /____/ / /__  /  /  /    (c) 2010, FIELD                **
**        /_/        /____/ /____/ /_____/     http://www.field.io            **
\*                                                                            */
/* created March 01, 2010 */
package field.kit.physics.behaviours

import field.kit._
import field.kit.physics._
import field.kit.math.geometry._

/**
 * Drags the particle towards a certain point in space
 * @author marcus
 */
class AttractorPoint extends Vec3 with Behaviour {
	
	var weight = 1f
	range = 100f
	
	def range_=(v:Float) {
		range_ = v
		rangeSq = v * v
	}
	def range = range_
	
	protected var range_ = 0f
	protected var rangeSq = 0f
	
	protected val tmp = new Vec3
	
	def this(v:Vec3, weight:Float) {
		this()
		this := v
		this.weight = weight
		this
	}
	
	def apply(p:Particle) {
		// create vector from particle to curve point
		val delta = (tmp := this) -= p
		
		// check if particle is in range of the attractor
		val distSq = delta.lengthSquared
		
		if(distSq < rangeSq) {
			val dist = sqrt(distSq)
			// normalize and inverse proportional weight
			p.force += (delta /= dist) *= ((1.0f - dist/ range) * weight)
		}
	}
}


import field.kit.math.geometry.Sphere

/**
 * An orbital force across the surface of a sphere  
 * @author marcus
 */
class AttractorOrbit(position:Vec3, radius:Float)
extends Sphere(position, radius) with Behaviour {

	var direction = new Vec2(0.0010f, 0.0025f)
	var weight = 0.25f
	
	private val tmp = new Vec3
	
	def apply(p:Particle) {
		val rotX = p.age * direction.x
		val rotY = p.age * direction.y
		
		tmp.x = this.x + (sin(rotX) * sin(rotY)) * radius
		tmp.y = this.y + (cos(rotX) * sin(rotY)) * radius
		tmp.z = this.z + cos(rotY) * radius
		 
		tmp -= p
		tmp.normalize
		tmp *= weight

		p.force += tmp
	}
}
