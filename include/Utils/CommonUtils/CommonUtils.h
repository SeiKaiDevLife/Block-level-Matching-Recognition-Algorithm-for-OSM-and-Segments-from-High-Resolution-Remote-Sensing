// SeiKai @ Second Institute Of Oceanography, MNR

#pragma once
#pragma execution_character_set("utf-8")

#include "3rdPort.h"

class CommonUtils {
public:
	CommonUtils();
	~CommonUtils();

public:
	// 计算两点间距离
	double CalDistance(
		double Point_A_X, double Point_A_Y,
		double Point_B_X, double Point_B_Y);

	// 计算两点间的角度
	double CalAngle(
		double Point_A_X, double Point_A_Y,
		double Point_B_X, double Point_B_Y);

	// 归一化BG_Polygon
	BG_Polygon ReCalPolygon(BG_Polygon bg_Polygon, MY_ENVELOPE my_Envelope);

	// 归一化BG_MultiPoint
	BG_MultiPoint ReCalMultiPoint(BG_MultiPoint bg_MultiPoint, MY_ENVELOPE my_Envelope);

	// 归一化BG_MultiPolygon
	BG_MultiPolygon ReCalMultiPolygon(BG_MultiPolygon bg_Multipolygon, MY_ENVELOPE my_Envelope);

	// 将BG_Polygon类型转化为BG_MultiPoint
	BG_MultiPoint ConvertPolygonToMultiPoint(BG_Polygon bg_Polygon);

	// 将BG_MultiPolygon类型转化为BG_MultiPoint
	BG_MultiPoint ConvertMultiPolygonToMultiPoint(BG_MultiPolygon bg_MultiPolygon);

	// 将两个多边形进行合并
	BG_MultiPolygon UnionPolygon(BG_MultiPolygon bg_MultiPolygon, BG_Polygon bg_Polygon);

	// 计算bg_MultiPolygon添加一个bg_Polygon后的重心
	BG_Point CalCentroid(BG_MultiPolygon bg_MultiPolygon, double OriArea, BG_Point OriCentorid, BG_Polygon bg_Polygon);

	// 计算BG_Polygon周长
	double CalPerimeter(BG_Polygon bg_Polygon);

	// 计算BG_MultiPolygon周长
	double CalPerimeter(BG_MultiPolygon bg_MultiPolygon);

	// 计算bg_MultiPolygon添加一个bg_Polygon后的周长
	double CalPerimeter(BG_MultiPolygon bg_MultiPolygon, BG_Polygon bg_Polygon);

	// 计算两个多边形重合面积
	double CalOverlapArea(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon);

	// 计算两个多边形重合面积
	double CalOverlapArea(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算两个多边形重合面积
	double CalOverlapArea(BG_MultiPolygon A_bg_MultiPolygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算两个多边形重合面积
	double CalOverlapArea(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon, double OriOverlapArea);

	// 计算两个多边形差分面积
	double CalSymDiffArea(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon);

	// 计算两个多边形差分面积
	double CalSymDiffArea(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算三个多边形差分面积
	double CalSymDiffArea(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_Ori_MultiPolygon, BG_Polygon B_bg_new_Polygon);

	// 计算两个多边形交集的Envelope对角线距离
	double CalUnionEnveDistance(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon);

	// 计算两个多边形交集的Envelope对角线距离
	double CalUnionEnveDistance(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon);

	// 计算三个多边形交集的Envelope对角线距离
	double CalUnionEnveDistance(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_Ori_MultiPolygon, BG_Polygon B_bg_new_Polygon);

	// 计算两个点集之间的Hausdorff距离
	double CalHausdorffDistance(BG_MultiPoint A_bg_MultiPoint, BG_MultiPoint B_bg_MultiPoint);

	// 计算包络圈的面积
	double CalAreaFromEnvelope(MY_ENVELOPE my_Envelope);
};

//CommonUtils comUtils;
