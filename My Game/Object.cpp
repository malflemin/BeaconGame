/// \file Object.cpp
/// \brief Code for the game object class CObject.

#include "Object.h"
#include "ComponentIncludes.h"
#include "GameDefines.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize an object given its sprite type
/// and initial position.
/// \param t Type of sprite.
/// \param p Initial position of object.

CObject::CObject(eSpriteType t, const Vector2& p){ 
  m_nSpriteIndex = t;
  m_vPos = p; 

  m_pRenderer->GetSize(t, m_vRadius.x, m_vRadius.y);
  m_vRadius *= 0.5f;
  
  const Vector2 topleft(-m_vRadius.x, m_vRadius.y);
  const Vector2 bottomrt(m_vRadius.x, -m_vRadius.y);
  BoundingBox::CreateFromPoints(m_Aabb, topleft + m_vPos, bottomrt + m_vPos);

  const unsigned numframes = (unsigned)m_pRenderer->GetNumFrames(m_nSpriteIndex);
  if (numframes > 1)
	  m_nCurrentFrame = 0;

  m_fFrameInterval = 0.1f + 0.02f * m_pRandom->randf();

  m_Sphere.Radius = max(m_vRadius.x, m_vRadius.y);
  m_Sphere.Center = (Vector3)m_vPos;

  m_fGunTimer = m_pStepTimer->GetTotalSeconds();
} //constructor

/// Move and update all bounding shapes.
/// The player object gets moved by the controller, everything
/// else moves an amount that depends on its velocity and the
/// frame time.

