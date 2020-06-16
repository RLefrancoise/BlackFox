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

    float32 BFRayCast::ReportFixture(
            b2Fixture* fixture,
            const b2Vec2& point,
            const b2Vec2& normal,
            float32 fraction)
    {
        auto data = static_cast<BFFixtureData*>(fixture->GetUserData());

        BFHitInfo hitInfo;
        hitInfo.hitEntity = data->entity;
        hitInfo.hitPoint = BFVector2f(point.x, point.y);
        hitInfo.normal = BFVector2f(normal.x, normal.y);
        hitInfo.fraction = fraction;

        /*BF_PRINT("Hit entity: {} at {}, ray length: {}",
                hitInfo.hitEntity,
                static_cast<std::string>(hitInfo.hitPoint),
                hitInfo.fraction);*/

        return HandleHit(hitInfo, fraction);
    }

    //---------------------------------------------------------------------------------

    BFRayCastClosest::BFRayCastClosest(
            const BFVector2f& startPoint,
            const BFVector2f& endPoint)
    : BFRayCast(startPoint, endPoint)
    , hit(false)
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

    float32 BFRayCastAll::HandleHit(const BFHitInfo& hitInfo, float32 fraction)
    {
        hits.emplace_back(hitInfo);
        return 1;
    }
}