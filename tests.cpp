#include "funkcijos.h"

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"


TEST_CASE("Input Operation")
        {
            duom t1;
            istringstream is("Vardas1                  Pavarde1                  5       9       4       5       10      8       7       10      10");
            is>>t1;
            CHECK(t1.vard() == "Vardas1");
            CHECK(t1.galvid() == 8.9);
        }
TEST_CASE("Copy Constructor")
        {
            duom t1;
            istringstream is("Vardas1                  Pavarde1                  5       9       4       5       10      8       7       10      10");
            is>>t1;
            duom t2(t1);
            CHECK(t2.pav() == "Pavarde1");
            CHECK(t2.galvid() == t1.galvid());
        }
TEST_CASE("Move Constructor")
        {
            duom t1;
            istringstream is("Vardas1                  Pavarde1                  5       9       4       5       10      8       7       10      10");
            is>>t1;
            duom t2(move(t1));
            CHECK(t2.vard() == "Vardas2");
            CHECK_FALSE(t2.galvid() == t1.galvid());
            CHECK(t1.galvid() == 0);
        }
TEST_CASE("Copy Assignment")
        {
            duom t1;
            istringstream iss("Lebronas Dzeimsas 10 10 10 10 10 10 7 10 9");
            iss>>t1;
            duom t2=t1;
            CHECK(t2.vard() == "Lebronas");
            CHECK(t2.galvid() == t1.galvid());
        }
TEST_CASE("Move Assignment")
        {
            duom t1;
            istringstream iss("Lebronas Dzeimsas 10 10 10 10 10 10 7 10 9");
            iss>>t1;
            duom t2=move(t1);
            CHECK(t2.pav() == "Dzeimsas");
            CHECK_FALSE(t2.galvid() == t1.galvid());
            CHECK(t1.galvid() == 0);
        }
