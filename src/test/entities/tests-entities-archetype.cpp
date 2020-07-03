#include <catch2/catch.hpp>

#include "BFEntityArchetype.h"
#include "BFComponent.h"

using namespace BlackFox;

#define CREATE_COMPONENT(componentName)     struct componentName { \
                                                BF_COMPONENT(componentName, "componentName") \
                                                componentName() = default; \
                                                componentName(const componentName&) = default; \
                                                componentName(componentName&&) noexcept = default; \
                                            };

CREATE_COMPONENT(TestComponent1)
CREATE_COMPONENT(TestComponent2)
CREATE_COMPONENT(TestComponent3)

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Template entity archetype
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE("Entity Archetype Template with one component", "[archetype][template][one]", TestComponent1) {
    BFEntityArchetype<TestType> archetype;

    SECTION("Creates entity with the given components") {
        EntityManager em = std::make_shared<entt::registry>();
        const auto entity = archetype.instance(em);

        REQUIRE(em->has<TestType>(entity));
    }
}

namespace
{
    using Types = std::tuple<TestComponent1, TestComponent2>;
    TEMPLATE_LIST_TEST_CASE("Entity Archetype Template with several components", "[archetype][template][several]", Types) {
        BFEntityArchetype<TestType> archetype;

        SECTION("Creates entity with the given components") {
            EntityManager em = std::make_shared<entt::registry>();
            const auto entity = archetype.instance(em);

            REQUIRE(em->has<TestType>(entity));
        }
    }
}



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Runtime entity archetype
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

class TestRuntimeEntityArchetype : public BFRuntimeEntityArchetype
{
private:
    EntityManager m_entityManager;

protected:
    void setComponent(entt::entity e, ComponentId c) const override {
        switch(c) {
            case TestComponent1::id:
                m_entityManager->emplace<TestComponent1>(e);
                break;
            case TestComponent2::id:
                m_entityManager->emplace<TestComponent2>(e);
                break;
            case TestComponent3::id:
                m_entityManager->emplace<TestComponent3>(e);
                break;
            default:
                REQUIRE(false);
                break;
        }
    }

public:
    explicit TestRuntimeEntityArchetype(EntityManager em, const std::vector<ComponentId>& components)
    : BFRuntimeEntityArchetype(components)
    , m_entityManager(std::move(em))
    {
    }
};

TEST_CASE("Runtime Entity Archetype", "[archetype][runtime]") {

    SECTION("Creates entity with no components") {
        EntityManager em = std::make_shared<entt::registry>();
        TestRuntimeEntityArchetype archetype(em, {});

        const auto entity = archetype.instance(em);

        REQUIRE(em->orphan(entity));
    }

    SECTION("Creates entity with one component") {
        EntityManager em = std::make_shared<entt::registry>();
        TestRuntimeEntityArchetype archetype(em, {TestComponent1::id});

        const auto entity = archetype.instance(em);

        REQUIRE(em->has<TestComponent1>(entity));
        REQUIRE_FALSE(em->has<TestComponent2>(entity));
        REQUIRE_FALSE(em->has<TestComponent3>(entity));
    }

    SECTION("Creates entity with several components") {
        EntityManager em = std::make_shared<entt::registry>();
        TestRuntimeEntityArchetype archetype(em, {TestComponent1::id, TestComponent2::id, TestComponent3::id});

        const auto entity = archetype.instance(em);

        REQUIRE(em->has<TestComponent1, TestComponent2, TestComponent3>(entity));
    }
}