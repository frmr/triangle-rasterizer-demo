#pragma once

#include "trTexture.hpp"
#include "tfString.hpp"
#include <memory>
#include <unordered_map>

namespace trd
{
	class TextureMap
	{
	public:
		                                                             TextureMap();

		const tr::Texture*                                           get(const tf::String& filename) const;

	private:
		void                                                         add(const tf::String& filename);

	private:
		std::unordered_map<tf::String, std::unique_ptr<tr::Texture>> m_textures;
	};
}