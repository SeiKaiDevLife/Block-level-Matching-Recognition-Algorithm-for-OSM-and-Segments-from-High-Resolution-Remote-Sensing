// SeiKai @ Second Institute Of Oceanography, MNR

#pragma once
#pragma execution_character_set("utf-8")

#include "3rdPort.h"
#include "CommonUtils.h"

// 角直方图类
class AngleHistogram {
public:
	// 构造对象，确认默认角直方图列数
	AngleHistogram(int _binCount = 0) { this->binCount = _binCount; };

	// 析构对象，释放空间
	~AngleHistogram() { /*if (AngleHis) delete[] AngleHis;*/ };

private:
	int binCount;				// 角直方图列数

	double * AngleHis;			// 角直方图

	double dPerimeter;			// 周长

	// 将数值添加到角直方图中
	int AddHisValue(double HisAngleKey, double HisValue);

	// 将数值从角直方图中减去
	int SubHisValue(double HisAngleKey, double HisValue);

public:
	// 初始化角直方图
	int InitHistogram();

	// 设置角直方图的列数
	int SetBinCount(int _binCount);

	// 计算图像角直方图
	int CalAngleHis(BG_Polygon bg_Polygon, double _dPerimeter);

	// 计算图像角直方图
	int CalAngleHis(BG_MultiPolygon bg_MultiPolygon, double _dPerimeter);

	// 获得binCount
	int GetbinCount();

	// 获得某一项目的数值
	double GetbinValue(int binKey);
};


// 角直方图匹配类
class AngleHistogramMatcher {
public:
	// 构造对象，确认默认角直方图列数
	AngleHistogramMatcher(int _binCount) { this->binCount = _binCount; OriPerimeter = 0; };

private:
	int binCount;				// 角直方图列数

	double OriPerimeter;		// 原有多边形的周长

	// 计算两个角直方图的匹配分数
	double CalculateHisScore(AngleHistogram A_AngleHis, AngleHistogram B_AngleHis);

	// 计算一个角直方图的分数
	double GetHisTotalScore(AngleHistogram AngleHis);

	// 计算两个角直方图差分的分数
	double CalHisSymDiffScore(AngleHistogram A_AngleHis, AngleHistogram B_AngleHis);

	// 设置角直方图的列数
	int SetBinCount(int _binCount);

public:
	// 计算匹配得分
	double CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon);

	// 计算匹配得分
	double CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon,
		BG_MultiPolygon B_bg_Ori_MultiPolygon,
		BG_Polygon B_bg_New_Polygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, AngleHistogram A_AngleHis,
		BG_MultiPolygon B_bg_Ori_MultiPolygon,
		BG_Polygon B_bg_New_Polygon);
};
