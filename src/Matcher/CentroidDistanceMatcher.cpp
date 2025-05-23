// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "CentroidDistanceMatcher.h"

/*******************************************************************************
 * Calculate the match Score of CentroidDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Polygon polygon B
 * @return match Score
 *******************************************************************************/
double CentroidDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_Polygon);

	// 计算两个多边形的重心
	BG_Point A_bg_Centorid, B_bg_Centorid;
	bg::centroid(A_bg_Polygon, A_bg_Centorid);
	bg::centroid(B_bg_Polygon, B_bg_Centorid);

	// 计算重心距离
	double CentroidDistance = CommonUtils().CalDistance(
		bg::get<0>(A_bg_Centorid), bg::get<1>(A_bg_Centorid),
		bg::get<0>(B_bg_Centorid), bg::get<1>(B_bg_Centorid));

	// 计算匹配得分
	return 1.00 - CentroidDistance / EnvelopDistance;
}


/*******************************************************************************
 * Calculate the match Score of CentroidDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_MultiPolygon multipolygon B
 * @return match Score
 *******************************************************************************/
double CentroidDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_MultiPolygon);

	// 计算两个多边形的重心
	BG_Point A_bg_Centorid, B_bg_Centorid;
	bg::centroid(A_bg_Polygon, A_bg_Centorid);
	bg::centroid(B_bg_MultiPolygon, B_bg_Centorid);

	// 计算重心距离
	double CentroidDistance = CommonUtils().CalDistance(
		bg::get<0>(A_bg_Centorid), bg::get<1>(A_bg_Centorid),
		bg::get<0>(B_bg_Centorid), bg::get<1>(B_bg_Centorid));

	double a = 1.00 - CentroidDistance / EnvelopDistance;

	// 计算匹配得分
	return 1.00 - CentroidDistance / EnvelopDistance;
}


/*******************************************************************************
 * Calculate the match Score of CentroidDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Ori_MultiPolygon original multipolygon B
 * @param Ori_MultiArea original Area B
 * @param Ori_Centorid original Centorid B
 * @param B_New_Polygon new polygon B
 * @return match Score
 *******************************************************************************/
double CentroidDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, 
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, BG_Point Ori_Centorid, 
	BG_Polygon B_New_Polygon)
{
	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_Ori_MultiPolygon, B_New_Polygon);

	// 计算两个多边形的重心
	BG_Point A_bg_Centroid, B_bg_Centroid;
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	B_bg_Centroid = CommonUtils().CalCentroid(B_bg_Ori_MultiPolygon, Ori_MultiArea, Ori_Centorid, B_New_Polygon);

	// 计算重心距离
	double CentroidDistance = CommonUtils().CalDistance(
		bg::get<0>(A_bg_Centroid), bg::get<1>(A_bg_Centroid),
		bg::get<0>(B_bg_Centroid), bg::get<1>(B_bg_Centroid));

	// 计算匹配得分
	return 1.00 - CentroidDistance / EnvelopDistance;
}


/*******************************************************************************
 * Calculate the match Score of CentroidDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param A_bg_Centroid the Centorid A
 * @param B_bg_Ori_MultiPolygon original multipolygon B
 * @param Ori_MultiArea original Area B
 * @param Ori_Centorid original Centorid B
 * @param B_New_Polygon new polygon B
 * @return match Score
 *******************************************************************************/
double CentroidDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_Point A_bg_Centroid,
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double Ori_MultiArea, BG_Point Ori_Centorid,
	BG_Polygon B_New_Polygon)
{
	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_Ori_MultiPolygon, B_New_Polygon);

	// 计算两个多边形的重心
	BG_Point B_bg_Centroid;
	B_bg_Centroid = CommonUtils().CalCentroid(B_bg_Ori_MultiPolygon, Ori_MultiArea, Ori_Centorid, B_New_Polygon);

	// 计算重心距离
	double CentroidDistance = CommonUtils().CalDistance(
		bg::get<0>(A_bg_Centroid), bg::get<1>(A_bg_Centroid),
		bg::get<0>(B_bg_Centroid), bg::get<1>(B_bg_Centroid));

	// 计算匹配得分
	return 1.00 - CentroidDistance / EnvelopDistance;
}
