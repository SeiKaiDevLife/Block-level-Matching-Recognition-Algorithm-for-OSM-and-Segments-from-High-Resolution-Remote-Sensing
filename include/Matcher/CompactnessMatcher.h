// SeiKai @ Second Institute Of Oceanography, MNR

#pragma once
#pragma execution_character_set("utf-8")

#include "3rdPort.h"
#include "CommonUtils.h"

// 紧密度指数匹配类
class CompactnessMatcher {
public:
	// 计算匹配得分
	double CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon);

	// 计算匹配得分
	double CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, 
		BG_MultiPolygon B_bg_Ori_MultiPolygon, double OriArea,
		BG_Polygon B_bg_new_Polygon);

	// 计算匹配得分
	double CalculateMatchScore(
		BG_Polygon A_bg_Polygon, double A_Perimeter, double A_Area,
		BG_MultiPolygon B_bg_Ori_MultiPolygon, double OriArea,
		BG_Polygon B_bg_new_Polygon);

	// 计算紧密度
	double CalCharacteristic(double dPerimeter, double dArea);
};
