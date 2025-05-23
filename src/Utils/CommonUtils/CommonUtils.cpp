// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "CommonUtils.h"

CommonUtils::CommonUtils()
{
}

CommonUtils::~CommonUtils()
{
}


/*******************************************************************************
 * Calculate the distance between two points
 * @param Point_A_X the x-coordinate of point A
 * @param Point_A_Y the y-coordinate of point A
 * @param Point_B_X the x-coordinate of point B
 * @param Point_B_Y the y-coordinate of point B
 * @return the distance
 *******************************************************************************/
double CommonUtils::CalDistance(double Point_A_X, double Point_A_Y, double Point_B_X, double Point_B_Y)
{
	return sqrt((Point_A_X - Point_B_X) * (Point_A_X - Point_B_X) +
		(Point_A_Y - Point_B_Y) * (Point_A_Y - Point_B_Y));
}


/*******************************************************************************
 * Calculate the angle between two points
 * @param Point_A_X the x-coordinate of point A
 * @param Point_A_Y the y-coordinate of point A
 * @param Point_B_X the x-coordinate of point B
 * @param Point_B_Y the y-coordinate of point B
 * @return the angle
 *******************************************************************************/
double CommonUtils::CalAngle(double Point_A_X, double Point_A_Y, double Point_B_X, double Point_B_Y)
{
	// 计算x与y方向的变化量
	double dx = Point_B_X - Point_A_X;
	double dy = Point_B_Y - Point_A_Y;

	// 计算角度，取值范围(-PI,PI)
	double AngleValue = atan2(dy, dx);

	// 将(-PI,0)范围内的角度加180°，取值范围限定到(0,PI)
	if (AngleValue < 0)
		AngleValue = AngleValue + M_PI;

	// 为了防止M_PI宏定义产生小数点误差，将所有仍然是负值的角度转为0，保证角度非负
	if (AngleValue < 0)
		AngleValue = 0;

	// 计算角度，取值范围(0,PI)
	return AngleValue;
}


/*******************************************************************************
 * Normalize the existing BG_Polygon based on the known range
 * @param bg_Polygon the BG_Polygon to be Normalized
 * @param my_Envelope the known range
 * @return the Normalized BG_Polygon
 *******************************************************************************/
BG_Polygon CommonUtils::ReCalPolygon(BG_Polygon bg_Polygon, MY_ENVELOPE my_Envelope)
{
	double factor = 100000000.0;

	// 定义新的BG_Polygon
	BG_Polygon result_Polygon;

	// 读取外环
	auto exterior_ring = bg::exterior_ring(bg_Polygon);

	// 定义新的外环
	std::vector<BG_Point> transformed_exterior_ring;

	// 遍历每一个已知外环的点
	bg::for_each_point
	(
		exterior_ring, [&](const BG_Point& p) {
		// 定义新的点
		BG_Point transformed_point;

		// 归一化处理
		bg::set<0>(transformed_point, floor((bg::get<0>(p) - my_Envelope.dXmin) / (my_Envelope.dXmax - my_Envelope.dXmin) * factor) / factor);
		bg::set<1>(transformed_point, floor((bg::get<1>(p) - my_Envelope.dYmin) / (my_Envelope.dYmax - my_Envelope.dYmin) * factor) / factor);

		// 新的点加入新的外环
		transformed_exterior_ring.push_back(transformed_point);
	}
	);

	// 新的外环加入新的BG_Polygon
	bg::append(result_Polygon.outer(), transformed_exterior_ring);

	// 读取内环
	auto rings = bg::interior_rings(bg_Polygon);

	// 给新的BG_Polygon开辟内环
	result_Polygon.inners().resize(bg::num_interior_rings(bg_Polygon));

	// 遍历所有内环
	for (std::size_t i = 0; i < bg::num_interior_rings(bg_Polygon); i++)
	{
		// 提取出第i个内环
		auto it = rings.begin();
		std::advance(it, i);

		// 如果还有内环
		if (it != rings.end())
		{
			// 定义新的内环
			std::vector<BG_Point> transformed_interior_ring;

			// 遍历每一个已知内环的点
			bg::for_each_point(
				*it, [&](const BG_Point& p)
			{
				// 定义新的点
				BG_Point transformed_point;

				// 归一化处理
				bg::set<0>(transformed_point, floor((bg::get<0>(p) - my_Envelope.dXmin) / (my_Envelope.dXmax - my_Envelope.dXmin) * factor) / factor);
				bg::set<1>(transformed_point, floor((bg::get<1>(p) - my_Envelope.dYmin) / (my_Envelope.dYmax - my_Envelope.dYmin) * factor) / factor);

				// 新的点加入新的内环
				transformed_interior_ring.push_back(transformed_point);
			}
			);

			// 新的内环加入新的BG_Polygon
			bg::append(result_Polygon.inners()[i], transformed_interior_ring);
		}
	}

	// 返回结果
	return result_Polygon;
}


