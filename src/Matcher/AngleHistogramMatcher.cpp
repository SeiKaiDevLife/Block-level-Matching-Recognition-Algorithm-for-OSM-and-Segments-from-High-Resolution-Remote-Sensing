// SeiKai @ Second Institute Of Oceanography, MNR

#pragma execution_character_set("utf-8")

#include "AngleHistogramMatcher.h"

/*******************************************************************************
 * Calculate the match Score of AngleHistogramMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_Polygon polygon B
 * @return match Score
 *******************************************************************************/
double AngleHistogramMatcher::CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_Polygon B_bg_Polygon)
{
	// 创建两个角直方图
	AngleHistogram A_AngleHis = AngleHistogram(binCount);
	AngleHistogram B_AngleHis = AngleHistogram(binCount);

	// 初始化角直方图
	A_AngleHis.InitHistogram();
	B_AngleHis.InitHistogram();

	// 计算角直方图
	A_AngleHis.CalAngleHis(A_bg_Polygon, CommonUtils().CalPerimeter(A_bg_Polygon));
	B_AngleHis.CalAngleHis(B_bg_Polygon, CommonUtils().CalPerimeter(B_bg_Polygon));

	// 计算匹配得分并返回
	return CalculateHisScore(A_AngleHis, B_AngleHis);
}


/*******************************************************************************
 * Calculate the match Score of AngleHistogramMatcher
 * @param A_bg_Polygon polygon A
 * @param B_bg_MultiPolygon multipolygon B
 * @return match Score
 *******************************************************************************/
double AngleHistogramMatcher::CalculateMatchScore(BG_Polygon A_bg_Polygon, BG_MultiPolygon B_bg_MultiPolygon)
{
	// 创建两个角直方图
	AngleHistogram A_AngleHis = AngleHistogram(binCount);
	AngleHistogram B_AngleHis = AngleHistogram(binCount);

	// 初始化角直方图
	A_AngleHis.InitHistogram();
	B_AngleHis.InitHistogram();

	// 计算角直方图
	A_AngleHis.CalAngleHis(A_bg_Polygon, CommonUtils().CalPerimeter(A_bg_Polygon));
	B_AngleHis.CalAngleHis(B_bg_MultiPolygon, CommonUtils().CalPerimeter(B_bg_MultiPolygon));

	// 计算匹配得分并返回
	return CalculateHisScore(A_AngleHis, B_AngleHis);
}


/*******************************************************************************
 * Calculate the match Score of AngleHistogramMatcher
 * @param A_bg_Polygon polygon A
 * @param A_AngleHis the AngleHis of polygon A
 * @param B_bg_Ori_MultiPolygon Ori multipolygon B
 * @param B_bg_New_Polygon New polygon B
 * @return match Score
 *******************************************************************************/
double AngleHistogramMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon,
	BG_MultiPolygon B_bg_Ori_MultiPolygon,
	BG_Polygon B_bg_New_Polygon)
{
	// 创建两个角直方图
	AngleHistogram A_AngleHis = AngleHistogram(binCount);
	AngleHistogram B_AngleHis = AngleHistogram(binCount);

	// 初始化角直方图
	A_AngleHis.InitHistogram();
	B_AngleHis.InitHistogram();

	// 添加新的多边形
	BG_MultiPolygon B_bg_MultiPolygon = B_bg_Ori_MultiPolygon;
	B_bg_MultiPolygon.push_back(B_bg_New_Polygon);

	// 计算角直方图
	A_AngleHis.CalAngleHis(A_bg_Polygon, CommonUtils().CalPerimeter(A_bg_Polygon));
	B_AngleHis.CalAngleHis(B_bg_MultiPolygon, CommonUtils().CalPerimeter(B_bg_Ori_MultiPolygon, B_bg_New_Polygon));

	double a = CalculateHisScore(A_AngleHis, B_AngleHis);

	// 计算匹配得分并返回
	return CalculateHisScore(A_AngleHis, B_AngleHis);
}


