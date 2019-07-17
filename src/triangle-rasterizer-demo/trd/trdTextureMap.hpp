#pragma once

#include "trTexture.hpp"
#include "tfString.hpp"
#include "tfUnorderedMap.hpp"
#include <memory>

namespace trd
{
	class TextureMap
	{
	public:
		                                                           TextureMap();

		const tr::Texture*                                         get(const tf::String& filename) const;

	private:
		void                                                       add(const tf::String& filename);

	private:
		tf::UnorderedMap<tf::String, std::unique_ptr<tr::Texture>> m_textures;
	};
}