/*******************************************************************************
* Normalize the existing BG_MultiPoint based on the known range
* @param bg_MultiPoint the BG_MultiPoint to be Normalized
* @param my_Envelope the known range
* @return the Normalized BG_MultiPoint
*******************************************************************************/
BG_MultiPoint CommonUtils::ReCalMultiPoint(BG_MultiPoint bg_MultiPoint, MY_ENVELOPE my_Envelope)
{
	double factor = 100000000.0;

	// 定义新的BG_MultiPoint
	BG_MultiPoint result_MultiPoint;

	// 遍历每一个已知的点
	bg::for_each_point(
		bg_MultiPoint, [&](const BG_Point& p)
	{
		// 定义新的点
		BG_Point transformed_point;

		// 归一化处理
		bg::set<0>(transformed_point, floor((bg::get<0>(p) - my_Envelope.dXmin) / (my_Envelope.dXmax - my_Envelope.dXmin) * factor) / factor);
		bg::set<1>(transformed_point, floor((bg::get<1>(p) - my_Envelope.dYmin) / (my_Envelope.dYmax - my_Envelope.dYmin) * factor) / factor);

		// 新的点加入新的BG_MultiPoint
		result_MultiPoint.push_back(transformed_point);
	}
	);

	// 返回结果
	return result_MultiPoint;
}


/*******************************************************************************
* Normalize the existing BG_MultiPolygon based on the known range
* @param bg_Multipolygon the BG_MultiPolygon to be Normalized
* @param my_Envelope the known range
* @return the Normalized BG_MultiPolygon
*******************************************************************************/
BG_MultiPolygon CommonUtils::ReCalMultiPolygon(BG_MultiPolygon bg_Multipolygon, MY_ENVELOPE my_Envelope)
{
	BG_MultiPolygon result_Multipolygon;

	for (const auto& polygon : bg_Multipolygon) {
		BG_Polygon result_polygon = ReCalPolygon(polygon, my_Envelope);
		result_Multipolygon.push_back(result_polygon);
	}

	return result_Multipolygon;
}


/*******************************************************************************
* Convert BG_Polygon To MultiPoint
* @param bg_Polygon the BG_Polygon to be Converted
* @return the Converted MultiPoint
*******************************************************************************/
BG_MultiPoint CommonUtils::ConvertPolygonToMultiPoint(BG_Polygon bg_Polygon)
{
	// 定义BG_MultiPoint
	BG_MultiPoint result_MultiPoints;

	// 读取外环
	auto exterior_ring = bg::exterior_ring(bg_Polygon);

	// 遍历每一个已知外环的点
	bg::for_each_point
	(
		exterior_ring, [&](const BG_Point& p) {

		// 新的点加入新的外环
		result_MultiPoints.push_back(p);
	}
	);

	// 读取内环
	auto rings = bg::interior_rings(bg_Polygon);

	// 遍历所有内环
	for (std::size_t i = 0; i < bg::num_interior_rings(bg_Polygon); i++)
	{
		// 提取出第i个内环
		auto it = rings.begin();
		std::advance(it, i);

		// 如果还有内环
		if (it != rings.end())
		{
			// 遍历每一个已知内环的点
			bg::for_each_point(
				*it, [&](const BG_Point& p)
			{
				// 新的点加入新的内环
				result_MultiPoints.push_back(p);
			}
			);
		}
	}

	// 返回结果
	return result_MultiPoints;
}


/*******************************************************************************
* Convert MultiPolygon To MultiPoint
* @param bg_MultiPolygon the BG_MultiPolygon to be Converted
* @return the Converted MultiPoint
*******************************************************************************/
BG_MultiPoint CommonUtils::ConvertMultiPolygonToMultiPoint(BG_MultiPolygon bg_MultiPolygon)
{
	// 定义BG_MultiPoint
	BG_MultiPoint result_MultiPoints;

	for (const auto& polygon : bg_MultiPolygon) {
		BG_MultiPoint tmp_MultiPoints = ConvertPolygonToMultiPoint(polygon);

		for (const auto& point : tmp_MultiPoints)
		{
			bg::append(result_MultiPoints, point);
		}
	}

	return result_MultiPoints;
}


