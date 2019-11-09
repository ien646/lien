#include <ien/image_ops.hpp>

#include <ien/fixed_vector.hpp>
#include <ien/platform.hpp>
#include <ien/internal/image_ops_args.hpp>
#include <ien/internal/std/image_ops_std.hpp>
#include <algorithm>

#if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
    #include <ien/internal/x86/image_ops_x86.hpp>
#elif defined(LIEN_ARCH_ARM) || defined(LIEN_ARCH_ARM64)
    #include <ien/internal/arm/image_ops_arm.hpp>
#endif

namespace ien::img
{
    template<typename TFuncPtr>
    TFuncPtr ARCH_X86_OVERLOAD_SELECT(TFuncPtr def, TFuncPtr sse2, TFuncPtr avx2)
    {
        #if defined(LIEN_ARCH_X86_64) // on x86-64 SSE2 is guaranteed
            return platform::x86::get_feature(platform::x86::feature::AVX2) ? avx2 : sse2;
        #elif defined(LIEN_ARCH_X86)
            return platform::x86::get_feature(platform::x86::feature::AVX2) ? avx2
                 : platform::x86::get_feature(platform::x86::feature::SSE2) ? sse2 : default;
        #else
            #error "Unable to select x86 overload on non-x86 platform!"
        #endif
    }

    void truncate_channel_data(image_unpacked_data* img, int bits_r, int bits_g, int bits_b, int bits_a)
    {
        typedef void(*func_ptr_t)(const _internal::truncate_channel_args& args);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::truncate_channel_data_std,
                &_internal::truncate_channel_data_sse2,
                &_internal::truncate_channel_data_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::truncate_channel_data_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::truncate_channel_data_std;
        #endif

        _internal::truncate_channel_args args(img, bits_r, bits_g, bits_b, bits_a);
        func(args);
    }

    fixed_vector<uint8_t> rgba_average(const image* img)
    {
        typedef fixed_vector<uint8_t>(*func_ptr_t)(const _internal::channel_info_extract_args_rgba&);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::rgba_average_std,
                &_internal::rgba_average_sse2,
                &_internal::rgba_average_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::rgba_average_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::rgba_average_std;
        #endif

        _internal::channel_info_extract_args_rgba args(img);
        return func(args);
    }    

    fixed_vector<uint8_t> rgba_max(const image* img)
    {
        typedef fixed_vector<uint8_t>(*func_ptr_t)(const _internal::channel_info_extract_args_rgba&);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::rgba_max_std,
                &_internal::rgba_max_sse2,
                &_internal::rgba_max_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::rgba_max_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::rgba_max_std;
        #endif

        _internal::channel_info_extract_args_rgba args(img);
        return func(args);
    }

    fixed_vector<uint8_t> rgba_min(const image* img)
    {
        typedef fixed_vector<uint8_t>(*func_ptr_t)(const _internal::channel_info_extract_args_rgba&);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::rgba_min_std,
                &_internal::rgba_min_sse2,
                &_internal::rgba_min_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::rgba_min_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::rgba_min_std;
        #endif

        _internal::channel_info_extract_args_rgba args(img);
        return func(args);
    }

    fixed_vector<uint8_t> rgba_sum_saturated(const image* img)
    {
        typedef fixed_vector<uint8_t>(*func_ptr_t)(const _internal::channel_info_extract_args_rgba&);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::rgba_sum_saturated_std,
                &_internal::rgba_sum_saturated_sse2,
                &_internal::rgba_sum_saturated_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::rgba_sum_saturated_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::rgba_sum_saturated_std;
        #endif

        _internal::channel_info_extract_args_rgba args(img);
        return func(args);
    }

    fixed_vector<float> rgb_saturation(const image* img)
    {
        typedef fixed_vector<float>(*func_ptr_t)(const _internal::channel_info_extract_args_rgb&);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::rgb_saturation_std,
                &_internal::rgb_saturation_sse2,
                &_internal::rgb_saturation_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::rgb_saturation_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::rgb_saturation_std;
        #endif

        _internal::channel_info_extract_args_rgb args(img);
        return func(args);
    }

    fixed_vector<float> rgb_luminance(const image* img)
    {
        typedef fixed_vector<float>(*func_ptr_t)(const _internal::channel_info_extract_args_rgb&);

        #if defined(LIEN_ARCH_X86) || defined(LIEN_ARCH_X86_64)
            static func_ptr_t func = ARCH_X86_OVERLOAD_SELECT(
                &_internal::rgb_luminance_std,
                &_internal::rgb_luminance_sse2,
                &_internal::rgb_luminance_avx2
            );
        #elif defined(LIEN_ARCH_ARM64)
            static func_ptr_t func = &_internal::rgb_luminance_neon;
        #elif defined(LIEN_ARCH_ARM)
            LIEN_NOT_IMPLEMENTED();
        #else
            static func_ptr_t func = &_internal::rgb_luminance_std;
        #endif

        _internal::channel_info_extract_args_rgb args(img);
        return func(args);
    }
}