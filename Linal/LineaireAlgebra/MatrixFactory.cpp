#include "stdafx.h"
#include "MatrixFactory.h"

MatrixFactory::MatrixFactory()
{
}


MatrixFactory::~MatrixFactory()
{
}

//======================================== 3D MATRICES ========================================

std::shared_ptr<CMatrix3d> MatrixFactory::get_rotation_matrix_3d_x_axis(const double rotation_angle)
{
	const int width = 4;
	const int height = 4;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();

	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	//1st row
	const auto radians = (rotation_angle * 3.1415926535897) / 180;
	matrix->values[0][0] = 1;
	matrix->values[0][1] = 0;
	matrix->values[0][2] = 0;
	matrix->values[0][3] = 0;

	//2nd row
	matrix->values[1][0] = 0;
	matrix->values[1][1] = cos(radians);
	matrix->values[1][2] = -sin(radians);
	matrix->values[1][3] = 0;

	//3rd row
	matrix->values[2][0] = 0;
	matrix->values[2][1] = sin(radians);
	matrix->values[2][2] = cos(radians);
	matrix->values[2][3] = 0;

	//4th row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = 0;
	matrix->values[3][3] = 1;

	return matrix;
}

std::shared_ptr<CMatrix3d> MatrixFactory::get_rotation_matrix_3d_y_axis(const double rotation_angle)
{
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	const int width = 4;
	const int height = 4;

	matrix->values.resize(height);
	for (auto i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	//1st row
	matrix->values[0][0] = cos(rotation_angle);
	matrix->values[0][1] = 0;
	matrix->values[0][2] = sin(rotation_angle);
	matrix->values[0][3] = 0;

	//2nd row
	matrix->values[1][0] = 0;
	matrix->values[1][1] = 1;
	matrix->values[1][2] = 0;
	matrix->values[1][3] = 0;

	//3rd row
	matrix->values[2][0] = -sin(rotation_angle);
	matrix->values[2][1] = 0;
	matrix->values[2][2] = cos(rotation_angle);
	matrix->values[2][3] = 0;

	//4th row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = 0;
	matrix->values[3][3] = 1;

	return matrix;
}

//NOTE: This rotation_angle is in radians already, so no need to convert it to radians ;).
//If you try to rotate this with degrees instead of radians you'll get a fucked up rotation speed.
std::shared_ptr<CMatrix3d> MatrixFactory::get_rotation_matrix_3d_z_axis(const double rotation_angle)
{
	const int width = 4;
	const int height = 4;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	//1st row
	matrix->values[0][0] = cos(rotation_angle);
	matrix->values[0][1] = sin(rotation_angle);
	matrix->values[0][2] = 0;
	matrix->values[0][3] = 0;

	//2nd row
	matrix->values[1][0] = -sin(rotation_angle);
	matrix->values[1][1] = cos(rotation_angle);
	matrix->values[1][2] = 0;
	matrix->values[1][3] = 0;

	//3rd row
	matrix->values[2][0] = 0;
	matrix->values[2][1] = 0;
	matrix->values[2][2] = 1;
	matrix->values[2][3] = 0;

	//4th row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = 0;
	matrix->values[3][3] = 1;

	return matrix;
}

std::shared_ptr<CMatrix3d> MatrixFactory::get_translation_matrix_3d(const double x_translate, const double y_translate, const double z_translate)
{
	const int width = 4;
	const int height = 4;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	//1st row
	matrix->values[0][0] = 1;
	matrix->values[0][1] = 0;
	matrix->values[0][2] = 0;
	matrix->values[0][3] = x_translate;

	//2nd row
	matrix->values[1][0] = 0;
	matrix->values[1][1] = 1;
	matrix->values[1][2] = 0;
	matrix->values[1][3] = y_translate;

	//3rd row
	matrix->values[2][0] = 0;
	matrix->values[2][1] = 0;
	matrix->values[2][2] = 1;
	matrix->values[2][3] = z_translate;

	//3rd row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = 0;
	matrix->values[3][3] = 1;

	return matrix;
}

std::shared_ptr<CMatrix3d> MatrixFactory::get_scale_matrix_3d(const double x_scale, const double y_scale, const double z_scale)
{
	const int width = 4;
	const int height = 4;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	//1st row
	matrix->values[0][0] = x_scale;
	matrix->values[0][1] = 0;
	matrix->values[0][2] = 0;
	matrix->values[0][3] = 0;

	//2nd row
	matrix->values[1][0] = 0;
	matrix->values[1][1] = y_scale;
	matrix->values[1][2] = 0;
	matrix->values[1][3] = 0;

	//3rd row
	matrix->values[2][0] = 0;
	matrix->values[2][1] = 0;
	matrix->values[2][2] = z_scale;
	matrix->values[2][3] = 0;

	//4th row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = 0;
	matrix->values[3][3] = 1;

	return matrix;
}

std::shared_ptr<CMatrix3d> MatrixFactory::get_perpendicular_axis(const double x, const double y, const double z)
{
	const int width = 4;
	const int height = 1;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	matrix->values[0][0] = x;
	matrix->values[0][1] = y;
	matrix->values[0][2] = z;
	matrix->values[0][3] = 1;

	return matrix;
}

std::shared_ptr<CMatrix3d> MatrixFactory::get_camera_matrix_3d(const std::shared_ptr<CVector3d> eye,
	const std::shared_ptr<CVector3d> look_at, const std::shared_ptr<CVector3d> up)
{
	const int width = 4;
	const int height = 4;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	const std::shared_ptr<CVector3d> eye_minus_lookat = std::make_shared<CVector3d>(eye->x - look_at->x, eye->y - look_at->y, eye->z - look_at->z);
	const auto z = eye_minus_lookat->normalize();
	auto y = up->normalize();
	const auto x = y->get_out_product(z)->normalize();
	y = z->get_out_product(x)->normalize();

	//1st row
	matrix->values[0][0] = x->x;
	matrix->values[0][1] = x->y;
	matrix->values[0][2] = x->z;
	matrix->values[0][3] = -x->get_in_product(eye);

	//2nd row
	matrix->values[1][0] = y->x;
	matrix->values[1][1] = y->y;
	matrix->values[1][2] = y->z;
	matrix->values[1][3] = -y->get_in_product(eye);

	//3rd row
	matrix->values[2][0] = z->x;
	matrix->values[2][1] = z->y;
	matrix->values[2][2] = z->z;
	matrix->values[2][3] = -z->get_in_product(eye);

	//4th row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = 0;
	matrix->values[3][3] = 1;

	return matrix;
}

std::shared_ptr<CMatrix3d> MatrixFactory::get_perspective_projection_matrix(const double near, const double far,
                                                                            const double fieldOfView)
{
	//Convert the fieldOfView angle to radians
	const auto radians = (fieldOfView * 3.1415926535897) / 180;
	const auto scale = near * tan(radians * 0.5);

	const int width = 4;
	const int height = 4;
	std::shared_ptr<CMatrix3d> matrix = std::make_shared<CMatrix3d>();
	matrix->values.resize(height);
	for (int i = 0; i < height; ++i)
	{
		matrix->values[i].resize(width);
	}

	//1st row
	matrix->values[0][0] = scale;
	matrix->values[0][1] = 0;
	matrix->values[0][2] = 0;
	matrix->values[0][3] = 0;

	//2nd row
	matrix->values[1][0] = 0;
	matrix->values[1][1] = scale;
	matrix->values[1][2] = 0;
	matrix->values[1][3] = 0;

	//3rd row
	matrix->values[2][0] = 0;
	matrix->values[2][1] = 0;
	matrix->values[2][2] = -far/(far-near);
	matrix->values[2][3] = -1;

	//4th row
	matrix->values[3][0] = 0;
	matrix->values[3][1] = 0;
	matrix->values[3][2] = (-far * near) / (far-near);
	matrix->values[3][3] = 0;

	return matrix;
}

