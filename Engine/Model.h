#pragma once
#include <filesystem>

#include "drawable.h"

namespace Engine
{
	class Model : public drawable
	{
	private:
		static std::vector<float> importModel(std::filesystem::path path);
		void assemble(std::vector<float> vertices);
	public:
		Model(std::filesystem::path path);
		~Model();

	public:
		//TODO: make rotate and other model transformation things
	};
}