void CObject::move(){
  const float t = m_pStepTimer->GetElapsedSeconds();

  if(m_nSpriteIndex == PLAYER_SPRITE){
    m_vVelocity.x = t*m_fSpeed;
    m_vVelocity -= 0.0f*t*Vector2::UnitY;
    m_vPos += 64.0f*t*m_vVelocity;

    const Vector2 viewvec = GetViewVector();
    m_fRoll += m_fRotSpeed*t;
    
    Vector2 norm(viewvec.y, -viewvec.x); 
    const float delta = 40.0f*t;

    if(m_bStrafeRight)
      m_vPos += delta*norm;

    else if(m_bStrafeLeft)
      m_vPos -= delta*norm;

    else if(m_bStrafeBack)
      m_vPos -= delta*viewvec;

    m_bStrafeLeft = m_bStrafeRight = m_bStrafeBack = false;
  } //if

  else m_vPos += m_vVelocity*t;

  if (m_nSpriteIndex == MINER_SPRITE) {
	  m_vVelocity.x = t * m_fSpeed;
	  m_vVelocity -= 20.0f * t * Vector2::UnitY;
	  m_vPos += 64.0f * t * m_vVelocity;

	  const Vector2 viewvec = GetViewVector();
	  m_fRoll += m_fRotSpeed * t;

	  Vector2 norm(viewvec.y, -viewvec.x);
	  const float delta = 40.0f * t;

	  if (m_bStrafeRight)
		  m_vPos += delta * norm;

	  else if (m_bStrafeLeft)
		  m_vPos -= delta * norm;

	  else if (m_bStrafeBack)
		  m_vPos -= delta * viewvec;

	  m_bStrafeLeft = m_bStrafeRight = m_bStrafeBack = false;
	  
  } //if

  if (m_nSpriteIndex == WARRIOR_SPRITE) {
	  m_vVelocity.x = t * m_fSpeed;
	  m_vVelocity -= 20.0f * t * Vector2::UnitY;
	  m_vPos += 64.0f * t * m_vVelocity;

	  const Vector2 viewvec = GetViewVector();
	  m_fRoll += m_fRotSpeed * t;

	  Vector2 norm(viewvec.y, -viewvec.x);
	  const float delta = 40.0f * t;

	  if (m_bStrafeRight)
		  m_vPos += delta * norm;

	  else if (m_bStrafeLeft)
		  m_vPos -= delta * norm;

	  else if (m_bStrafeBack)
		  m_vPos -= delta * viewvec;

	  m_bStrafeLeft = m_bStrafeRight = m_bStrafeBack = false;

  } //if
  if (m_nSpriteIndex == AMBER_SPRITE) {
	  m_vVelocity.x = t * m_fSpeed;
	  m_vVelocity -= 20.0f * t * Vector2::UnitY;
	  m_vPos += 64.0f * t * m_vVelocity;

	  const Vector2 viewvec = GetViewVector();
	  m_fRoll += m_fRotSpeed * t;

	  Vector2 norm(viewvec.y, -viewvec.x);
	  const float delta = 40.0f * t;

	  if (m_bStrafeRight)
		  m_vPos += delta * norm;

	  else if (m_bStrafeLeft)
		  m_vPos -= delta * norm;

	  else if (m_bStrafeBack)
		  m_vPos -= delta * viewvec;

	  m_bStrafeLeft = m_bStrafeRight = m_bStrafeBack = false;
  } //if
	if (m_nSpriteIndex == SAPPHIRE_SPRITE) {
		m_vVelocity.x = t * m_fSpeed;
		m_vVelocity -= 20.0f * t * Vector2::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;

		const Vector2 viewvec = GetViewVector();
		m_fRoll += m_fRotSpeed * t;

		Vector2 norm(viewvec.y, -viewvec.x);
		const float delta = 40.0f * t;
	} //if
	if (m_nSpriteIndex == RUBY_SPRITE) {
		m_vVelocity.x = t * m_fSpeed;
		m_vVelocity -= 20.0f * t * Vector2::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;

		const Vector2 viewvec = GetViewVector();
		m_fRoll += m_fRotSpeed * t;

		Vector2 norm(viewvec.y, -viewvec.x);
		const float delta = 40.0f * t;
	} //if
	if (m_nSpriteIndex == EMERALD_SPRITE) {
		m_vVelocity.x = t * m_fSpeed;
		m_vVelocity -= 20.0f * t * Vector2::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;

		const Vector2 viewvec = GetViewVector();
		m_fRoll += m_fRotSpeed * t;

		Vector2 norm(viewvec.y, -viewvec.x);
		const float delta = 40.0f * t;
	} //if
	if (m_nSpriteIndex == AMETHYST_SPRITE) {
		m_vVelocity.x = t * m_fSpeed;
		m_vVelocity -= 20.0f * t * Vector2::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;

		const Vector2 viewvec = GetViewVector();
		m_fRoll += m_fRotSpeed * t;

		Vector2 norm(viewvec.y, -viewvec.x);
		const float delta = 40.0f * t;
	} //if
	if (m_nSpriteIndex == DIAMOND_SPRITE) {
		m_vVelocity.x = t * m_fSpeed;
		m_vVelocity -= 20.0f * t * Vector2::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;

		const Vector2 viewvec = GetViewVector();
		m_fRoll += m_fRotSpeed * t;

		Vector2 norm(viewvec.y, -viewvec.x);
		const float delta = 40.0f * t;
	} //if
	if (m_nSpriteIndex == BACON_SPRITE) {
		m_vVelocity.x = t * m_fSpeed;
		m_vVelocity -= 20.0f * t * Vector2::UnitY;
		m_vPos += 64.0f * t * m_vVelocity;

		const Vector2 viewvec = GetViewVector();
		m_fRoll += m_fRotSpeed * t;

		Vector2 norm(viewvec.y, -viewvec.x);
		const float delta = 40.0f * t;
	} //if
  else m_vPos += m_vVelocity * t;
  //update bounding shapes
	if (m_nSpriteIndex == FIN_SPRITE) {
		const Vector2 topleft(-m_vRadius.x, m_vRadius.y - 105.0f);
		const Vector2 bottomrt(m_vRadius.x, -m_vRadius.y);
		BoundingBox::CreateFromPoints(m_Aabb, topleft + m_vPos, bottomrt + m_vPos);
	}
	else {
		const Vector2 topleft(-m_vRadius.x, m_vRadius.y);
		const Vector2 bottomrt(m_vRadius.x, -m_vRadius.y);
		BoundingBox::CreateFromPoints(m_Aabb, topleft + m_vPos, bottomrt + m_vPos);
	}

	if (m_nSpriteIndex == PLAYER_SPRITE) {
		mining();
	}

  m_Sphere.Center = (Vector3)m_vPos;

	///This causes the game to ABORT when player object dies
	///It should be fine when the miners get implemented.
	///For now, it is commented out to avoid problems.
	//if (m_nSpriteIndex == PLAYER_SPRITE && m_nHitCount >= 3)
		//kill();

} //move