/*******************************************************************************
 * Calculate the match Score of AngleHistogramMatcher
 * @param A_bg_Polygon polygon A
 * @param A_AngleHis the AngleHis of polygon A
 * @param B_bg_Ori_MultiPolygon Ori multipolygon B
 * @param B_bg_New_Polygon New polygon B
 * @return match Score
 *******************************************************************************/
double AngleHistogramMatcher::CalculateMatchScore(
	BG_Polygon A_bg_Polygon, AngleHistogram A_AngleHis,
	BG_MultiPolygon B_bg_Ori_MultiPolygon,
	BG_Polygon B_bg_New_Polygon)
{
	// 创建两个角直方图
	AngleHistogram B_AngleHis = AngleHistogram(binCount);

	// 初始化角直方图
	B_AngleHis.InitHistogram();

	// 添加新的多边形
	BG_MultiPolygon B_bg_MultiPolygon = B_bg_Ori_MultiPolygon;
	B_bg_MultiPolygon.push_back(B_bg_New_Polygon);

	// 计算角直方图
	B_AngleHis.CalAngleHis(B_bg_MultiPolygon, CommonUtils().CalPerimeter(B_bg_Ori_MultiPolygon, B_bg_New_Polygon));

	double a = CalculateHisScore(A_AngleHis, B_AngleHis);

	// 计算匹配得分并返回
	return CalculateHisScore(A_AngleHis, B_AngleHis);
}


/*******************************************************************************
 * Calculate the matching score between two angle histograms
 * @param A_AngleHis angle histograms to be matched
 * @param B_AngleHis angle histograms to be matched
 * @return the matching score
 *******************************************************************************/
double AngleHistogramMatcher::CalculateHisScore(AngleHistogram A_AngleHis, AngleHistogram B_AngleHis)
{
	// 计算两个直方图分别的分数和差分分数，并计算匹配得分
	return 1.00 - (CalHisSymDiffScore(A_AngleHis, B_AngleHis) /
		(GetHisTotalScore(A_AngleHis) + GetHisTotalScore(B_AngleHis)));
}


/*******************************************************************************
 * Calculate the total score from a angle histograms
 * @param AngleHis angle histograms to be calculated
 * @return the total score
 *******************************************************************************/
double AngleHistogramMatcher::GetHisTotalScore(AngleHistogram AngleHis)
{
	// 初始化总得分
	double dTotalScore = 0;

	// 每一个索引值下的分数相加
	for (int ii = 0; ii < AngleHis.GetbinCount(); ii++)
	{
		dTotalScore += AngleHis.GetbinValue(ii);
	}

	// 返回最终得分
	return dTotalScore;
}


/*******************************************************************************
 * Calculate the symmetric difference score between two angle histograms
 * @param A_AngleHis angle histograms to be matched
 * @param B_AngleHis angle histograms to be matched
 * @return the symmetric difference score
 *******************************************************************************/
double AngleHistogramMatcher::CalHisSymDiffScore(AngleHistogram A_AngleHis, AngleHistogram B_AngleHis)
{
	// 初始化差分得分
	double dSymDiffScore = 0;

	// 两个直方图索引数量一定一致
	assert(A_AngleHis.GetbinCount() == B_AngleHis.GetbinCount());

	// 每一个索引下的差分分数相加
	for (int ii = 0; ii < A_AngleHis.GetbinCount(); ii++)
	{
		dSymDiffScore += abs(A_AngleHis.GetbinValue(ii) - B_AngleHis.GetbinValue(ii));
	}

	// 返回最终得分
	return dSymDiffScore;
}


/*******************************************************************************
 * Set the BinCount
 * @return 1
 *******************************************************************************/
int AngleHistogramMatcher::SetBinCount(int _binCount)
{
	// 设置角直方图列数
	this->binCount = _binCount;

	return 1;
}


/*******************************************************************************
 * Initialize the angle histogram
 * @return 1 if successfully Initialized
 * 0 if failed
 *******************************************************************************/
int AngleHistogram::InitHistogram()
{
	// 清空数据
	// if (AngleHis) delete[] AngleHis;

	// 申请空间
	AngleHis = new double[binCount];

	// 确认空间申请成功
	if (!AngleHis) return 0;

	// 初始化数据
	for (int ii = 0; ii < binCount; ii++) AngleHis[ii] = 0.0;

	return 1;
}