// 定义将Polygon从浮点型转化为整型的函数
void polyd2i(const BG_Polygon& poly, BG_Polygon_Int& polyi)
{
	double transform = 100000000.0;
	for (const auto& p : poly.outer()) {
		polyi.outer().emplace_back(BG_Point_Int(static_cast<long>(p.x() * transform), static_cast<long>(p.y() * transform)));
	}
	for (const auto& in : poly.inners()) {
		BG_Ring_Int ini;
		for (const auto& p : in) {
			ini.emplace_back(BG_Point_Int(static_cast<long>(p.x() * transform), static_cast<long>(p.y() * transform)));
		}
		polyi.inners().emplace_back(ini);
	}
	if (!bg::is_valid(polyi)) {
		bg::correct(polyi);
	}
}


// 定义将Polygon从整型转化为浮点型的函数
void polyi2d(const BG_Polygon_Int& polyi, BG_Polygon& poly)
{
	double transform = 100000000.0;
	for (const auto& p : polyi.outer()) {
		poly.outer().emplace_back(BG_Point(static_cast<double>(p.x()) / transform, static_cast<double>(p.y()) / transform));
	}
	for (const auto& in : polyi.inners()) {
		BG_Ring ini;
		for (const auto& p : in) {
			ini.emplace_back(BG_Point(static_cast<double>(p.x()) / transform, static_cast<double>(p.y()) / transform));
		}
		poly.inners().emplace_back(ini);
	}
	if (!bg::is_valid(poly)) {
		bg::correct(poly);
	}
}


/*******************************************************************************
 * Union two Polygon
 * @param bg_MultiPolygon MultiPolygon A
 * @param bg_Polygon Polygon B
 * @return the unioned polygon if successful
 * NULL BG_MultiPolygon if failed
*******************************************************************************/
BG_MultiPolygon CommonUtils::UnionPolygon(BG_MultiPolygon bg_MultiPolygon, BG_Polygon bg_Polygon)
{
	// 新建结果多边形
	BG_MultiPolygon UnionMultiPolygon;

	// 尝试直接合并多边形
	bg::union_(bg_MultiPolygon, bg_Polygon, UnionMultiPolygon);

	// 如果合并成功则直接返回合并结果
	if (UnionMultiPolygon.size() <= bg_MultiPolygon.size())
		return UnionMultiPolygon;

	// 新建临时存放结果的多边形
	BG_MultiPolygon_Int tmpi;
	BG_MultiPolygon_Int outsi;

	// 遍历所有多边形，转化为整型后再合并
	for (const auto& polyd : UnionMultiPolygon) {
		BG_Polygon_Int polyi;

		// 转化为整型
		polyd2i(polyd, polyi);

		// 合并
		bg::union_(outsi, polyi, tmpi);

		// 交换数据
		outsi.swap(tmpi);

		// 清空临时多边形
		bg::clear(tmpi);
	}

	// 清空结果多边形
	UnionMultiPolygon.clear();

	// 遍历所有多边形，转化为浮点型
	for (const auto& polyi : outsi) {
		BG_Polygon polyd;

		// 转化为浮点型
		polyi2d(polyi, polyd);

		//赋值给结果多边形
		UnionMultiPolygon.emplace_back(polyd);
	}

	// 返回结果多边形
	return UnionMultiPolygon;
}


/*******************************************************************************
 * Calculate the Perimeter after append new BG_Polygon to Original MultiPolygon
 * @param bg_MultiPolygon Original MultiPolygon
 * @param OriArea Original Area
 * @param OriCentorid Original Centroid
 * @param bg_Polygon input Polygon
 * @return new Centroid
*******************************************************************************/
BG_Point CommonUtils::CalCentroid(BG_MultiPolygon bg_MultiPolygon, double OriArea, BG_Point OriCentorid, BG_Polygon bg_Polygon)
{
	// 计算polygon面积
	double dPolyArea = bg::area(bg_Polygon);

	// 计算polygon重心
	BG_Point PolyCentroid;
	bg::centroid(bg_Polygon, PolyCentroid);

	// 计算新的重心的横纵坐标
	double NewCentroid_X = (bg::get<0>(OriCentorid) * OriArea + bg::get<0>(PolyCentroid) * dPolyArea) /
		(OriArea + dPolyArea);
	double NewCentroid_Y = (bg::get<1>(OriCentorid) * OriArea + bg::get<1>(PolyCentroid) * dPolyArea) /
		(OriArea + dPolyArea);

	// 返回重心坐标
	return BG_Point(NewCentroid_X, NewCentroid_Y);
}


/*******************************************************************************
 * Calculate the Perimeter of BG_Polygon
 * @param bg_Polygon polygon input
 * @return perimeter
*******************************************************************************/
double CommonUtils::CalPerimeter(BG_Polygon bg_Polygon)
{
	return bg::perimeter(bg_Polygon);
}


