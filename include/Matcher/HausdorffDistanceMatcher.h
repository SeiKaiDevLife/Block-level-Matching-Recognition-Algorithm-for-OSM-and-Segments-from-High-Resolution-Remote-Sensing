// SeiKai @ Second Institute Of Oceanography, MNR

#pragma once
#pragma execution_character_set("utf-8")

#include "3rdPort.h"
#include "CommonUtils.h"

// 豪斯多夫距离匹配类
class HausdorffDistanceMatcher {
public:
	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, BG_MultiPoint A_bg_MultiPoint,
		BG_Polygon B_bg_Polygon, BG_MultiPoint B_bg_MultiPoint);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, BG_MultiPoint A_bg_MultiPoint, 
		BG_MultiPolygon B_bg_MultiPolygon, BG_MultiPoint B_bg_MultiPoint);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, BG_MultiPoint A_bg_MultiPoint,
		BG_MultiPolygon B_bg_Ori_MultiPolygon, BG_MultiPoint B_bg_Ori_MultiPoint, double Ori_MultiArea, BG_Point Ori_Centorid,
		BG_Polygon B_bg_New_MultiPolygon, BG_MultiPoint B_bg_New_MultiPoint);
};