/// Make the object jump straight up. Only works when the player's
/// vertical speed is zero. Theoretically you can double-jump
/// (and more) if you hit it right at the top of the arc, but
/// iy's tricky.

void CObject::Jump(){
    m_vVelocity.y = 5.0f;
} //CollisionResponse

void CObject::Fall() {
		m_vVelocity.y = -5.0f;
} //CollisionResponse

void CObject::Reset() {
		m_vVelocity.y = 0.0f;
} //CollisionResponse

/// Perform the appropriate response to a collision.
/// \param b Axially aligned bounding box for the object it collided with.

void CObject::CollisionResponse(const BoundingBox& b){
  float w, h;
  m_pRenderer->GetSize(m_nSpriteIndex, w, h);
  w /= 2; h /= 2;
  
  const float top = b.Center.y + b.Extents.y;
  const float bottom = b.Center.y - b.Extents.y;

  const float left = b.Center.x - b.Extents.x;
  const float right = b.Center.x + b.Extents.x;

  if(m_vPos.y > top && m_vPos.y < top + h){
    m_vPos.y = top + h;
    m_vVelocity.y = 0;
  } //if

  else if(m_vPos.y < bottom && m_vPos.y > bottom - h){
    m_vPos.y = bottom - h;
    m_vVelocity.y = 0;
  } //else if

  else if(m_vPos.x < left && m_vPos.x > left - w){
    m_vPos.x = left - w - 0.5f;
    m_vVelocity.x = 0;
  } //else if

  else if(m_vPos.x > right && m_vPos.x < right + w){
    m_vPos.x = right + w + 0.5f;
    m_vVelocity.x = 0;
  } //else if
} //CollisionResponse

/// Set the strafe left flag.

void CObject::StrafeLeft(){
  m_bStrafeLeft = true;
} //StrafeLeft

/// Set the strafe right flag.

void CObject::StrafeRight(){
  m_bStrafeRight = true;
} //StrafeRight

/// Set the strafe back flag.

void CObject::StrafeBack(){
  m_bStrafeBack = true;
} //StrafeBack

/// Perform a death particle effect to mark the death of an object.

void CObject::DeathFX(){
  CParticleDesc2D d;
	d.m_nSpriteIndex = BLOOD_SPRITE;
  d.m_vPos = m_vPos;
      
  d.m_fLifeSpan = 0.5f;
  d.m_fMaxScale = 0.5f;
  d.m_fScaleInFrac = 0.2f;
  d.m_fFadeOutFrac = 0.8f;
  d.m_fScaleOutFrac = d.m_fFadeOutFrac;

  m_pAudio->play(DEATH_SOUND);
  m_pParticleEngine->create(d);
} //DeathFX

/// Kill an object by marking its "is dead" flag. The object
/// will get deleted later at the appropriate time.

void CObject::kill(){
  m_bDead = true;
  //DeathFX();
} //kill

/// Reader function for the "is dead" flag.
/// \return true if marked as being dead, that is, ready for disposal.

bool CObject::IsDead(){
  return m_bDead;
} //IsDead

/// Reader function for speed.
/// \return Speed.

float CObject::GetSpeed(){
  return m_fSpeed;
} //GetSpeed

/// Set the object's speed, assuming that the object
/// moves according to its speed and view vector.
/// \param speed Speed.

void CObject::SetSpeed(float speed){
  m_fSpeed = speed;
} //SetVelocity

/// Set the object's rotational speed in revolutions per second.
/// \param speed Rotational speed in RPS.

void CObject::SetRotSpeed(float speed){
  m_fRotSpeed = speed;
} //Rotate

/// Reader function for the AABB.
/// \return The AABB.

const BoundingBox& CObject::GetBoundingBox(){
  return m_Aabb;
} //GetBoundingBox

/// Reader function for the bounding sphere.
/// \return The bounding sphere.

