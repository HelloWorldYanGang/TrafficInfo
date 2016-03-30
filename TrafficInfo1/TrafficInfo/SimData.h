#ifndef __SIMDATA_H__
#define __SIMDATA_H__

#include <string>
#include "VspdCToMySQL.h"
using namespace std;
class SimData
{
public:

	SimData();
	~SimData();
	vector<string> allDetectorId;

	//当前仿真时间
	string simuTime;
	//
	int simState;  //当前仿真状态 0：未开始 1：运行  2：暂停  3：结束

	int simIndex;//当前仿真编号

	float odValue;  //仿真时的OD值

	//每个检测器对应有几个线圈
	vector<int> loopNumArray;
	//所有线圈的指针
	vector<vector<LOOP*>> netLoop;

public:  

	//路网中每一个detector的每一个loop通过的车辆数(累积量)(有车通过时就刷新)
	vector<vector<int>> countEveryLoop;
	//路网中每一个detector的每一个loop通过的车辆数(累积量)(到达间隔时间时才刷新)
	vector<vector<int>> countEveryLoopDuration;
	//路网中每一个detector的每一个loop通过的车辆数(差分量)
	vector<vector<int>> countEveryLoopDiff;
	//路网中每一个detector所有线圈通过的车辆数
	vector<int> countEveryDetector;

	//每一个线圈上一辆车的占有时间(有车通过时刷新)
	vector<vector<float>> occupancyEveryLoop;
	//统计时段内，占有时间的累加
	vector<vector<float>> occupancyEveryLoopDuration;
	//线圈是否被车占用
	vector<vector<int>> isOccupiedEveryLoop;

	//线圈所属车道平均车速（截止当前时刻）
	vector<vector<float>> velocityEveryLoop;
	//统计时段内平均车速
	vector<vector<float>> velocityEveryLoopDuration;

	//路网仿真时的demand矩阵
	vector<vector<float>> demandMatrix;
	
public:
	//对应roadrecord表信息
	vector<string> allRoadId;
	vector<vector<LINK*> > linkPointerInRoad;  //对应allRoadId上所有Link指针,
	vector<vector<int>> laneNum;//该link车道数
	vector<vector<float> > Roadcount, RoadDelay, RoadDensity, RoadFlow, RoadQueueCount, RoadQueuePCU, RoadQueueLength, RoadSpeed,RoadMaxQueueCount,RoadMaxQueueLength;
	vector<vector<float> > RoadLength;
public:
	//初始化相关变量
	void initCountLoop(int detectorNum);
	void initCountDetector(int detectorNum);

	//初始化demand矩阵
	void initDemandMatrix(int zoneNum);

	//根据从数据库获取的ODvalue设置demand矩阵
	void setDemandMatrix(int zoneNum, float od_value);

	//数据写入数据库
	void writeDetectorDataToSql(VspdCToMySQL* mysql, int detectorNum);

	//初始化Road相关数据
	void initRoadInfo(VspdCToMySQL* mysql);

	void writeRoadDataToSql(VspdCToMySQL* mysql);
};
#endif