/*******************************************************************************
 * Set the BinCount
 * @return 1
 *******************************************************************************/
int AngleHistogram::SetBinCount(int _binCount)
{
	// 设置角直方图列数
	this->binCount = _binCount;

	return 1;
}


/*******************************************************************************
 * Calculate the angle histogram of polygon
 * @param bg_Polygon the polygon to be calculated
 * @param _dPerimeter the perimeter of polygon
 * @return 1
*******************************************************************************/
int AngleHistogram::CalAngleHis(BG_Polygon bg_Polygon, double _dPerimeter)
{
	// 计算周长
	dPerimeter = _dPerimeter;

	// 获取外环
	const auto& OuterRing = bg_Polygon.outer();

	// 计算外环的角直方图
	for (size_t ii = 0; ii < OuterRing.size(); ii++)
	{
		// 读取第ii条边的两个顶点
		const auto& current_Pt = OuterRing[ii];
		const auto& next_Pt = OuterRing[(ii + 1) % OuterRing.size()];

		// 计算边长
		double EdgeLength = CommonUtils().CalDistance(
			bg::get<0>(current_Pt), bg::get<1>(current_Pt),
			bg::get<0>(next_Pt), bg::get<1>(next_Pt)) / dPerimeter;

		// 计算角度
		double EdgeAngle = CommonUtils().CalAngle(
			bg::get<0>(current_Pt), bg::get<1>(current_Pt),
			bg::get<0>(next_Pt), bg::get<1>(next_Pt));

		// 加入角直方图
		AddHisValue(EdgeAngle, EdgeLength);
	}

	// 遍历内环
	for (int ii = 0; ii < bg::num_interior_rings(bg_Polygon); ii++)
	{
		// 获取内环
		const auto& InnerRing = bg_Polygon.inners()[ii];

		// 计算内环的角直方图
		for (int jj = 0; jj < InnerRing.size(); jj++)
		{
			// 读取第jj条边的两个顶点
			const auto& current_Pt = InnerRing[jj];
			const auto& next_Pt = InnerRing[(jj + 1) % InnerRing.size()];

			// 计算边长
			double EdgeLength = CommonUtils().CalDistance(
				bg::get<0>(current_Pt), bg::get<1>(current_Pt),
				bg::get<0>(next_Pt), bg::get<1>(next_Pt)) / dPerimeter;

			// 计算角度
			double EdgeAngle = CommonUtils().CalAngle(
				bg::get<0>(current_Pt), bg::get<1>(current_Pt),
				bg::get<0>(next_Pt), bg::get<1>(next_Pt));

			// 加入角直方图
			AddHisValue(EdgeAngle, EdgeLength);
		}
	}

	return 1;
}


