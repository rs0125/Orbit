#ifndef OBJUTILS_H
#define OBJUTILS_H

#include <bits/stdc++.h>
#include "utils.h"
using namespace std;

class Obj
{
public:
    bool loadOBJ(const string &filename, float zOffset = 10.0f);
};

#endif