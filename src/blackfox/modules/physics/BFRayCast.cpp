#include "BFRayCast.h"
#include "BFDebug.h"

namespace BlackFox
{
    BFRayCast::BFRayCast(
            const BFVector2f& startPoint,
            const BFVector2f& endPoint)
    : startPoint(startPoint)
    , endPoint(endPoint)
    {}

    BFRayCast::BFRayCast(const BlackFox::BFRay &ray)
    : BFRayCast(ray.origin, ray.endPoint())
    {}

    float32 BFRayCast::ReportFixture(
            b2Fixture* fixture,
            const b2Vec2& point,
            const b2Vec2& normal,
            float32 fraction)
    {
        auto data = static_cast<BFFixtureData*>(fixture->GetUserData());

        BFHitInfo hitInfo;
        hitInfo.hitEntity = data->entity;
        hitInfo.hitCollider = data->collider;
        hitInfo.hitPoint = BFVector2f(point.x, point.y);
        hitInfo.normal = BFVector2f(normal.x, normal.y);
        hitInfo.fraction = fraction;

        return HandleHit(hitInfo, fraction);
    }

    //---------------------------------------------------------------------------------

    BFRayCastClosest::BFRayCastClosest(
            const BFVector2f& startPoint,
            const BFVector2f& endPoint)
    : BFRayCast(startPoint, endPoint)
    , hit(false)
    {}

    BFRayCastClosest::BFRayCastClosest(
            const BFRay& ray)
    : BFRayCast(ray.origin, ray.endPoint())
    {}

    float32 BFRayCastClosest::HandleHit(const BFHitInfo& hitInfo, float32 fraction)
    {
        this->hitInfo = hitInfo;
        hit = true;
        return fraction;
    }

    //---------------------------------------------------------------------------------

    BFRayCastAll::BFRayCastAll(
            const BFVector2f& startPoint,
            const BFVector2f& endPoint)
    : BFRayCast(startPoint, endPoint)
    {}

    BFRayCastAll::BFRayCastAll(
        const BFRay& ray)
    : BFRayCast(ray.origin, ray.endPoint())
    {}

    float32 BFRayCastAll::HandleHit(const BFHitInfo& hitInfo, float32 fraction)
    {
        hits.emplace_back(hitInfo);
        return 1;
    }
}