/*******************************************************************************
 * Calculate the Perimeter of BG_MultiPolygon
 * @param bg_MultiPolygon polygon input
 * @return perimeter
*******************************************************************************/
double CommonUtils::CalPerimeter(BG_MultiPolygon bg_MultiPolygon)
{
	// 初始化周长
	double dPerimeter = bg::perimeter(bg_MultiPolygon);

	// 返回周长计算结果
	return dPerimeter;
}


/*******************************************************************************
 * Calculate the Perimeter after append new BG_Polygon to Original MultiPolygon
 * @param bg_MultiPolygon Original MultiPolygon
 * @param bg_Polygon input Polygon
 * @return new perimeter
*******************************************************************************/
double CommonUtils::CalPerimeter(BG_MultiPolygon bg_MultiPolygon, BG_Polygon bg_Polygon)
{
	BG_MultiPolygon UnionPolygon = this->UnionPolygon(bg_MultiPolygon, bg_Polygon);

	// 计算周长
	double dPerimeter = bg::perimeter(UnionPolygon);

	// 返回周长计算结果
	return dPerimeter;
}


/*******************************************************************************
 * Calculate the Overlap Area between two Polyshape
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_Polygon the second Polyshape
 * @return the Overlap Area
 *******************************************************************************/
double CommonUtils::CalOverlapArea(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 创建多边形交叉结果
	BG_MultiPolygon output;

	// 求多边形交集
	bg::intersection(A_bg_Polygon, B_bg_Polygon, output);

	// 返回面积
	return bg::area(output);
}


/*******************************************************************************
 * Calculate the Overlap Area between two Polyshape
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_MultiPolygon the second Polyshape
 * @return the Overlap Area
 *******************************************************************************/
double CommonUtils::CalOverlapArea(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 初始化面积
	double dArea = 0.0;

	// 单独计算每一个多边形的面积并添加到总面积上
	for (const auto& polygon : B_bg_MultiPolygon) {
		dArea += CalOverlapArea(A_bg_Polygon, polygon);
	}

	return dArea;
}


/*******************************************************************************
 * Calculate the Overlap Area between two Polyshape
 * @param A_bg_MultiPolygon the first Polyshape
 * @param B_bg_MultiPolygon the second Polyshape
 * @return the Overlap Area
 *******************************************************************************/
double CommonUtils::CalOverlapArea(BG_MultiPolygon A_bg_MultiPolygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 初始化面积
	double dArea = 0.0;

	// 单独计算每一个多边形的面积并添加到总面积上
	for (const auto& polygonA : A_bg_MultiPolygon) {
		for (const auto& polygonB : B_bg_MultiPolygon) {
			dArea += CalOverlapArea(polygonA, polygonB);
		}
	}

	return dArea;
}


/*******************************************************************************
 * Calculate the Overlap Area between two Polyshape
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_Polygon the second Polyshape
 * @param OriOverlapArea the Original overlap area
 * @return the Overlap Area
 *******************************************************************************/
double CommonUtils::CalOverlapArea(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon, double OriOverlapArea)
{
	// 创建多边形交叉结果
	BG_MultiPolygon output;

	// 求多边形交集
	bg::intersection(A_bg_Polygon, B_bg_Polygon, output);

	// 返回面积
	return bg::area(output) + OriOverlapArea;
}


/*******************************************************************************
 * Calculate the Symmetric Difference Area between two Polyshape
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_Polygon the second Polyshape
 * @return the Symmetric Difference Area
 *******************************************************************************/
double CommonUtils::CalSymDiffArea(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 创建多边形交叉结果
	BG_MultiPolygon output;

	// 求多边形交集
	bg::sym_difference(A_bg_Polygon, B_bg_Polygon, output);

	// 返回面积
	return bg::area(output);
}


/*******************************************************************************
 * Calculate the Symmetric Difference Area between two Polyshape
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_MultiPolygon the second Polyshape
 * @return the Symmetric Difference Area
 *******************************************************************************/
double CommonUtils::CalSymDiffArea(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 创建多边形交叉结果
	BG_MultiPolygon output;

	// 求多边形交集
	bg::sym_difference(A_bg_Polygon, B_bg_MultiPolygon, output);

	// 返回面积
	return bg::area(output);
}


/*******************************************************************************
 * Calculate the Symmetric Difference Area between three Polyshape
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_Ori_MultiPolygon the second Polyshape
 * @param B_bg_new_Polygon the third Polyshape
 * @return the Symmetric Difference Area
 *******************************************************************************/
