#include "pch.h"
#include <Physics/Physics.h>
#include <Core/Timer.h>

using namespace clt;

Physics::Physics() : mGravity({0.0f, -300.0f})
{
}

Physics::~Physics()
{
}

void Physics::AddCollider(Collider2DComponent* pCollider)
{
	mColliders.push_back(pCollider);
	if (mColliderEvent.find(pCollider) == mColliderEvent.end()) 
	{
		mColliderEvent[pCollider] = new CollisionEvent();
	}
}

void Physics::AddRigidbody(RigidBody2D* pRigidbody)
{
	mRigidbody.push_back(pRigidbody);
}

void Physics::RemoveRigidBody(RigidBody2D* pRigidbody)
{

}

void Physics::RemoveCollider(Collider2DComponent* pCollider)
{
	mColliders.erase(std::remove(mColliders.begin(), mColliders.end(), pCollider), mColliders.end());
	if (mColliderEvent.find(pCollider) != mColliderEvent.end()) {
		delete mColliderEvent[pCollider];
		mColliderEvent.erase(pCollider);
	}
}



void Physics::SubscribeTo(Collider2DComponent* pCollider, ICollisionListener* pListener)
{
	size_t hasCollider = mColliderEvent.count(pCollider);

	if (!hasCollider)
	{
		mColliderEvent[pCollider] = new CollisionEvent();
	}
	mColliderEvent[pCollider]->Subscribe(pListener);
}

void Physics::Update()
{
	for (auto& rb : mRigidbody)
	{
		rb->mIsGrounded = false;

		if (!rb->mIsKinematic && rb->IsActive()) 
		{
			rb->AddVelocity(mGravity * rb->GetGravityScale() * Timer::deltaTime);
			rb->UpdateRotation(Timer::deltaTime);
		}

		rb->GetOwner()->AddActorLocationOffset(rb->GetVelocity() * Timer::deltaTime);
	}

	CheckCollisions();
	ResolveCollisions();
	DispatchEvents();
}

void Physics::CheckCollisions()
{
	mCurrentFrameCollisions.clear();

	for (size_t i = 0; i < mColliders.size(); i++)
	{
		for (size_t j = i + 1; j < mColliders.size(); j++)
		{
			Collider2DComponent* a = mColliders[i];
			Collider2DComponent* b = mColliders[j];
			hitResult result;

			if (a->CheckCollision(b, result))
			{
				mCurrentFrameCollisions.push_back(result);
			}
		}
	}
}

void Physics::ResolveCollisions()
{
	for (auto& result : mCurrentFrameCollisions)
	{
		RigidBody2D* rbA = result.ActorA->GetComponentOfType<RigidBody2D>();
		RigidBody2D* rbB = result.ActorB->GetComponentOfType<RigidBody2D>();

		if (!result.ColliderA->IsTrigger() && !result.ColliderB->IsTrigger())
		{
			const Vector2 correction = result.Normal * result.Penetration;
			const float safetyFactor = 1.1f;
			const Vector2 safeCorrection = correction * safetyFactor;

			if (rbA && !rbA->mIsKinematic && rbA->IsActive() && !rbB)
			{
				result.ActorA->AddActorLocationOffset(safeCorrection);

				float combinedFriction = result.ColliderA->mFriction * result.ColliderB->mFriction;

				Vector2 normal =  result.Normal.Normalized();
				Vector2 tangent = Vector2(normal.y, -normal.x).Normalized();

				Vector2 velocity = rbA->GetVelocity();
				float velocityNormal = Vector2::Dot(velocity, normal);
				float velocityTangent = Vector2::Dot(velocity, tangent);

				velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
				velocity = normal * velocityNormal + tangent * velocityTangent;
				rbA->SetVelocity(velocity);

				Vector2 contactPoint = result.Point;
				Vector2 centerA = result.ActorA->GetActorLocation();
				Vector2 contactOffset = contactPoint - centerA;

				Vector2 force = result.Normal * (1 + velocityNormal) * rbA->mMass * 100;
				rbA->mTorque += contactOffset.Cross(force);

				if (result.Normal.y > 0.5f) 
				{
					rbA->SetVelocity(Vector2(rbA->GetVelocity().x, 0.0f));
					rbA->mIsGrounded = true;
					rbA->mAngularVelocity *= 0.2f; 
				}
			}
			else if (!rbA && rbB && !rbB->mIsKinematic && rbB->IsActive())
			{
				result.ActorB->AddActorLocationOffset(safeCorrection);

				float combinedFriction = result.ColliderB->mFriction * result.ColliderA->mFriction;

				Vector2 normal = result.Normal.Normalized();
				Vector2 tangent = Vector2(normal.y, -normal.x).Normalized();

				Vector2 velocity = rbB->GetVelocity();
				float velocityNormal = Vector2::Dot(velocity, normal);
				float velocityTangent = Vector2::Dot(velocity, tangent);

				velocityTangent *= (1.0f - combinedFriction * Timer::deltaTime);
				velocity = normal * velocityNormal + tangent * velocityTangent;
				rbB->SetVelocity(velocity);

				Vector2 contactPoint = result.Point;
				Vector2 centerB = rbB->GetWorldPosition();
				Vector2 contactOffset = contactPoint - centerB;

				Vector2 force = result.Normal * (- 1.5f * (velocityNormal) / (1 / rbB->mMass) * 100);
				rbB->mTorque += contactOffset.Cross(-force);

				if (result.Normal.y > 0.5f) 
				{
					rbB->SetVelocity(Vector2(rbB->GetVelocity().x, 0.0f));
					rbB->mIsGrounded = true;
					rbB->mAngularVelocity *= 0.2f;
				}
			}

			else if (rbA && rbB && !rbA->mIsKinematic && !rbB->mIsKinematic)
			{
				Vector2 relativeVelocity = rbB->GetVelocity() - rbA->GetVelocity();
				float velAlongNormal = Vector2::Dot(relativeVelocity, result.Normal);

				if (velAlongNormal < 0)
				{
					const float restitution = 0.5f;
					const float invMassA = 1.0f / rbA->mMass;
					const float invMassB = 1.0f / rbB->mMass;
					const float totalInverseMass = invMassA + invMassB;

					const float impulseMagnitude = -(1 + restitution) * velAlongNormal / totalInverseMass;
					const Vector2 impulse = impulseMagnitude * result.Normal;

					rbA->SetVelocity(rbA->GetVelocity() - impulse * invMassA);
					rbB->SetVelocity(rbB->GetVelocity() + impulse * invMassB);

					const float friction = std::sqrt(result.ColliderA->mFriction * result.ColliderB->mFriction * 0.01f);
					const Vector2 tangent = (relativeVelocity - result.Normal * velAlongNormal).Normalized();
					const float velAlongTangent = Vector2::Dot(relativeVelocity, tangent);
					const float tangentImpulseMagnitude = -velAlongTangent / totalInverseMass * friction;
					const Vector2 tangentImpulse = tangent * tangentImpulseMagnitude;

					rbA->SetVelocity(rbA->GetVelocity() - tangentImpulse * invMassA);
					rbB->SetVelocity(rbB->GetVelocity() + tangentImpulse * invMassB);

					if (totalInverseMass > 0)
					{
						const Vector2 correctionA = -correction * (invMassA / totalInverseMass);
						const Vector2 correctionB =  correction * (invMassB / totalInverseMass);

						result.ActorA->AddActorLocationOffset(correctionA);
						result.ActorB->AddActorLocationOffset(correctionB);
						if (rbA->mCanStepOn) rbB->mIsGrounded = true;
						if (rbB->mCanStepOn) rbA->mIsGrounded = true;
					}

					Vector2 contactPoint = result.Point;
					Vector2 centerA = result.ActorA->GetActorLocation();
					Vector2 centerB = result.ActorB->GetActorLocation();

					Vector2 rA = contactPoint - centerA;
					Vector2 rB = contactPoint - centerB;

					Vector2 force = result.Normal * impulseMagnitude; 
					float torqueA = rA.Cross(-force); 
					float torqueB = rB.Cross(force);

					if (rbA) rbA->mTorque += torqueA;
					if (rbB) rbB->mTorque += torqueB;
				}
			}
		}
	}
}

