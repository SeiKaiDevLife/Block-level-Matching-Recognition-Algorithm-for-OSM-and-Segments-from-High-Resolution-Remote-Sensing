// SeiKai @ Second Institute Of Oceanography, MNR

#pragma once
#pragma execution_character_set("utf-8")

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

// Qt相关文件
#include <QtWidgets/QWidget>
#include <QString>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QThread>
#include <QtConcurrent/QtConcurrentRun>
#include <QCloseEvent>

// GDAL相关文件
#include "gdal_priv.h"
#include "ogr_api.h"
#include "ogrsf_frmts.h"
#include "ogr_spatialref.h"

// boost相关文件
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/centroid.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/is_valid.hpp>
#include <boost/geometry/algorithms/num_geometries.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/discrete_hausdorff_distance.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/polygon/polygon.hpp>

// 命名空间
using namespace std;
namespace bg = boost::geometry;

// 定义基于boost的各类结构
typedef bg::model::d2::point_xy<double> BG_Point;
typedef bg::model::d2::point_xy<int> BG_Point_Int;
typedef bg::model::ring<BG_Point> BG_Ring;
typedef bg::model::ring<BG_Point_Int> BG_Ring_Int;
typedef bg::model::polygon<BG_Point> BG_Polygon;
typedef bg::model::polygon<BG_Point_Int> BG_Polygon_Int;
typedef bg::model::box<BG_Point> BG_Box;
typedef bg::model::linestring<BG_Point> BG_Linestring;
typedef bg::model::multi_point<BG_Point> BG_MultiPoint;
typedef bg::model::multi_polygon<BG_Polygon> BG_MultiPolygon;
typedef bg::model::multi_polygon<BG_Polygon_Int> BG_MultiPolygon_Int;

// 用于Boost库中的元素平移的结构
struct translate_strategy
{
	translate_strategy(const BG_Point& displacement)
		: m_displacement(displacement)
	{}

	template <typename Point>
	void apply(Point& pt) const
	{
		pt.x() += m_displacement.x();
		pt.y() += m_displacement.y();
	}

private:
	BG_Point m_displacement;
};

// 定义最外包络圈的数据结构
typedef struct tag_MY_ENVELOPE
{
	double dXmin, dXmax, dYmin, dYmax;	// 定义最外包络圈的范围

	// 构造函数
	tag_MY_ENVELOPE() : dXmin(0), dXmax(0), dYmin(0), dYmax(0) {}
}MY_ENVELOPE;
