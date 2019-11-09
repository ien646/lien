#include <ien/platform.hpp>

#if defined(LIEN_ARCH_ARM) || defined(LIEN_ARCH_ARM64)

namespace ien::img::_internal
{
    void truncate_channel_data_neon(const truncate_channel_args& args);

    fixed_vector<uint8_t> rgba_average_neon(const channel_info_extract_args_rgba& args);

    fixed_vector<uint8_t> rgba_max_neon(const channel_info_extract_args_rgba& args);

    fixed_vector<uint8_t> rgba_min_neon(const channel_info_extract_args_rgba& args);

    fixed_vector<uint8_t> rgba_sum_saturated_neon(const channel_info_extract_args_rgba& args);

    fixed_vector<float> rgb_saturation_neon(const channel_info_extract_args_rgb& args);

    fixed_vector<float> rgb_luminance_neon(const channel_info_extract_args_rgb& args);
}

#endif