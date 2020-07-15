#include <cmath>
#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "dbscan.h"

using namespace std;

/*********

dbscan_cpp

Summary: Density-Based Spatial Clustering of Applications with Noise inplemented in C++

Parameters:
	cluster: an array contains all points, points' clusterIndex and dataType are initiated as 0
	totalPts: number of points in cluster

Return: number of clusters

*********/

int dbscan_cpp(clusterData *cluster, const int totalPts, const double eps, const unsigned int minPts)
{
	vector<int> coreObj;
	vector<set<int>> neighbors(totalPts);

	for (int j = 0; j < totalPts; j++) {
		for (int i = 0; i < totalPts; i++) {
			double dist = sqrt(pow((cluster[j].coordinate[0] - cluster[i].coordinate[0]), 2)
				+ pow((cluster[j].coordinate[1] - cluster[i].coordinate[1]), 2));
			if (dist <= eps)
				neighbors[j].insert(i);
		}
		if (neighbors[j].size() >= minPts)
			coreObj.push_back(j);
	}

	set<int> unvisitedPts;
	for (int i = 0; i < totalPts; i++)
		unvisitedPts.insert(i);

	int k = 1; //the index of first cluster is 1, not 0
	vector<set<int>> C;
	while (coreObj.size() > 0)
	{
		set<int> unvisitedPtsOld(unvisitedPts.begin(), unvisitedPts.end());
		int omg = coreObj[0];
		list<int> Q;
		Q.push_back(omg);
		unvisitedPts.erase(omg);
		while (Q.size() > 0)
		{
			int q = Q.front();
			Q.remove(q);
			cluster[q].clusterIndex = k;
			if (neighbors[q].size() >= minPts)
			{
				cluster[q].dataType = 2;
				set<int> delta;
				set_intersection(unvisitedPts.begin(), unvisitedPts.end(), neighbors[q].begin(), neighbors[q].end(), inserter(delta, delta.begin()));
				Q.insert(Q.end(), delta.begin(), delta.end());
				set<int> diff;
				set_difference(unvisitedPts.begin(), unvisitedPts.end(), delta.begin(), delta.end(), inserter(diff, diff.begin()));
				unvisitedPts.clear();
				copy(diff.begin(), diff.end(), std::inserter(unvisitedPts, unvisitedPts.end()));
			}
			else
				cluster[q].dataType = 1;
		}
		k = k + 1;
		set<int> c;
		set_difference(unvisitedPtsOld.begin(), unvisitedPtsOld.end(), unvisitedPts.begin(), unvisitedPts.end(), inserter(c, c.begin()));
		C.push_back(c);
		set<int> diff;
		sort(coreObj.begin(), coreObj.end());
		set_difference(coreObj.begin(), coreObj.end(), c.begin(), c.end(), inserter(diff, diff.begin()));
		coreObj.assign(diff.begin(), diff.end());
	}

	return k-1;
}
