//
//  main.cpp
//  Project_One
//
//  Created by Kyle Nguyen on 9/30/19.
//  Copyright © 2019 CS-30. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>
#include <type_traits>
#include "BballRoster.h"

using namespace std;

bool lookupPlayer3type(bool (BballRoster::*)(const std::string&, const std::string&, SomeType&) const) { return true; }
bool lookupPlayer3type(bool (BballRoster::*)(const std::string&, const std::string&, SomeType&)) { return false; }
bool lookupPlayer3type(...) { return false; }
bool choosePlayer4type(bool (BballRoster::*)(int, std::string&, std::string&, SomeType&) const) { return true; }
bool choosePlayer4type(bool (BballRoster::*)(int, std::string&, std::string&, SomeType&)) { return false; }
bool choosePlayer4type(...) { return false; }

std::string SOMEFNAME = std::string("123");
std::string DEFAULTFNAME = std::string();
std::string ARRAYFNAME[6] = {
    std::string("10"), std::string("20"), std::string("30"),
    std::string("40"), std::string("50"), std::string("60")
};

std::string SOMELNAME = std::string("321");
std::string DEFAULTLNAME = std::string();
std::string ARRAYLNAME[6] = {
    std::string("11"), std::string("21"), std::string("31"),
    std::string("41"), std::string("51"), std::string("61")
};

SomeType SOMEVALUE = "junk";
SomeType DEFAULTV = SomeType();
SomeType ARRAYV[6] = {
    "able", "baker", "charlie", "delta", "echo", "foxtrot"
};

bool has(const BballRoster& m, const std::string& firstName, const std::string& lastName, const SomeType& v)
{
    SomeType v2 = DEFAULTV;
    m.lookupPlayer(firstName, lastName, v2);
    SomeType v3 = SOMEVALUE;
    m.lookupPlayer(firstName, lastName, v3);
    return v2 == v && v3 == v;
}

