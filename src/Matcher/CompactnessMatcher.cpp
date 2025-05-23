// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "CompactnessMatcher.h"

/*******************************************************************************
 * Calculate the match Score of CompactnessMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Polygon polygon B
 * @return match Score
 *******************************************************************************/
double CompactnessMatcher::CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 计算两个多边形周长
	double A_Perimeter = bg::perimeter(A_bg_Polygon);
	double B_Perimeter = bg::perimeter(B_bg_Polygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon);
	double B_Area = bg::area(B_bg_Polygon);

	// 计算匹配得分
	return 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) - 
		CalCharacteristic(B_Perimeter, B_Area));
}


/*******************************************************************************
 * Calculate the match Score of CompactnessMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_MultiPolygon multipolygon B
 * @return match Score
 *******************************************************************************/
double CompactnessMatcher::CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 计算两个多边形周长
	double A_Perimeter = CommonUtils().CalPerimeter(A_bg_Polygon);
	double B_Perimeter = CommonUtils().CalPerimeter(B_bg_MultiPolygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon);
	double B_Area = bg::area(B_bg_MultiPolygon);

	double a = 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) -
		CalCharacteristic(B_Perimeter, B_Area));

	// 计算匹配得分
	return 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) -
		CalCharacteristic(B_Perimeter, B_Area));
}


/*******************************************************************************
 * Calculate the match Score of CompactnessMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Ori_MultiPolygon Ori multipolygon B
 * @param OriArea Ori Area B
 * @param B_bg_new_Polygon new Polygon B
 * @return match Score
 *******************************************************************************/
double CompactnessMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, 
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double OriArea, 
	BG_Polygon B_bg_new_Polygon)
{
	// 计算两个多边形周长
	double A_Perimeter = CommonUtils().CalPerimeter(A_bg_Polygon);
	double B_Perimeter = CommonUtils().CalPerimeter(B_bg_Ori_MultiPolygon, B_bg_new_Polygon);

	// 计算两个多边形的面积
	double A_Area = bg::area(A_bg_Polygon);
	double B_Area = OriArea + bg::area(B_bg_new_Polygon);

	double a = 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) -
		CalCharacteristic(B_Perimeter, B_Area));

	// 计算匹配得分
	return 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) -
		CalCharacteristic(B_Perimeter, B_Area));
}


/*******************************************************************************
 * Calculate the match Score of CompactnessMatcher
 * @param A_bg_Polygon polygon A
 * @param A_Perimeter the Perimeter of polygon A
 * @param A_Area the area of Polygon A
 * @param B_bg_Ori_MultiPolygon Ori multipolygon B
 * @param OriArea Ori Area B
 * @param B_bg_new_Polygon new Polygon B
 * @return match Score
 *******************************************************************************/
double CompactnessMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, double A_Perimeter, double A_Area,
	BG_MultiPolygon B_bg_Ori_MultiPolygon, double OriArea,
	BG_Polygon B_bg_new_Polygon)
{
	// 计算两个多边形周长
	double B_Perimeter = CommonUtils().CalPerimeter(B_bg_Ori_MultiPolygon, B_bg_new_Polygon);

	// 计算两个多边形的面积
	double B_Area = OriArea + bg::area(B_bg_new_Polygon);

	double a = 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) -
		CalCharacteristic(B_Perimeter, B_Area));

	// 计算匹配得分
	return 1.00 - abs(
		CalCharacteristic(A_Perimeter, A_Area) -
		CalCharacteristic(B_Perimeter, B_Area));
}


/*******************************************************************************
 * Calculate Compactness Characteristic
 * @param dPerimeter perimeter of polygon
 * @param dArea area of polygon
 * @return characteristic value
 *******************************************************************************/
double CompactnessMatcher::CalCharacteristic(double dPerimeter, double dArea)
{
	// 计算紧密度
	return 4 * M_PI * dArea / dPerimeter / dPerimeter;
}
