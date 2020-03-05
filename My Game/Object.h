/// \file Object.h
/// \brief Interface for the game object class CObject.

#pragma once

#include "GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"

/// \brief The game object. 
///
/// CObject is the abstract representation of an object.

class CObject:
  public CCommon,
  public CComponent,
  public CSpriteDesc2D
{
  friend class CObjectManager;

protected:
	Vector2 m_vVelocity = Vector2::Zero; ///< Velocity.

  private:

	 enum eStateType {
		  STATIC_STATE, FOLLOWING_STATE
	 }; //eStateType

    BoundingSphere m_Sphere; ///< Bounding sphere.
    BoundingBox m_Aabb; ///< Axially aligned bounding box.

	Vector2 followVec = Vector2(0.0f, 0.0f);
	float m_fFrameTimer = 0.0f;
	float m_fFrameInterval = 0.1f; ///< Interval between frames.
    float m_fSpeed = 0.0f; ///< Speed.
    float m_fRotSpeed = 0.0f; ///< Rotational speed.
    //Vector2 m_vVelocity = Vector2::Zero; ///< Velocity.
    bool m_bDead = false; ///< Is dead or not.
    
    bool m_bStrafeLeft = false; ///< Strafe left.
    bool m_bStrafeRight = true; ///< Strafe right.
    bool m_bStrafeBack = false; ///< Strafe back.

	bool m_bFollow = false;
	bool m_bMine = false;

	bool m_bDisable = false;

	bool m_bActiveBridge = false;

	bool m_bOnMenu1 = false;
	bool m_bOnMenu2 = false;

    Vector2 m_vRadius = Vector2::Zero; ///< Half width and height of object sprite.

    float m_fGunTimer = 0.0f; ///< Gun fire timer.

		int m_nHitCount = 0; ///< Number of hits taken. (anything)

		int m_nSpikeDamage = 10; ///< Spike damage output.
		int m_nCurrSpikeDamage = 10; ///< Current spike damage.

		float m_fInitialTrapTimer = 0.0f; ///< Initial trap timer.
		float m_fCurrentTrapTimer = 0.0f; ///< Current trap timer.

		float m_fSpikeTimeLimit = 10.0f; ///< Amount of time before release.

		float SpikeCooldown = 0.0f; ///<Cooldown for receding spikes.

		int m_nMinerScore = 0;

		Vector2 InitialPos;

		bool counted = false;

		bool gameover = false;

  public:
    CObject(eSpriteType t, const Vector2& p); ///< Constructor.

    void move(); ///< Move object.
    void Jump(); ///< Jump.
	void Fall(); ///< Lower model.
	void Reset(); //< Reset velocity

    void kill(); ///< Kill me.
    bool IsDead(); ///< Query whether dead.
    void DeathFX(); ///< Death special effects.
    void CollisionResponse(const BoundingBox& b); ///< Collision response.
    
    void SetSpeed(float speed); ///< Set speed.
    float GetSpeed(); ///< Get speed.
    void SetRotSpeed(float speed); ///< Set rotational velocity.

    Vector2 GetViewVector(); //Get view vector.

    float GetOrientation(); ///< Get orientation.
    void SetOrientation(float angle); ///< Set orientation.
    
    const Vector2& GetVelocity(); ///< Get orientation.
    void SetVelocity(const Vector2& v); ///< Set orientation.
    
    void StrafeLeft(); ///< Strafe left.
    void StrafeRight(); ///< Strafe right.
    void StrafeBack(); ///< Strafe back.
    
    const BoundingBox& GetBoundingBox(); ///< Get AABB.
    const BoundingSphere& GetBoundingSphere(); ///< Get bounding sphere.
    const Vector2& GetPos(); ///< Get position.

	void SetState(bool f);
	void SetMine(bool f);
	void IncrHit();
	void DecrHit();

	int Gethit();
	bool IsFollowing();
	void mining();
	void follow(float);
	void setFollowVec(Vector2);

	bool IsDisabled();
	void SetDisableState(bool f);

	void SetBridgeState(bool f);
	void SetVector(const Vector2& p);
	void SetVector(float x, float y);

	void SetIsOnMenu1(bool f);
	bool IsOnMenu1();

	void SetIsOnMenu2(bool f);
	bool IsOnMenu2();

	void SetIsOnMenu3(bool f);
	bool IsOnMenu3();

	void IsCounted(bool f);
}; //CObject