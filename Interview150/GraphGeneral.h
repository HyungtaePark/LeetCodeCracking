#pragma once
#include <vector>
#include <string>
#include <set>

using namespace std;

namespace Interview150
{
	class GraphGeneral
	{
	protected:
		bool canFinish_help(int idCourse, vector<vector<int>>& vCources, vector<int>& vCache, vector<bool>& vVisit);

	public:

		// 207. Course Schedule
		bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
	};

}