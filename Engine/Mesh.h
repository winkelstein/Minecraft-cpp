#pragma once
#include <filesystem>

#include "drawable.h"

namespace Engine
{
	class Mesh : public drawable
	{
	private:
		GLuint VAO;
		size_t count;

	private:
		template<typename POD>
		static std::istream& deserialize(std::istream& is, std::vector<POD>& v);

		static std::vector<float> importModel(std::filesystem::path path);
		void assemble(std::vector<float> vertices);

	public:
		Mesh(std::filesystem::path path);
		~Mesh();

	public:
		void draw(gltk::Shader& shader) const override;
	};
}

template<typename POD>
inline std::istream& Engine::Mesh::deserialize(std::istream& is, std::vector<POD>& v)
{
	static_assert(std::is_trivial<POD>::value && std::is_standard_layout<POD>::value,
		"Can only deserialize POD types with this function");

	decltype(v.size()) size;
	is.read(reinterpret_cast<char*>(&size), sizeof(size));
	v.resize(size);
	is.read(reinterpret_cast<char*>(v.data()), v.size() * sizeof(POD));
	return is;
}