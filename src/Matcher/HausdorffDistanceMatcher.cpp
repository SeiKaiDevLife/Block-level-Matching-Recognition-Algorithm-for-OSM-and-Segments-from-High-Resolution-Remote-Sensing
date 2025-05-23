// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "HausdorffDistanceMatcher.h"

/*******************************************************************************
 * Calculate the match Score of HausdorffDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param A_bg_MultiPoint multipoint A
 * @param B_bg_Polygon polygon B
 * @param B_bg_MultiPoint multipoint B
 * @return match Score
 *******************************************************************************/
double HausdorffDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_MultiPoint A_bg_MultiPoint,
	BG_Polygon B_bg_Polygon, BG_MultiPoint B_bg_MultiPoint)
{
	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_Polygon);

	// 计算两个多边形的重心
	BG_Point A_bg_Centroid, B_bg_Centroid;
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	bg::centroid(B_bg_Polygon, B_bg_Centroid);

	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 将A多边形的重心移动到和B相同位置
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	BG_MultiPoint A_bg_MultiPoint_tran;
	bg::transform(A_bg_MultiPoint, A_bg_MultiPoint_tran, translator);

	// 计算顶点集合的Hausdorff距离
	double HausDistance = CommonUtils().CalHausdorffDistance(A_bg_MultiPoint_tran, B_bg_MultiPoint);

	// 计算匹配得分
	return 1.00 - HausDistance / EnvelopDistance;
}


/*******************************************************************************
 * Calculate the match Score of HausdorffDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param A_bg_MultiPoint MultiPoint A
 * @param B_bg_MultiPolygon multipolygon B
 * @param B_bg_MultiPoint MultiPoint B
 * @return match Score
 *******************************************************************************/
double HausdorffDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_MultiPoint A_bg_MultiPoint,
	BG_MultiPolygon B_bg_MultiPolygon, BG_MultiPoint B_bg_MultiPoint)
{
	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_MultiPolygon);

	// 计算两个多边形的重心
	BG_Point A_bg_Centroid, B_bg_Centroid;
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	bg::centroid(B_bg_MultiPolygon, B_bg_Centroid);

	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 将A多边形的重心移动到和B相同位置
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	BG_MultiPoint A_bg_MultiPoint_tran;
	bg::transform(A_bg_MultiPoint, A_bg_MultiPoint_tran, translator);

	// 计算顶点集合的Hausdorff距离
	double HausDistance = CommonUtils().CalHausdorffDistance(A_bg_MultiPoint_tran, B_bg_MultiPoint);

	// 计算匹配得分
	return 1.00 - HausDistance / EnvelopDistance;
}


/*******************************************************************************
 * Calculate the match Score of HausdorffDistanceMatcher
 * @param A_bg_Polygon polygon A
 * @param A_bg_MultiPoint MultiPoint A
 * @param B_bg_Ori_MultiPolygon Ori multipolygon B
 * @param B_bg_Ori_MultiPoint Ori MultiPoint B
 * @param Ori_MultiArea Ori Area
 * @param Ori_Centorid Ori Centorid
 * @param B_bg_New_MultiPolygon New multipolygon B
 * @param B_bg_New_MultiPoint New multiPoint B
 * @return match Score
 *******************************************************************************/
double HausdorffDistanceMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, BG_MultiPoint A_bg_MultiPoint, 
	BG_MultiPolygon B_bg_Ori_MultiPolygon, BG_MultiPoint B_bg_Ori_MultiPoint, double Ori_MultiArea, BG_Point Ori_Centorid, 
	BG_Polygon B_bg_New_Polygon, BG_MultiPoint B_bg_New_MultiPoint)
{
	// 计算多边形交集
	BG_MultiPolygon B_bg_MultiPolygon = B_bg_Ori_MultiPolygon;
	B_bg_MultiPolygon.push_back(B_bg_New_Polygon);

	// 计算点集交集
	BG_MultiPoint B_bg_MultiPoint = B_bg_Ori_MultiPoint;
	bg::append(B_bg_MultiPoint, A_bg_MultiPoint);

	// 计算多边形并集Envelope对角线距离
	double EnvelopDistance = CommonUtils().CalUnionEnveDistance(A_bg_Polygon, B_bg_MultiPolygon);

	// 计算两个多边形的重心
	BG_Point A_bg_Centroid, B_bg_Centroid;
	bg::centroid(A_bg_Polygon, A_bg_Centroid);
	B_bg_Centroid = CommonUtils().CalCentroid(B_bg_Ori_MultiPolygon, Ori_MultiArea, Ori_Centorid, B_bg_New_Polygon);

	// 计算移动的距离
	double dx = bg::get<0>(B_bg_Centroid) - bg::get<0>(A_bg_Centroid);
	double dy = bg::get<1>(B_bg_Centroid) - bg::get<1>(A_bg_Centroid);

	// 遍历所有多边形组合，寻找公共边从点集中减去
	for (auto it1 = B_bg_MultiPolygon.begin(); it1 != B_bg_MultiPolygon.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != B_bg_MultiPolygon.end(); ++it2) {

			// 如果两个多边形相邻
			if (bg::touches(*it1, *it2)) {

				// 提取公共边
				BG_MultiPoint intersection;
				bg::intersection(*it1, *it2, intersection);

				// 如果存在公共边
				if (!intersection.empty()) {

					// 从点集中去除
					for (size_t i = 1; i < intersection.size() - 1; ++i)
					{
						// 查找并删除特定坐标的点
						auto it = std::find_if(B_bg_MultiPoint.begin(), B_bg_MultiPoint.end(), [&](const BG_Point& p) {
							return bg::get<0>(p) == bg::get<0>(intersection[i]) && bg::get<1>(p) == bg::get<1>(intersection[i]);
						});

						if (it != B_bg_MultiPoint.end()) {
							B_bg_MultiPoint.erase(it);
						}
					}
				}
			}
		}
	}

	// 将A多边形的重心移动到和B相同位置
	bg::strategy::transform::translate_transformer<double, 2, 2> translator(dx, dy);
	BG_MultiPoint A_bg_MultiPoint_tran;
	bg::transform(A_bg_MultiPoint, A_bg_MultiPoint_tran, translator);

	// 计算顶点集合的Hausdorff距离
	double HausDistance = CommonUtils().CalHausdorffDistance(A_bg_MultiPoint_tran, B_bg_MultiPoint);

	double a = 1.00 - HausDistance / EnvelopDistance;

	// 计算匹配得分
	return 1.00 - HausDistance / EnvelopDistance;
}