double CommonUtils::CalSymDiffArea(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_Ori_MultiPolygon, BG_Polygon B_bg_new_Polygon)
{
	// 计算多边形交集
	BG_MultiPolygon bg_UnionResult = B_bg_Ori_MultiPolygon;
	bg_UnionResult.push_back(B_bg_new_Polygon);

	// 创建多边形交叉结果
	BG_MultiPolygon output;

	// 求多边形交集
	bg::sym_difference(A_bg_Polygon, bg_UnionResult, output);

	// 返回面积
	return bg::area(output);
}


/*******************************************************************************
 * Calculate the diagonal distance of the envelope of the intersection of two polygons
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_Polygon the second Polyshape
 * @return the Distance
 *******************************************************************************/
double CommonUtils::CalUnionEnveDistance(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 计算多边形交集
	BG_MultiPolygon bg_UnionResult;
	bg_UnionResult.clear();
	bg_UnionResult.push_back(A_bg_Polygon);
	bg_UnionResult.push_back(B_bg_Polygon);

	// 计算交集多边形的Envelope
	BG_Box bg_Envelope;
	bg::envelope(bg_UnionResult, bg_Envelope);

	// 计算对角线距离
	return CalDistance(
		bg::get<bg::min_corner, 0>(bg_Envelope), bg::get<bg::min_corner, 1>(bg_Envelope),
		bg::get<bg::max_corner, 0>(bg_Envelope), bg::get<bg::max_corner, 1>(bg_Envelope));
}


/*******************************************************************************
 * Calculate the diagonal distance of the envelope of the intersection of two polygons
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_MultiPolygon the second Polyshape
 * @return the Distance
 *******************************************************************************/
double CommonUtils::CalUnionEnveDistance(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 计算多边形交集
	BG_MultiPolygon bg_UnionResult = B_bg_MultiPolygon;
	bg_UnionResult.push_back(A_bg_Polygon);

	// 计算交集多边形的Envelope
	BG_Box bg_Envelope;
	bg::envelope(bg_UnionResult, bg_Envelope);

	// 计算对角线距离
	return CalDistance(
		bg::get<bg::min_corner, 0>(bg_Envelope), bg::get<bg::min_corner, 1>(bg_Envelope),
		bg::get<bg::max_corner, 0>(bg_Envelope), bg::get<bg::max_corner, 1>(bg_Envelope));
}


/*******************************************************************************
 * Calculate the diagonal distance of the envelope of the intersection of three polygons
 * @param A_bg_Polygon the first Polyshape
 * @param B_bg_Ori_MultiPolygon the second Polyshape
 * @param B_bg_new_Polygon the third Polyshape
 * @return the Distance
 *******************************************************************************/
double CommonUtils::CalUnionEnveDistance(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_Ori_MultiPolygon, BG_Polygon B_bg_new_Polygon)
{
	// 计算多边形交集
	BG_MultiPolygon bg_UnionResult = B_bg_Ori_MultiPolygon;
	bg_UnionResult.push_back(A_bg_Polygon);
	bg_UnionResult.push_back(B_bg_new_Polygon);

	// 计算交集多边形的Envelope
	BG_Box bg_Envelope;
	bg::envelope(bg_UnionResult, bg_Envelope);

	// 计算对角线距离
	return CalDistance(
		bg::get<bg::min_corner, 0>(bg_Envelope), bg::get<bg::min_corner, 1>(bg_Envelope),
		bg::get<bg::max_corner, 0>(bg_Envelope), bg::get<bg::max_corner, 1>(bg_Envelope));
}


/*******************************************************************************
 * Calculate the Hausdorff Distance between two Polyshape
 * @param A_bg_MultiPoint the first Polyshape
 * @param B_bg_MultiPoint the second Polyshape
 * @return the Hausdorff Distance
 *******************************************************************************/
double CommonUtils::CalHausdorffDistance(BG_MultiPoint A_bg_MultiPoint, BG_MultiPoint B_bg_MultiPoint)
{
	// 计算hausdorff距离
	double distance = bg::discrete_hausdorff_distance(A_bg_MultiPoint, B_bg_MultiPoint);

	return distance;
}


/*******************************************************************************
 * Calculate the Area of Envelope
 * @param my_Envelope the Envelope
 * @return the Area of Envelope
 *******************************************************************************/
double CommonUtils::CalAreaFromEnvelope(MY_ENVELOPE my_Envelope)
{
	// 用绝对值防止出现负数
	return abs((my_Envelope.dXmax - my_Envelope.dXmin) * (my_Envelope.dYmax - my_Envelope.dYmin));
}
