#ifndef DBSCAN_H
#define DBSCAN_H

struct clusterData
{
	int coordinate[2]; //coordinate[0]:x, coordinate[1]:y
	int clusterIndex = 0;
	int dataType = 0; //0:noise,1:boundary,2:core
};

int dbscan_cpp(clusterData *cluster, const int totalPts, const double eps, const unsigned int minPts);

#endif // !DBSCAN_H
