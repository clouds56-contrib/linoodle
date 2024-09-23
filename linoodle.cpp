
#include "windows_library.h"

typedef __attribute__((ms_abi)) size_t(*tDecompress)(uint8_t* src_buf, size_t src_len, uint8_t* dst_buf, size_t dst_len, int64_t fuzz, int64_t crc, int64_t verbose, uint8_t* dec_buf_base, size_t dec_buf_size, void* cb, void* cb_ctx, void* scratch, size_t scratch_size, int64_t thread_phase);
typedef __attribute__((ms_abi)) size_t(*tCompress)(int64_t codec, uint8_t* src_buf, size_t src_len, uint8_t* dst_buf, int64_t level, void* opts, void* dictionary_base, void* lrm, void* scratch, size_t scratch_size);
typedef __attribute__((ms_abi)) void*(*tCompressOptions_GetDefault)(int64_t codec, int64_t level);
typedef __attribute__((ms_abi)) size_t(*tGetCompressedBufferSizeNeeded)(size_t src_len);
typedef __attribute__((ms_abi)) size_t(*tGetDecodeBufferSize)(size_t src_len, bool corruption_possible);

class OodleWrapper {
public:
    OodleWrapper() :
        m_oodleLib(WindowsLibrary::Load("oo2core_6_win64.dll"))
    {
        m_Decompress = reinterpret_cast<tDecompress>(m_oodleLib.GetExport("OodleLZ_Decompress"));
        m_Compress = reinterpret_cast<tCompress>(m_oodleLib.GetExport("OodleLZ_Compress"));
        m_CompressOptions_GetDefault = reinterpret_cast<tCompressOptions_GetDefault>(m_oodleLib.GetExport("OodleLZ_CompressOptions_GetDefault"));
        m_GetCompressedBufferSizeNeeded = reinterpret_cast<tGetCompressedBufferSizeNeeded>(m_oodleLib.GetExport("OodleLZ_GetCompressedBufferSizeNeeded"));
        m_GetDecodeBufferSize = reinterpret_cast<tGetDecodeBufferSize>(m_oodleLib.GetExport("OodleLZ_GetDecodeBufferSize"));
    }

    size_t Decompress(uint8_t* src_buf, size_t src_len, uint8_t* dst_buf, size_t dst_len, int64_t fuzz, int64_t crc, int64_t verbose, uint8_t* dec_buf_base, size_t dec_buf_size, void* cb, void* cb_ctx, void* scratch, size_t scratch_size, int64_t thread_phase) {
        WindowsLibrary::SetupCall();
        return m_Decompress(src_buf, src_len, dst_buf, dst_len, fuzz, crc, verbose, dec_buf_base, dec_buf_size, cb, cb_ctx, scratch, scratch_size, thread_phase);
    }

    size_t Compress(int64_t codec, uint8_t* src_buf, size_t src_len, uint8_t* dst_buf, int64_t level, void* opts, void* dictionary_base, void* lrm, void* scratch, size_t scratch_size) {
        WindowsLibrary::SetupCall();
        return m_Compress(codec, src_buf, src_len, dst_buf, level, opts, dictionary_base, lrm, scratch, scratch_size);
    }

    void* CompressOptions_GetDefault(int64_t codec, int64_t level) {
        WindowsLibrary::SetupCall();
        return m_CompressOptions_GetDefault(codec, level);
    }

    size_t GetCompressedBufferSizeNeeded(size_t src_len) {
        WindowsLibrary::SetupCall();
        return m_GetCompressedBufferSizeNeeded(src_len);
    }

    size_t GetDecodeBufferSize(size_t src_len, bool corruption_possible) {
        WindowsLibrary::SetupCall();
        return m_GetDecodeBufferSize(src_len, corruption_possible);
    }

private:
    WindowsLibrary m_oodleLib;
    tDecompress m_Decompress; // for oo2core_6_win64::OodleLZ_Decompress
    tCompress m_Compress; // for oo2core_6_win64::OodleLZ_Compress
    tCompressOptions_GetDefault m_CompressOptions_GetDefault; // for oo2core_6_win64::OodleLZ_CompressOptions_GetDefault
    tGetCompressedBufferSizeNeeded m_GetCompressedBufferSizeNeeded; // for oo2core_6_win64::OodleLZ_GetCompressedBufferSizeNeeded
    tGetDecodeBufferSize m_GetDecodeBufferSize; // for oo2core_6_win64::OodleLZ_GetDecodeBufferSize
};

OodleWrapper g_oodleWrapper;

extern "C" size_t OodleLZ_Decompress(uint8_t* src_buf, size_t src_len, uint8_t* dst_buf, size_t dst_len, int64_t fuzz, int64_t crc, int64_t verbose, uint8_t* dec_buf_base, size_t dec_buf_size, void* cb, void* cb_ctx, void* scratch, size_t scratch_size, int64_t thread_phase) {
    return g_oodleWrapper.Decompress(src_buf, src_len, dst_buf, dst_len, fuzz, crc, verbose, dec_buf_base, dec_buf_size, cb, cb_ctx, scratch, scratch_size, thread_phase);
}

extern "C" size_t OodleLZ_Compress(int64_t codec, uint8_t* src_buf, size_t src_len, uint8_t* dst_buf, int64_t level, void* opts, void* dictionary_base, void* lrm, void* scratch, size_t scratch_size) {
    return g_oodleWrapper.Compress(codec, src_buf, src_len, dst_buf, level, opts, dictionary_base, lrm, scratch, scratch_size);
}

extern "C" void* OodleLZ_CompressOptions_GetDefault(int64_t codec, int64_t level) {
    return g_oodleWrapper.CompressOptions_GetDefault(codec, level);
}

extern "C" size_t OodleLZ_GetCompressedBufferSizeNeeded(size_t src_len) {
    return g_oodleWrapper.GetCompressedBufferSizeNeeded(src_len);
}

extern "C" size_t OodleLZ_GetDecodeBufferSize(size_t src_len, bool corruption_possible) {
    return g_oodleWrapper.GetDecodeBufferSize(src_len, corruption_possible);
}
