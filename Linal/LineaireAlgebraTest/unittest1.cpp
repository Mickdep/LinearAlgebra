#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <memory>
#include "../LineaireAlgebra/CMatrix3d.h"
#include "../LineaireAlgebra/CVector3d.h"
#include "../LineaireAlgebra/GameObject.h"
#include "../LineaireAlgebra/MatrixFactory.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LineaireAlgebraTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TransformTest)
		{
			//Arrange
			auto translation_matrix = MatrixFactory::get_translation_matrix_3d(10, 10, 10);
			auto game_object = std::make_shared<GameObject>();
			game_object->vectors.push_back(CVector3d(0, 0, 0));

			//Act
			game_object->transform(translation_matrix);

			//Assert
			Assert::AreEqual(10.0, game_object->vectors[0].x);
			Assert::AreEqual(10.0, game_object->vectors[0].y);
			Assert::AreEqual(10.0, game_object->vectors[0].z);
		}

		TEST_METHOD(MatrixMultiplicationTest) {
			//Arrange
			auto translation_matrix = MatrixFactory::get_translation_matrix_3d(10, 10, 10);
			auto translation_matrix_2 = MatrixFactory::get_translation_matrix_3d(5, 5, 5);
			auto rotation_matrix = MatrixFactory::get_rotation_matrix_3d_x_axis(360);

			auto transformation_matrix = *translation_matrix * (*translation_matrix_2 * rotation_matrix);

			auto game_object = std::make_shared<GameObject>();
			game_object->vectors.push_back(CVector3d(0, 0, 0));

			//Act
			game_object->transform(transformation_matrix);

			//Assert

			Assert::AreEqual(15.0, game_object->vectors[0].x);
			Assert::AreEqual(15.0, game_object->vectors[0].y);
			Assert::AreEqual(15.0, game_object->vectors[0].z);
		}

		TEST_METHOD(CrossProductTest) {
			//Arrange
			auto vector_1 = std::make_shared<CVector3d>(1, 2, 3);
			auto vector_2 = std::make_shared<CVector3d>(3, 4, 5);

			//Act
			auto cross_product = vector_1->get_out_product(vector_2);

			//Assert
			Assert::AreEqual(-2.0, cross_product->x);
			Assert::AreEqual(4.0, cross_product->y);
			Assert::AreEqual(-2.0, cross_product->z);
		}

		TEST_METHOD(DotProductTest) {
			//Arrange
			auto vector_1 = std::make_shared<CVector3d>(1, 2, 3);
			auto vector_2 = std::make_shared<CVector3d>(1, 5, 7);

			//Act
			auto dot_product = vector_1->get_in_product(vector_2);

			//Assert
			Assert::AreEqual(32.0, dot_product);
		}

		TEST_METHOD(NormalizationTest) {
			//Arrange
			auto vector = std::make_shared<CVector3d>(0, 0, -500);
			
			//Act
			auto normalized_vector = vector->normalize();

			//Assert
			Assert::AreEqual(0.0, normalized_vector->x);
			Assert::AreEqual(0.0, normalized_vector->y);
			Assert::AreEqual(-1.0, normalized_vector->z);
		}

	};
}