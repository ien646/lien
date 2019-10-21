#pragma once

#include <cinttypes>
#include <vector>

namespace ien::img
{
    class image;
    class image_unpacked_data
    {
        friend class image;

    private:
        uint8_t* _r;
        uint8_t* _g;
        uint8_t* _b;
        uint8_t* _a;
        size_t _size;

		constexpr image_unpacked_data() noexcept 
			: _r(nullptr)
			, _g(nullptr)
			, _b(nullptr)
			, _a(nullptr)
			, _size(0)
		{ }
        
    public:
        image_unpacked_data(size_t pixel_count);
        ~image_unpacked_data();

        uint8_t* data_r() noexcept;
        uint8_t* data_g() noexcept;
        uint8_t* data_b() noexcept;
        uint8_t* data_a() noexcept;

        const uint8_t* cdata_r() const noexcept;
        const uint8_t* cdata_g() const noexcept;
        const uint8_t* cdata_b() const noexcept;
        const uint8_t* cdata_a() const noexcept;

        size_t size() const noexcept;

        void resize(size_t len);

        [[nodiscard]] std::vector<uint8_t> pack_data() const;
    };

    extern image_unpacked_data unpack_image_data(const uint8_t* data, size_t len);
}