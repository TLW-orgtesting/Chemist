#include "chemist/operators/derivative.hpp"
#include "test_operator.hpp"

using namespace chemist::operators;

using type_list = std::tuple<ElectronIdentity_Nuclear>;

TEMPLATE_LIST_TEST_CASE("Derivative", "", type_list) {
    using kinetic_type   = TestType;
    using particle_types = typename kinetic_type::particle_type;
    using particle0_type = std::tuple_element_t<0, particle_types>;
    using particle1_type = std::tuple_element_t<1, particle_types>;

    kinetic_type defaulted;

    auto p0 = particle0_type{};
    auto p1 = testing::non_default_parameter<particle1_type>();
    kinetic_type non_default(p0, p1);

    SECTION("Ctors") {
        SECTION("Default") {
            REQUIRE(defaulted.template at<0>() == particle0_type{});
            REQUIRE(defaulted.template at<1>() == particle1_type{});
        }
        SECTION("Value") { REQUIRE(non_default.template at<1>() == p1); }
        SECTION("Copy") {
            kinetic_type other(non_default);
            REQUIRE(other.template at<0>() == p0);
            REQUIRE(other.template at<1>() == p1);
        }
        SECTION("Move") {
            kinetic_type other(std::move(non_default));
            REQUIRE(other.template at<0>() == p0);
            REQUIRE(other.template at<1>() == p1);
        }
        SECTION("Copy assignment") {
            kinetic_type copy;
            auto pcopy = &(copy = non_default);
            REQUIRE(pcopy == &copy);
            REQUIRE(copy.template at<0>() == p0);
            REQUIRE(copy.template at<1>() == p1);
        }
        SECTION("Move assignment") {
            kinetic_type copy;
            auto pcopy = &(copy = std::move(non_default));
            REQUIRE(pcopy == &copy);
            REQUIRE(copy.template at<0>() == p0);
            REQUIRE(copy.template at<1>() == p1);
        }
    }

    SECTION("Hash") {
        using chemist::detail_::hash_objects;
        SECTION("LHS == default") {
            auto lhs = hash_objects(defaulted);

            SECTION("LHS == RHS") {
                kinetic_type rhs;
                REQUIRE(lhs == hash_objects(rhs));
            }

            SECTION("LHS != RHS") { REQUIRE(lhs != hash_objects(non_default)); }
        }
    }

    SECTION("comparisons") {
        SECTION("LHS == default") {
            SECTION("LHS == RHS") {
                kinetic_type rhs;
                REQUIRE(defaulted == rhs);
                REQUIRE_FALSE(defaulted != rhs);
            }

            SECTION("LHS != RHS") {
                REQUIRE(defaulted != non_default);
                REQUIRE_FALSE(defaulted == non_default);
            }
        }
    }

    SECTION("as_string") { REQUIRE(defaulted.as_string() == "O??"); }
}
