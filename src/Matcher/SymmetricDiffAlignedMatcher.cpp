// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "SymmetricDiffAlignedMatcher.h"

/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param A_Envelope envelope A
 * @param B_bg_Polygon polygon B
 * @param B_Envelope envelope B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffAlignedMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	BG_Point A_bg_Centroid, B_bg_Centroid;

	// 计算两个多边形的重心
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	bg::centroid(B_bg_Polygon, B_bg_Centroid);
	
	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 将A多边形的重心移动到和B相同位置
	BG_Polygon A_bg_Polygon_tran;
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	bg::transform(A_bg_Polygon, A_bg_Polygon_tran, translator);

	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon_tran, B_bg_Polygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon_tran);
	double B_Area = bg::area(B_bg_Polygon);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}


/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param A_Envelope envelope A
 * @param B_bg_MultiPolygon multipolygon B
 * @param B_Envelope envelope B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffAlignedMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	BG_Point A_bg_Centroid, B_bg_Centroid;

	// 计算两个多边形的重心
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	bg::centroid(B_bg_MultiPolygon, B_bg_Centroid);

	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 将A多边形的重心移动到和B相同位置
	BG_Polygon A_bg_Polygon_tran;
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	bg::transform(A_bg_Polygon, A_bg_Polygon_tran, translator);

	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon_tran, B_bg_MultiPolygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon_tran);
	double B_Area = bg::area(B_bg_MultiPolygon);

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
double SymmetricDiffAlignedMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, 
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, BG_Point Ori_Centorid, 
	BG_Polygon B_New_Polygon)
{
	// 计算两个多边形的重心
	BG_Point A_bg_Centroid, B_bg_Centroid;
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	B_bg_Centroid = CommonUtils().CalCentroid(B_bg_Ori_MultiPolygon, Ori_MultiArea, Ori_Centorid, B_New_Polygon);

	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 将A多边形的重心移动到和B相同位置
	BG_Polygon A_bg_Polygon_tran;
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	bg::transform(A_bg_Polygon, A_bg_Polygon_tran, translator);

	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon_tran, B_bg_Ori_MultiPolygon, B_New_Polygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon_tran);
	double B_Area = Ori_MultiArea + bg::area(B_New_Polygon);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}


/*******************************************************************************
 * Calculate the match Score of SymmetricDiffMatcher
 * @param A_bg_Polygon polygon A
 * @param A_bg_Centroid the Centroid of Polygon A
 * @param A_Area the Area of Polygon A
 * @param B_bg_Ori_MultiPolygon Original multipolygon B
 * @param Ori_MultiArea Original Area B
 * @param B_New_Polygon new polygon B
 * @return match Score
 *******************************************************************************/
double SymmetricDiffAlignedMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_Point A_bg_Centroid, double A_Area,
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, BG_Point Ori_Centorid,
	BG_Polygon B_New_Polygon)
{
	// 计算两个多边形的重心
	BG_Point B_bg_Centroid;
	B_bg_Centroid = CommonUtils().CalCentroid(B_bg_Ori_MultiPolygon, Ori_MultiArea, Ori_Centorid, B_New_Polygon);

	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 将A多边形的重心移动到和B相同位置
	BG_Polygon A_bg_Polygon_tran;
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	bg::transform(A_bg_Polygon, A_bg_Polygon_tran, translator);

	// 计算多边形差分部分面积
	double SymDiffArea = CommonUtils().CalSymDiffArea(A_bg_Polygon_tran, B_bg_Ori_MultiPolygon, B_New_Polygon);

	// 计算两个多边形的面积
	double B_Area = Ori_MultiArea + bg::area(B_New_Polygon);

	// 计算匹配得分
	return 1.00 - SymDiffArea / (A_Area + B_Area);
}
