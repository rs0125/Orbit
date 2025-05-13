#include <bits/stdc++.h>
#include "utils.h"

class Obj
{
public:
    vector<vertex> VertexBuffer;
    vector<vector<int>> EdgeBuffer;

    bool loadOBJ(const string &filename, float zOffset = 10.0f)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Failed to open OBJ file: " << filename << endl;
            return false;
        }

        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string type;
            iss >> type;

            if (type == "v")
            {
                float x, y, z;
                iss >> x >> y >> z;
                VertexBuffer.emplace_back(vertex({x, y, z + zOffset}));
            }
            else if (type == "f")
            {
                vector<int> face;
                string vert;
                while (iss >> vert)
                {
                    // Handle formats like f 1, f 1/1, f 1/1/1
                    int idx = stoi(vert.substr(0, vert.find('/')));
                    face.push_back(idx - 1); // .obj is 1-indexed
                }
                if (face.size() >= 3)
                {
                    // Triangulate if necessary
                    for (size_t i = 1; i < face.size() - 1; ++i)
                    {
                        EdgeBuffer.push_back({face[0], face[i], face[i + 1]});
                    }
                }
            }
        }
        return true;
    }
};