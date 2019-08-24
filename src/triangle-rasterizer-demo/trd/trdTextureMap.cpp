#include "trdTextureMap.hpp"
#include "trdExternalLibraryException.hpp"
#include "lodepng.h"

trd::TextureMap::TextureMap()
{
}

const tr::Texture* trd::TextureMap::get(const tf::String& filename)
{
	const auto iterator = m_textures.find(filename);

	if (iterator == m_textures.end())
	{
		std::vector<uint8_t> encodedData;

		if (!lodepng::load_file(encodedData, filename))
		{
			uint32_t             width;
			uint32_t             height;
			lodepng::State       state;
			std::vector<uint8_t> decodedData;

			state.info_raw.colortype = LodePNGColorType::LCT_RGBA;

			if (!lodepng::decode(decodedData, width, height, state, encodedData))
			{
				return m_textures.emplace(filename, new tr::Texture(width, height, decodedData)).first->second.get();
			}
			else
			{
				throw ExternalLibraryException("trd::TextureMap::get(): lodepng failed to decode texture (" + filename + ")");
			}
		}
		else
		{
			throw ExternalLibraryException("trd::TextureMap::get(): lodepng failed to load texture (" + filename + ")");
		}
	}
	else
	{
		return iterator->second.get();
	}
}