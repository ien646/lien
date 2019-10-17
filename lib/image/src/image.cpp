#include <ien/image.hpp>

#include <ien/assert.hpp>
#include <ien/platform.hpp>
#include <stb_image.h>
#include <stb_image_resize.h>
#include <stb_image_write.h>
#include <stdexcept>

namespace ien::img
{
    image::image(int width, int height)
        : _width(width)
        , _height(height)
        , _data(static_cast<size_t>(width) * height)
    { }

    image::image(const std::string& path)
		: _width(0), _height(0)
    {
        int channels_dummy = 0;
        uint8_t* packed_data = stbi_load(
            path.c_str(),
            &_width,
            &_height,
            &channels_dummy,
            4
        );

        if(packed_data == nullptr)
        {
            throw std::invalid_argument("Unable to load image with path: " + path);
        }
        _data = unpack_image_data(packed_data, (static_cast<size_t>(_width) * _height * 4));
        stbi_image_free(packed_data);
    }

    image_unpacked_data* image::data() noexcept { return &_data; }

    const image_unpacked_data* image::cdata() const noexcept { return &_data; }

    void image::save_to_file_png(const std::string& path, int compression_level)
    {
        std::vector<uint8_t> packed_data = _data.pack_data();
        stbi_write_png_compression_level = compression_level;
        stbi_write_png(path.c_str(), _width, _height, 4, packed_data.data(), _width * 4);
    }

    size_t image::pixel_count() const noexcept
    {
        return static_cast<size_t>(_width) * _height;
    }

    int image::width() const noexcept { return _width; }
    
    int image::height() const noexcept { return _height; }

    std::array<uint8_t, 4> image::get_packed_pixel(int index)
    {
        return { 
            _data.cdata_r()[index], 
            _data.cdata_g()[index], 
            _data.cdata_b()[index],
            _data.cdata_a()[index] 
        };
    }

    std::array<uint8_t, 4> image::get_packed_pixel(int x, int y)
    {
        return {
            _data.cdata_r()[(y * _height) + x],
            _data.cdata_g()[(y * _height) + x],
            _data.cdata_b()[(y * _height) + x],
            _data.cdata_a()[(y * _height) + x],
        };
    }

    void image::save_to_file_jpeg(const std::string& path, int quality)
    {
        std::vector<uint8_t> packed_data = _data.pack_data();
        stbi_write_jpg(path.c_str(), _width, _height, 4, packed_data.data(), quality);
    }

    void image::save_to_file_tga(const std::string& path)
    {
        std::vector<uint8_t> packed_data = _data.pack_data();
        stbi_write_tga(path.c_str(), _width, _height, 4, packed_data.data());
    }

    void image::resize_absolute(int w, int h)
    {
        const std::vector<uint8_t> packed_data = _data.pack_data();
        _data.resize(static_cast<size_t>(w) * h); // realloc unpacked data buffers
        
        std::vector<uint8_t> resized_packed_data;
        resized_packed_data.resize(w * h * 4);

        stbir_resize_uint8(
            packed_data.data(), _width, _height, 4, resized_packed_data.data(), w, h, 4, 4
        );
        
        uint8_t* r = _data.data_r();
        uint8_t* g = _data.data_g();
        uint8_t* b = _data.data_b();
        uint8_t* a = _data.data_a();

        for(size_t i = 0; i < (w * h); ++i)
        {
            r[i] = resized_packed_data[(i * 4) + 0];
            g[i] = resized_packed_data[(i * 4) + 1];
            b[i] = resized_packed_data[(i * 4) + 2];
            a[i] = resized_packed_data[(i * 4) + 3];
        }
    }

    void image::resize_relative(float w, float h)
    {
        int real_w = static_cast<int>(static_cast<float>(_width) * w);
        int real_h = static_cast<int>(static_cast<float>(_height) * h);

        resize_absolute(real_w, real_h);
    }
}