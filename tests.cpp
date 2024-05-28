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
            CHECK(t2.vard() == "Vardas1");
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


TEST_CASE("Vector Constructor")
        {
        Vector<int> v;
        CHECK(v.getSize() == 0);
        CHECK(v.capacity() == 0);
        CHECK(v.empty() == true);
        }
TEST_CASE("Vector Resize")
        {
        Vector<int> v;
        v.resize(3);
        CHECK(v.getSize() == 3);
        CHECK(v.capacity() == 3);

        v.resize(10, 5);
        CHECK(v.getSize() == 10);
        CHECK(v[3] == 5);
        CHECK(v[8] == 5);
        }
TEST_CASE("Vector Reserve")
        {
        Vector<int> v;
        v.reserve(10);
        CHECK(v.capacity() == 10);

        v.reserve(5);
        CHECK(v.capacity() == 5);
        }
TEST_CASE("Push_back")
        {
        Vector<int> v;
        for(int i=0; i<5; i++){
                v.push_back(i);
        }

        CHECK(v.getSize() == 5);
        CHECK(v[3] == 3);
        }
TEST_CASE("Pop_back")
        {
        Vector<int> v;
        for(int i=0; i<5; i++){
                v.push_back(i);
        }

        CHECK(v.getSize() == 5);

        v.pop_back();

        CHECK(v.getSize() == 4);
        }
TEST_CASE("front/back/at")
        {
        Vector<int> v;
        for(int i=0; i<5; i++){
                v.push_back(i);
        }

        CHECK(v[1] == 1);
        CHECK(v.front() == 0);
        CHECK(v.back() == 4);
        CHECK(v.at(2) == 3);
        }
TEST_CASE("front/back/at")
        {
        Vector<int> v;
        for(int i=0; i<5; i++){
                v.push_back(i);
        }

        CHECK(v[1] == 1);
        CHECK(v.front() == 0);
        CHECK(v.back() == 4);
        CHECK(v.at(2) == 3);
        }