void Physics::DispatchEvents()
{
	std::set<std::pair<Collider2DComponent*, Collider2DComponent*>> currentCollisions;

	for (hitResult& result : mCurrentFrameCollisions)
	{
		auto colliderPair = (result.ColliderA < result.ColliderB)
			? std::make_pair(result.ColliderA, result.ColliderB)
			: std::make_pair(result.ColliderB, result.ColliderA);

		currentCollisions.insert(colliderPair);
	}

		// ENTER
	for (auto& colliderPair : currentCollisions)
	{
		if (!mPreviousCollisions.count(colliderPair))
		{
			for (hitResult& result : mCurrentFrameCollisions)
			{
				if ((result.ColliderA == colliderPair.first && result.ColliderB == colliderPair.second) ||
					(result.ColliderA == colliderPair.second && result.ColliderB == colliderPair.first))
				{
					if (mColliderEvent.count(result.ColliderA))
					{
						mColliderEvent[result.ColliderA]->NotifyEnter(result);
					}
					if (mColliderEvent.count(result.ColliderB))
					{
						mColliderEvent[result.ColliderB]->NotifyEnter(result);
					}
					break;
				}
			}
		}
	}

		// STAY
	for (auto& colliderPair : mPreviousCollisions)
	{
		if (currentCollisions.count(colliderPair))
		{
			for (hitResult& result : mCurrentFrameCollisions)
			{
				if ((result.ColliderA == colliderPair.first && result.ColliderB == colliderPair.second) ||
					(result.ColliderB == colliderPair.second && result.ColliderB == colliderPair.first))
				{
					if (mColliderEvent.count(result.ColliderA))
					{
						mColliderEvent[result.ColliderA]->NotifyStay(result);
					}
					if (mColliderEvent.count(result.ColliderB))
					{
						mColliderEvent[result.ColliderB]->NotifyStay(result);
					}
				}
			}
		}
	}

		//EXIT
	for (auto& colliderPair : mPreviousCollisions)
	{
		if (!currentCollisions.count(colliderPair))
		{
			for (hitResult& prevResult : mPreviousFrameCollisions)
			{
				if ((prevResult.ColliderA == colliderPair.first && prevResult.ColliderB == colliderPair.second) ||
					(prevResult.ColliderA == colliderPair.second && prevResult.ColliderB == colliderPair.first))
				{
					if (mColliderEvent.count(colliderPair.first))
					{
						mColliderEvent[colliderPair.first]->NotifyExit(prevResult);
					}
					if (mColliderEvent.count(colliderPair.second))
					{
						mColliderEvent[colliderPair.second]->NotifyExit(prevResult);
					}
				}
			}
		}
	}
}
