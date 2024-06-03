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
TEST_CASE("Reserve/shrink_to_fit")
        {
        Vector<int> v;
        v.reserve(10);
        CHECK(v.capacity() == 10);

        v.reserve(5);
        CHECK_FALSE(v.capacity() == 5);

        for(int i=0; i<2; i++){
                v.push_back(i);
        }

        v.shrink_to_fit();

        CHECK(v.capacity() == 2);

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
        CHECK(v.at(2) == 2);
        }
TEST_CASE("iterators")
        {
        Vector<int> v{1, 2, 3};
        CHECK(*v.begin() == 1);
        CHECK(*(v.end() - 1) == 3);

        CHECK(*v.rbegin() == 3);
        CHECK(*(v.rend() - 1) == 1);
        }
TEST_CASE("insert")
        {
        Vector<int> v{1, 2, 3, 4, 5};

        v.insert(v.begin()+2, 10);

        CHECK(v.getSize() == 6);
        CHECK(v[2] == 10);

        Vector<int> b{9, 8, 7};

        v.insert(v.begin()+2, b.begin(), b.end());

        CHECK(v.getSize() == 9);
        CHECK(v[2] == 9);
        CHECK(v[5] == 10);

        v.insert(v.end(), {1, 2});
        CHECK(v.getSize() == 11);
        CHECK(v[9] == 1);
        CHECK(v[10] == 2);
        }
TEST_CASE("erase")
        {
        Vector<int> v{1, 2, 3};

        v.erase(v.begin()+1);

        CHECK(v.getSize() == 2);
        CHECK(v[1] == 3);

        v.erase(v.begin(), v.end());

        CHECK(v.getSize() == 0);
        }
TEST_CASE("swap")
        {
        Vector<int> v{1, 2, 3};
        Vector<int> b{9, 8};

        v.swap(b);

        CHECK(v.getSize() == 2);
        CHECK(v[0] == 9);

        CHECK(b.getSize() == 3);
        CHECK(b[2] == 3);
        }
TEST_CASE("clear")
        {
        Vector<int> v{1, 2, 3};
        v.clear();
        CHECK(v.getSize() == 0);
        CHECK(v.empty() == true);
        }
TEST_CASE("emplace")
        {
        Vector<int> v{1, 2, 3};

        v.emplace_back(6);
        CHECK(v.getSize() == 4);
        CHECK(v.back() == 6);

        v.emplace(v.begin()+1, 14);
        CHECK(v[1] == 14);
        }