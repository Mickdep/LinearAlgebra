#pragma once
#include <vector>
#include <memory>
#include "CVector3d.h"
#include "CMatrix3d.h"

static class MatrixFactory
{
public:
	MatrixFactory();
	~MatrixFactory();

	static std::shared_ptr<CMatrix3d> get_rotation_matrix_3d_x_axis(double rotation_angle);
	static std::shared_ptr<CMatrix3d> get_rotation_matrix_3d_y_axis(double rotation_angle);
	static std::shared_ptr<CMatrix3d> get_rotation_matrix_3d_z_axis(double rotation_angle);
	static std::shared_ptr<CMatrix3d> get_translation_matrix_3d(double x_translate, double y_translate, double z_translate);
	static std::shared_ptr<CMatrix3d> get_scale_matrix_3d(double x_scale, double y_scale, double z_scale);
	static std::shared_ptr<CMatrix3d> get_perpendicular_axis(double x, double y, double z);

	static std::shared_ptr<CMatrix3d> get_camera_matrix_3d(std::shared_ptr<CVector3d> eye, std::shared_ptr<CVector3d> look_at, std::shared_ptr<CVector3d> up);
	static std::shared_ptr<CMatrix3d> get_perspective_projection_matrix(double near, double far, double fieldOfView);
};

