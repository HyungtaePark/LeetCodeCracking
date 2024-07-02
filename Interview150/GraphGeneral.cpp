#pragma once
#include "GraphGeneral.h"
#include <map>
#include <set>

namespace Interview150
{
    
    // 207. Course Schedule
    bool GraphGeneral::canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> vectNodes;
        vectNodes.resize(numCourses, vector<int>());
        for (int k = 0; k < prerequisites.size(); ++k)
            vectNodes[prerequisites[k][0]].push_back(prerequisites[k][1]);

        // DFS approach.
        // node cache. 
        vector<int> vCache;
        vCache.resize(numCourses, -1);	// -1(undone), 0(failed), 1(successed)
        for (int k = 0; k < numCourses; ++k)
        {
            vector<bool> vVisit;
            vVisit.resize(numCourses, false);
            if (!canFinish_help(k, vectNodes, vCache, vVisit))
                return false;
        }
        return true;
    }

    // 210. Course Schedule II
    vector<int> GraphGeneral::findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> vBuff;
        vBuff.resize(numCourses, vector<int>{});
        for (int q = 0; q < numCourses; ++q)
        {
            vBuff[prerequisites[q][0]].push_back(prerequisites[q][1]);
        }

        vector<int> vRet;
        for (int q = 0; q < numCourses; ++q)
        {
            // find the course that visits all the other course.
            vector<bool> vVisit;
            vVisit.resize(numCourses, false);
            findOrder_helper(vVisit, q, vBuff);
        }
        return vRet;
    }


    // Helper.
    bool GraphGeneral::findOrder_helper(vector<bool>& vVisit, int idxCourse, const vector<vector<int>>& vCBuff)
    {
        if (vVisit[idxCourse])
            return false;             // has cycle.

        vVisit[idxCourse] = true;
        for (int q = 0; q < vCBuff[idxCourse].size(); ++q)
        {
            if (!findOrder_helper(vVisit, vCBuff[idxCourse][q], vCBuff))
                return false;
        }
        vVisit[idxCourse] = false;
        return true;
    }

    bool GraphGeneral::canFinish_help(int idCourse, vector<vector<int>>& vCources, vector<int>& vCache, vector<bool>& vVisit)
    {
        if (vCache[idCourse] >= 0)
            return vCache[idCourse] == 1;

        if (vVisit[idCourse])
        {
            vCache[idCourse] = false;
            return false;
        }

        vVisit[idCourse] = true;
        for (int q = 0; q < vCources[idCourse].size(); ++q)
        {
            int nextCourse = vCources[idCourse][q];
            if (!canFinish_help(nextCourse, vCources, vCache, vVisit))
            {
                vCache[idCourse] = 0;
                return false;
            }
        }
        vVisit[idCourse] = false;
        // successed anyway!
        vCache[idCourse] = 1;
        return true;
    }
}