/*******************************************************************************
 * Calculate the angle histogram of multipolygon
 * @param bg_MultiPolygon the multipolygon to be calculated
 * @param _dPerimeter the perimeter of multipolygon
 * @return 1
*******************************************************************************/
int AngleHistogram::CalAngleHis(BG_MultiPolygon bg_MultiPolygon, double _dPerimeter)
{
	// 计算周长
	dPerimeter = _dPerimeter;

	for (const auto& polygon : bg_MultiPolygon) {
		// 获取外环
		const auto& OuterRing = polygon.outer();

		// 计算外环的角直方图
		for (size_t ii = 0; ii < OuterRing.size(); ii++)
		{
			// 读取第ii条边的两个顶点
			const auto& current_Pt = OuterRing[ii];
			const auto& next_Pt = OuterRing[(ii + 1) % OuterRing.size()];

			// 计算边长
			double EdgeLength = CommonUtils().CalDistance(
				bg::get<0>(current_Pt), bg::get<1>(current_Pt),
				bg::get<0>(next_Pt), bg::get<1>(next_Pt)) / dPerimeter;

			// 计算角度
			double EdgeAngle = CommonUtils().CalAngle(
				bg::get<0>(current_Pt), bg::get<1>(current_Pt),
				bg::get<0>(next_Pt), bg::get<1>(next_Pt));

			// 加入角直方图
			AddHisValue(EdgeAngle, EdgeLength);
		}

		// 遍历内环
		for (int ii = 0; ii < bg::num_interior_rings(polygon); ii++)
		{
			// 获取内环
			const auto& InnerRing = polygon.inners()[ii];

			// 计算内环的角直方图
			for (int jj = 0; jj < InnerRing.size(); jj++)
			{
				// 读取第jj条边的两个顶点
				const auto& current_Pt = InnerRing[jj];
				const auto& next_Pt = InnerRing[(jj + 1) % InnerRing.size()];

				// 计算边长
				double EdgeLength = CommonUtils().CalDistance(
					bg::get<0>(current_Pt), bg::get<1>(current_Pt),
					bg::get<0>(next_Pt), bg::get<1>(next_Pt)) / dPerimeter;

				// 计算角度
				double EdgeAngle = CommonUtils().CalAngle(
					bg::get<0>(current_Pt), bg::get<1>(current_Pt),
					bg::get<0>(next_Pt), bg::get<1>(next_Pt));

				// 加入角直方图
				AddHisValue(EdgeAngle, EdgeLength);
			}
		}
	}

	// 遍历所有多边形组合，寻找公共边从角直方图中减去
	for (auto it1 = bg_MultiPolygon.begin(); it1 != bg_MultiPolygon.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != bg_MultiPolygon.end(); ++it2) {

			// 如果两个多边形相邻
			if (bg::touches(*it1, *it2)) {

				// 提取公共边
				BG_MultiPoint intersection;
				bg::intersection(*it1, *it2, intersection);

				// 如果存在公共边
				if (!intersection.empty()) {

					// 按照顺序计算每两个点之间的距离，添加到公共边长度上
					for (size_t i = 1; i < intersection.size(); ++i)
					{
						// 计算边长
						double EdgeLength = CommonUtils().CalDistance(
							bg::get<0>(intersection[i - 1]), bg::get<1>(intersection[i - 1]),
							bg::get<0>(intersection[i]), bg::get<1>(intersection[i])) / dPerimeter;

						// 计算角度
						double EdgeAngle = CommonUtils().CalAngle(
							bg::get<0>(intersection[i - 1]), bg::get<1>(intersection[i - 1]),
							bg::get<0>(intersection[i]), bg::get<1>(intersection[i]));

						// 从角直方图中减去重合部分
						SubHisValue(EdgeAngle, EdgeLength * 2);
					}
				}
			}
		}
	}

	return 1;
}


/*******************************************************************************
 * Add values to the angle histogram
 * @return 1
 *******************************************************************************/
int AngleHistogram::AddHisValue(double HisAngleKey, double HisValue)
{
	// 将弧度转化为角度
	// 计算每一个bin的角度数值
	// 两个数值相除，取整数部分就是对应的key值
	int index = static_cast<int>((HisAngleKey / M_PI * 180) / (180.0 / binCount));

	// 防止M_PI宏定义小数点误差带来的索引溢出
	if (index >= binCount) index = binCount - 1;

	AngleHis[index] += HisValue;

	return 1;
}


/*******************************************************************************
 * Sub values to the angle histogram
 * @return 1
 *******************************************************************************/
int AngleHistogram::SubHisValue(double HisAngleKey, double HisValue)
{
	// 将弧度转化为角度
	// 计算每一个bin的角度数值
	// 两个数值相除，取整数部分就是对应的key值
	int index = static_cast<int>((HisAngleKey / M_PI * 180) / (180.0 / binCount));

	// 防止M_PI宏定义小数点误差带来的索引溢出
	if (index >= binCount) index = binCount - 1;

	AngleHis[index] -= HisValue;

	return 1;
}


/*******************************************************************************
 * get binCount
 * @return binCount
 *******************************************************************************/
int AngleHistogram::GetbinCount()
{
	// 获取binCount数值
	return binCount;
}


/*******************************************************************************
 * Get the value at a certain index in a histogram
 * @param binKey the index
 * @return the value at that index
 *******************************************************************************/
double AngleHistogram::GetbinValue(int binKey)
{
	// 返回该索引对应的直方图数值
	return AngleHis[binKey];
}
