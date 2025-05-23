// SeiKai @ Second Institute Of Oceanography, MNR

#pragma once
#pragma execution_character_set("utf-8")

#include "3rdPort.h"
#include "CommonUtils.h"

// 重心对齐差分匹配类
class SymmetricDiffAlignedMatcher {
public:
	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, 
		BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, BG_Point Ori_Centorid,
		BG_Polygon B_New_Polygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, BG_Point A_bg_Centroid, double A_Area,
		BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, BG_Point Ori_Centorid,
		BG_Polygon B_New_Polygon);
};
