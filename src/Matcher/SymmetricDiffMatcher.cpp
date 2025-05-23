// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "SymmetricDiffMatcher.h"

/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Polygon polygon B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon, B_bg_Polygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon);
	double B_Area = bg::area(B_bg_Polygon);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}


/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_MultiPolygon multipolygon B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon, B_bg_MultiPolygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon);
	double B_Area = bg::area(B_bg_MultiPolygon);

	double a = 1.00 - SymDiffArea / (A_Area + B_Area);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}


/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Ori_MultiPolygon Original multipolygon B
 * @param Ori_MultiArea Original Area B
 * @param B_New_Polygon new polygon B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, 
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, 
	BG_Polygon B_New_Polygon)
{
	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon, B_bg_Ori_MultiPolygon, B_New_Polygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon);
	double B_Area = Ori_MultiArea + bg::area(B_New_Polygon);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}


/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param A_Area the area of polygon A
 * @param B_bg_Ori_MultiPolygon Original multipolygon B
 * @param Ori_MultiArea Original Area B
 * @param B_New_Polygon new polygon B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, double A_Area,
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea,
	BG_Polygon B_New_Polygon)
{
	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon, B_bg_Ori_MultiPolygon, B_New_Polygon);

	// 计算两个多边形的面积
	double B_Area = Ori_MultiArea + bg::area(B_New_Polygon);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}