const BoundingSphere& CObject::GetBoundingSphere(){
  return m_Sphere;
} //GetBoundingSphere

/// Reader function for position.
/// \return Position.

const Vector2& CObject::GetPos(){
  return m_vPos;
} //GetPos

/// Get the view vector.
/// \return The view vector.

Vector2 CObject::GetViewVector(){
  return Vector2(-sin(m_fRoll), 2*cos(m_fRoll));
} //GetViewVector

/// Reader function for the orientation. A 2D object's
/// orientation is its roll amount in 3D space.
/// \return The view vector.

float CObject::GetOrientation(){
  return m_fRoll;
} //GetOrientation

/// Writer function for the orientation. A 2D object's
/// orientation is its roll amount in 3D space.
/// \param angle The new orientation.

void CObject::SetOrientation(float angle){
  m_fRoll = angle;
} //GetOrientation

/// Reader function for velocity.
/// \return Velocity.

const Vector2& CObject::GetVelocity(){
  return m_vVelocity;
} //GetVel

/// Writer function for velocity.
/// \param v Velocity.

void CObject::SetVelocity(const Vector2& v){
  m_vVelocity = v;
} //SetVel

/*START of Miner Code*/
void CObject::SetState(bool f) {
	m_bFollow = f;
} //Enable follow player

/*CURRENTLY USELESS*/
void CObject::SetMine(bool f) {
	m_bMine = f;
} //Enable mine resource
/*END OF USELESS*/

bool CObject::IsFollowing() {
	return m_bFollow;
}

void CObject::mining() {
	const size_t nFrameCount = m_pRenderer->GetNumFrames(m_nSpriteIndex);
	const float dt = 1000 * m_fFrameInterval / (1500 + fabs(m_vVelocity.x));
	
	if (nFrameCount > 1 && m_pStepTimer->GetTotalSeconds() > m_fFrameTimer + dt) {
		m_fFrameTimer = m_pStepTimer->GetTotalSeconds();
		m_nCurrentFrame = (m_nCurrentFrame+1) % nFrameCount;
	} //if
}
/*END of Miner Code*/

/*START CurrentHit functions*/
//INCREMENT HIT
void CObject::IncrHit() {
	m_nHitCount++;
}
//DECREMENT HIT
void CObject::DecrHit() {
	m_nHitCount--;
}
//RETURN HIT
int CObject::Gethit() {
	return m_nHitCount;
}
/*END CurrentHit functions*/

/*Standard Object states*/
bool CObject::IsDisabled() {
	return m_bDisable;
}

void CObject::SetDisableState(bool f) {
	m_bDisable = f;
}

void CObject::SetBridgeState(bool f) {
	m_bActiveBridge = f;
}
/*Standard Object states END*/
void CObject::SetVector(const Vector2& p) {
	m_vPos = p;
}

void CObject::SetVector(float x, float y) {
	m_vPos.x = x;
	m_vPos.y = y;
}

void CObject::SetIsOnMenu1(bool f) {
	m_bOnMenu1 = f;
}

bool CObject::IsOnMenu1() {
	return m_bOnMenu1;
}

void CObject::SetIsOnMenu2(bool f) {
	m_bOnMenu2 = f;
}

bool CObject::IsOnMenu2() {
	return m_bOnMenu2;
}

void CObject::SetIsOnMenu3(bool f) {
	m_bOnMenu1 = f;
}

bool CObject::IsOnMenu3() {
	return m_bOnMenu1;
}

void CObject::IsCounted(bool f) {
	counted = true;
}

void CObject::setFollowVec(Vector2 vec) {
	followVec = vec;
}

void CObject::follow(float ran) {
	float pos = m_vPos.x;

	if (pos < ran && pos < ran - (50.0f)) {
		SetSpeed(100.0f);
		SetState(true);
	}
	if (pos > ran&& pos > ran + (50.0f)) {
		SetSpeed(-100.0f);
		SetState(true);
	}
	else if (pos < ran && pos > ran - (50.0f)) {
		SetSpeed(0.0f);
		SetState(false);
	}
	else if (pos > ran&& pos < ran + (50.0f)) {
		SetSpeed(0.0f);
		SetState(false);
	}
}