void testone(int n)
{
    BballRoster m;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert((is_same<decltype(&BballRoster::rosterEmpty), bool (BballRoster::*)() const>::value));
        } break; case  2: {
            assert((is_same<decltype(&BballRoster::howManyPlayers), int (BballRoster::*)() const>::value));
        } break; case  3: {
            assert((is_same<decltype(&BballRoster::playerOnRoster), bool (BballRoster::*)(const std::string, const std::string) const>::value) ||
                   (is_same<decltype(&BballRoster::playerOnRoster), bool (BballRoster::*)(const std::string&, const std::string&) const>::value));
        } break; case  4: {
            assert(lookupPlayer3type(&BballRoster::lookupPlayer));
        } break; case  5: {
            assert(choosePlayer4type(&BballRoster::choosePlayer));
        } break; case  6: {
            assert(m.rosterEmpty());
        } break; case  7: {
            assert(m.howManyPlayers() == 0);
        } break; case  8: {
            assert(!m.resignPlayer(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE) && m.howManyPlayers() == 0);
        } break; case  9: {
            assert(!m.renouncePlayer(DEFAULTFNAME, DEFAULTLNAME) && m.howManyPlayers() == 0);
        } break; case 10: {
            assert(!m.playerOnRoster(DEFAULTFNAME, DEFAULTLNAME));
        } break; case 11: {
            SomeType v = SOMEVALUE;
            assert(!m.lookupPlayer(DEFAULTFNAME, DEFAULTLNAME, v) && v == SOMEVALUE);
        } break; case 12: {
            SomeType v = SOMEVALUE;
            assert(!m.choosePlayer(0, DEFAULTFNAME, DEFAULTLNAME, v) && v == SOMEVALUE);
        } break; case 13: {
            assert(m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE));
        } break; case 14: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            assert(!m.rosterEmpty());
        } break; case 15: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            assert(m.howManyPlayers() == 1);
        } break; case 16: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            assert(m.playerOnRoster(SOMEFNAME, SOMELNAME));
        } break; case 17: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            SomeType v = DEFAULTV;
            assert(m.lookupPlayer(SOMEFNAME, SOMELNAME, v));
        } break; case 18: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            SomeType v = DEFAULTV;
            m.lookupPlayer(SOMEFNAME, SOMELNAME, v);
            assert(v == SOMEVALUE);
        } break; case 19: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], SOMEVALUE);
            SomeType v = DEFAULTV;
            assert(!m.lookupPlayer(ARRAYFNAME[1], ARRAYLNAME[1], v));
        } break; case 20: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            SomeType v = SOMEVALUE;
            m.lookupPlayer(ARRAYFNAME[1], ARRAYLNAME[1], v);
            assert(v == SOMEVALUE);
        } break; case 21: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            std::string f = DEFAULTFNAME;
            std::string l = DEFAULTLNAME;
            SomeType v = DEFAULTV;
            assert(m.choosePlayer(0, f, l, v));
        } break; case 22: {
            m.signPlayer(SOMEFNAME, SOMELNAME, SOMEVALUE);
            std::string f = DEFAULTFNAME;
            std::string l = DEFAULTLNAME;
            SomeType v = DEFAULTV;
            m.choosePlayer(0, f, l, v);
            assert(f == SOMEFNAME && l == SOMELNAME && v == SOMEVALUE);
        } break; case 23: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(!m.rosterEmpty() && m.howManyPlayers() == 2);
        } break; case 24: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) && m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]));
        } break; case 25: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
        } break; case 26: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], SOMEVALUE);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE);
            assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0], SOMEVALUE) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE));
        } break; case 27: {
            assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]));
            assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
        } break; case 28: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]);
            assert(m.howManyPlayers() == 2);
        } break; case 29: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]);
            assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
        } break; case 30: {
            assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]));
            assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
            assert(!m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]));
        } break; case 31: {
            assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]));
            assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
            assert(!m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]));
        } break; case 32: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m.resignPlayer(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE);
            assert(m.howManyPlayers() == 3 && m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) && m.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 33: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m.resignPlayer(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE);
            assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE) &&
                   has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]));
        } break; case 34: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            assert(m.resignPlayer(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE));
        } break; case 35: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.resignPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[0]);
            assert(m.howManyPlayers() == 2 && has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
                   has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]) && !m.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 36: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(!m.resignPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]) && !m.resignPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[0]));
        } break; case 37: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(!m.rosterEmpty() && m.howManyPlayers() == 2);
        } break; case 38: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
        } break; case 39: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], SOMEVALUE);
            m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE);
            assert(has(m, ARRAYFNAME[0], ARRAYLNAME[0], SOMEVALUE) && has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE));
        } break; case 40: {
            assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]));
            assert(m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
        } break; case 41: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signOrResign(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]);
            assert(m.howManyPlayers() == 2 && has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]) &&
                   has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
        } break; case 42: {
            assert(m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]));
            assert(m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]));
            assert(m.signOrResign(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[2]));
        } break; case 43: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE);
            assert(m.howManyPlayers() == 3 && has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
                   has(m, ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE) && has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]));
        } break; case 44: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            assert(m.signOrResign(ARRAYFNAME[1], ARRAYLNAME[1], SOMEVALUE));
        } break; case 45: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signOrResign(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[0]);
            assert(m.howManyPlayers() == 3 && has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
                   has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]) && has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[0]));
        } break; case 46: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(m.signOrResign(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]));
        } break; case 47: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]));
        } break; case 48: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
            assert(!m.rosterEmpty() && m.howManyPlayers() == 1 && has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
                   !m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]));
        } break; case 49: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.renouncePlayer(ARRAYFNAME[0], ARRAYLNAME[0]);
            assert(!m.rosterEmpty() && m.howManyPlayers() == 1 && has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]) &&
                   !m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]));
        } break; case 50: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.renouncePlayer(ARRAYFNAME[0], ARRAYLNAME[0]);
            m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
            assert(m.howManyPlayers() == 0);
        } break; case 51: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
            m.renouncePlayer(ARRAYFNAME[2], ARRAYLNAME[2]);
            m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            assert(m.howManyPlayers() == 2 && has(m, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) &&
                   has(m, ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]) && !m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   !m.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 52: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            assert(!m.renouncePlayer(ARRAYFNAME[2], ARRAYLNAME[2]) && m.howManyPlayers() == 2);
        } break; case 53: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            std::string f;
            std::string l;
            SomeType v;
            assert(!m.choosePlayer(-1, f, l, v));
        } break; case 54: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            std::string f = SOMEFNAME;
            std::string l = SOMELNAME;
            SomeType v = SOMEVALUE;
            m.choosePlayer(-1, f, l, v);
            assert(f == SOMEFNAME && l == SOMELNAME && v == SOMEVALUE);
        } break; case 55: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            std::string f, l;
            SomeType v;
            assert(!m.choosePlayer(2, f, l, v));
        } break; case 56: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            std::string f = SOMEFNAME;
            std::string l = SOMELNAME;
            SomeType v = SOMEVALUE;
            m.choosePlayer(2, f, l, v);
            assert(f == SOMEFNAME && l == SOMELNAME && v == SOMEVALUE);
        } break; case 57: {
            m.signPlayer(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE);
            assert(m.howManyPlayers() == 1 && has(m, DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE));
        } break; case 58: {
            m.resignPlayer(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE);
            assert(m.howManyPlayers() == 0 && !m.playerOnRoster(DEFAULTFNAME, DEFAULTLNAME));
        } break; case 59: {
            m.signOrResign(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE);
            assert(m.howManyPlayers() == 1 && has(m, DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE));
        } break; case 60: {
            m.signPlayer(DEFAULTFNAME, DEFAULTLNAME, SOMEVALUE);
            m.renouncePlayer(DEFAULTFNAME, DEFAULTLNAME);
            assert(m.howManyPlayers() == 0 && !m.playerOnRoster(DEFAULTFNAME, DEFAULTLNAME));
        } break; case 61: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m.swapRoster(m2);
                assert(m.howManyPlayers() == 3);
            }
        } break; case 62: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m.swapRoster(m2);
                assert(has(m, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]) && has(m, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]) &&
                       has(m, ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]) && !m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]));
            }
        } break; case 63: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m.swapRoster(m2);
                assert(m2.howManyPlayers() == 2);
            }
        } break; case 64: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m.swapRoster(m2);
                assert(has(m2, ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]) && has(m2, ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]) &&
                       !m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) && !m2.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]));
            }
        } break; case 65: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m.swapRoster(m2);
                assert(m.howManyPlayers() == 3 && m2.howManyPlayers() == 5);
            }
        } break; case 66: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                assert(m2.howManyPlayers() == 2 && m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) && !m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[3]));
            }
        } break; case 67: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.renouncePlayer(ARRAYFNAME[2], ARRAYLNAME[2]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m2.renouncePlayer(ARRAYFNAME[0], ARRAYLNAME[0]);
                m2.renouncePlayer(ARRAYFNAME[3], ARRAYLNAME[3]);
                m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 68: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                BballRoster m3(m2);
                m3.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m3.renouncePlayer(ARRAYFNAME[1], ARRAYLNAME[1]);
                m3.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m3.renouncePlayer(ARRAYFNAME[2], ARRAYLNAME[2]);
                m3.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m3.renouncePlayer(ARRAYFNAME[0], ARRAYLNAME[0]);
                m3.renouncePlayer(ARRAYFNAME[3], ARRAYLNAME[3]);
                m3.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 69: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                BballRoster m3(m2);
                assert(m3.howManyPlayers() == 3);
            }
        } break; case 70: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            {
                BballRoster m2(m);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                assert(m2.howManyPlayers() == m.howManyPlayers() + 1);
            }
        } break; case 71: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            {
                BballRoster m2(m);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                assert(m2.howManyPlayers() == 4 && m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) && m2.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]));
            }
        } break; case 72: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            {
                BballRoster m2(m);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                assert(m2.howManyPlayers() == 4 && m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) && !m2.playerOnRoster(ARRAYFNAME[4], ARRAYLNAME[4]));
            }
        } break; case 73: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                BballRoster m3;
                m3.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
                m3.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5], ARRAYV[5]);
                m3 = m2;
                assert(m3.howManyPlayers() == 3 && m2.howManyPlayers() == 3);
            }
        } break; case 74: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
                m2 = m;
                m2.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5], ARRAYV[5]);
                assert(m2.howManyPlayers() == m.howManyPlayers() + 1);
            }
        } break; case 75: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
                m2.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5], ARRAYV[5]);
                m2 = m;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                       m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                       m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                       !m2.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]));
            }
        } break; case 76: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
                m2.signPlayer(ARRAYFNAME[5], ARRAYLNAME[5], ARRAYV[5]);
                m2 = m;
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                assert(m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                       m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                       !m.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
            }
        } break; case 77: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2 = m2;
                assert(m2.howManyPlayers() == 3);
                assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                       m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                       m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
            }
            assert(true);  // no corruption so bad that destruction failed
        } break; case 78: {
            {
                BballRoster m2;
                m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
                m2.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
                m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
                m2 = m2;
                m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
                assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                       m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                       m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                       m2.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]));
            }
        } break; case 79: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            BballRoster m3;
            joinRosters(m, m2, m3);
            assert(m3.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m3.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m3.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 80: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            BballRoster m3;
            joinRosters(m2, m, m3);
            assert(m3.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m3.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m3.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 81: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            BballRoster m3;
            joinRosters(m, m2, m3);
            assert(m3.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m3.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m3.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                   m3.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]) &&
                   m3.playerOnRoster(ARRAYFNAME[4], ARRAYLNAME[4]));
        } break; case 82: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            BballRoster m3;
            assert(joinRosters(m, m2, m3));
        } break; case 83: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            BballRoster m3;
            m3.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[5]);
            joinRosters(m, m2, m3);
            assert(m3.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m3.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m3.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                   m3.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]) &&
                   m3.playerOnRoster(ARRAYFNAME[4], ARRAYLNAME[4]) &&
                   has(m3, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]) &&
                   !has(m3, ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[5]));
        } break; case 84: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            BballRoster m3;
            m3.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[5]);
            assert(joinRosters(m, m2, m3));
        } break; case 85: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m3;
            joinRosters(m, m2, m3);
            assert(m3.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m3.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m3.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                   m3.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]));
        } break; case 86: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m3;
            assert(joinRosters(m, m2, m3));
        } break; case 87: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[4]);
            BballRoster m3;
            joinRosters(m, m2, m3);
            assert(m3.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m3.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m3.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 88: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[4]);
            BballRoster m3;
            assert(!joinRosters(m, m2, m3));
        } break; case 89: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            joinRosters(m, m2, m);
            assert(m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                   m.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]) &&
                   m.playerOnRoster(ARRAYFNAME[4], ARRAYLNAME[4]));
        } break; case 90: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[3], ARRAYLNAME[3], ARRAYV[3]);
            m2.signPlayer(ARRAYFNAME[4], ARRAYLNAME[4], ARRAYV[4]);
            joinRosters(m, m2, m2);
            assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]) &&
                   m2.playerOnRoster(ARRAYFNAME[3], ARRAYLNAME[3]) &&
                   m2.playerOnRoster(ARRAYFNAME[4], ARRAYLNAME[4]));
        } break; case 91: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            m2.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            checkRoster(ARRAYFNAME[1], ARRAYLNAME[1], m, m2);
            assert(!m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) && m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]));
        } break; case 92: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            checkRoster(ARRAYFNAME[1], ARRAYLNAME[1], m, m2);
            assert(!m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) && m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]));
        } break; case 93: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            checkRoster(ARRAYFNAME[1], ARRAYLNAME[1], m, m);
            assert(!m.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) && m.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]));
        } break; case 94: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);//index : 20
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[1], ARRAYV[1]);//index : 21
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[2]);//index : 21
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[1], ARRAYV[3]);//index : 21
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);//index : 22
            BballRoster m2;
            checkRoster("*", ARRAYLNAME[1], m, m2);
            assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[1]) &&
                   !m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   !m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 95: {
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[0], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[2]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[2], ARRAYV[3]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            checkRoster(ARRAYFNAME[1], "*", m, m2);
            assert(m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[0]) &&
                   m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[2]) &&
                   !m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   !m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 96: {
            string all = "*";
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[0], ARRAYV[0]);
            m.signPlayer(ARRAYFNAME[0], ARRAYLNAME[1], ARRAYV[1]);
            m.signPlayer(ARRAYFNAME[1], ARRAYLNAME[1], ARRAYV[2]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[1], ARRAYV[3]);
            m.signPlayer(ARRAYFNAME[2], ARRAYLNAME[2], ARRAYV[2]);
            BballRoster m2;
            checkRoster("*", "*", m, m2);
            assert(m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[1], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[1]) &&
                   m2.playerOnRoster(ARRAYFNAME[0], ARRAYLNAME[0]) &&
                   m2.playerOnRoster(ARRAYFNAME[2], ARRAYLNAME[2]));
        } break; case 97: {
            BballRoster m2 = m;
            BballRoster m3;
            checkRoster("*", "*", m2, m3);
            assert(m3.howManyPlayers() == m.howManyPlayers());
        } break; case 98: {
            BballRoster m2;
            BballRoster m3(m);
            checkRoster("*", "*", m2, m3);
            assert(m3.rosterEmpty());
        } break; case 99: {
            BballRoster m2;
            checkRoster("*", "*", m2, m2);
            assert(m2.howManyPlayers() == 0);
        } break; case 100: {
            const int NITEMS = 2000;
            for (int k = 0; k < NITEMS; k++)
                assert(m.signPlayer(std::to_string(k), std::to_string(k), SOMEVALUE));
            assert(m.howManyPlayers() == NITEMS);
        }
    }
}


int main()
{
    
    int n;
    for(int i =0; i < 101; i++)
    {
        cout << "Enter test number: ";
        cin >> n;
        testone(n);
        cout << "Passed" << endl;
    }
}

/*
 UPDATED NOTES :
 OCT 22nd 2019 13:20 : Test case 11 and case 57 is not conflicting.
 OCT 22nd 2019 13:31 : Test 57 passed.
 OCT 22nd 2019 14:05 : Test 73, 74, 75, 83 has assertion fail.
 OCT 22nd 2019 17:40 : Test 73 passed
 OCT 22nd 2019 18:26 : Test 83 passed
 OCT 23rd 2019 10:24 : Test 82 fail
 OCT 23rd 2019 11:29 : Test 83 ask program to change a value of player already on bbJoined when that player is already existed on bbOne or bbJoined
 OCT 23rd 2019 11:34 : Test 84 ask program to check whether the player is still on bbJoined or not. 
 */
