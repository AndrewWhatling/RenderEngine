#pragma once

#include "../core/color.h"
#include <vector>
#include <string>
#include "pixel.h"
#include <cstring>
#include <unordered_map>

#include <Imath/ImathBox.h>
#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfArray.h>
#include <OpenEXR/ImfChannelList.h>
#include <OpenEXR/ImfFrameBuffer.h>
#include <OpenEXR/ImfOutputFile.h>
#include <OpenEXR/ImfStringAttribute.h>
#include <nlohmann/json.hpp>

// MurmurHash3_x86_32 
inline uint32_t MurmurHash3_x86_32(const void* key, size_t len, uint32_t seed = 0) {
    const uint8_t *data = static_cast<const uint8_t*>(key);
    const int nblocks = static_cast<int>(len / 4);

    uint32_t h1 = seed;
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    
    // bodu
    const uint32_t *blocks = reinterpret_cast<const uint32_t*>(data + nblocks * 4);
    for (int i = -nblocks; i; i++) {
        uint32_t k1 = blocks[i];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> 17);
        k1 *= c2;
        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> 19);
        h1 = h1 * 5 + 0xe6546b64;
    }
    // tail
    const uint8_t* tail = data + nblocks * 4;
    uint32_t k1 = 0;
    switch (len & 3) {
        case 3: k1 ^= tail[2] << 16; [[fallthrough]];
        case 2: k1 ^= tail[1] << 8;  [[fallthrough]];
        case 1: k1 ^= tail[0];
                k1 *= c1;
                k1 = (k1 << 15) | (k1 >> 17);
                k1 *= c2;
                h1 ^= k1;
    }
    
    // finalization

    h1 ^= len;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}

inline uint32_t hash_name(const std::string &name) {
    return MurmurHash3_x86_32(name.data(), name.size(), 0);
}

inline float uint32_to_float32(uint32_t v) {
    float f;
    static_assert(sizeof(f) == sizeof(v));
    std::memcpy(&f, &v, sizeof(float));
    return f;
}

inline std::string to_hex8(uint32_t v) {
    std::ostringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << std::nouppercase << v;
    return ss.str();
}

inline void write_exr16(const std::string& filename, int width, int height, const std::vector<std::vector<pixel>>& framebuffer) {
    
    Imf::Header header(width, height);
    
    header.channels().insert("R", Imf::Channel(Imf::HALF));
    header.channels().insert("G", Imf::Channel(Imf::HALF));
    header.channels().insert("B", Imf::Channel(Imf::HALF));
    header.channels().insert("A", Imf::Channel(Imf::HALF));

    header.channels().insert("N.red", Imf::Channel(Imf::HALF));
    header.channels().insert("N.green", Imf::Channel(Imf::HALF));
    header.channels().insert("N.blue", Imf::Channel(Imf::HALF));
    header.channels().insert("depth.Z", Imf::Channel(Imf::HALF));

    header.channels().insert("P.x", Imf::Channel(Imf::HALF));
    header.channels().insert("P.y", Imf::Channel(Imf::HALF));
    header.channels().insert("P.z", Imf::Channel(Imf::HALF));

    header.channels().insert("facing_ratio.r", Imf::Channel(Imf::HALF));
    //header.channels().insert("object_id.r", Imf::Channel(Imf::HALF));

    header.channels().insert("CryptoObject00.R", Imf::Channel(Imf::FLOAT));
    header.channels().insert("CryptoObject00.G", Imf::Channel(Imf::FLOAT));
    header.channels().insert("CryptoObject00.B", Imf::Channel(Imf::FLOAT));
    header.channels().insert("CryptoObject00.A", Imf::Channel(Imf::FLOAT));

    header.channels().insert("CryptoMaterial00.R", Imf::Channel(Imf::FLOAT));
    header.channels().insert("CryptoMaterial00.G", Imf::Channel(Imf::FLOAT));
    header.channels().insert("CryptoMaterial00.B", Imf::Channel(Imf::FLOAT));
    header.channels().insert("CryptoMaterial00.A", Imf::Channel(Imf::FLOAT));

    Imf::FrameBuffer buffer;
    
    std::vector<Imf::Rgba> rgbaPixels(height * width);
    
    std::vector<Imath::half> nx(height * width);
    std::vector<Imath::half> ny(height * width);
    std::vector<Imath::half> nz(height * width);
    std::vector<Imath::half> depth(height * width);

    std::vector<Imath::half> px(height * width);
    std::vector<Imath::half> py(height * width);
    std::vector<Imath::half> pz(height * width);

    std::vector<Imath::half> facing_ratio(height * width);
    //std::vector<Imath::half> object_id(height * width);

    std::vector<float> cryptoR(height * width);
    std::vector<float> cryptoG(height * width);
    std::vector<float> cryptoB(height * width);
    std::vector<float> cryptoA(height * width);

    std::vector<float> cryptoMatR(height * width);
    std::vector<float> cryptoMatG(height * width);
    std::vector<float> cryptoMatB(height * width);
    std::vector<float> cryptoMatA(height * width);

    std::unordered_map<std::string, std::string> manifest;
    std::unordered_map<std::string, std::string> mat_manifest;
    

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++) {
            int idx = j * width + i;
            const pixel &curr_pixel = framebuffer[j][i];

            vec3 col = return_srgb(curr_pixel.rgb);
            vec3 norm = curr_pixel.N;

            rgbaPixels[idx].r = col.x;
            rgbaPixels[idx].g = col.y;
            rgbaPixels[idx].b = col.z;
            rgbaPixels[idx].a = curr_pixel.hit;
            
            nx[idx] = Imath::half(curr_pixel.N.x);
            ny[idx] = Imath::half(curr_pixel.N.y);
            nz[idx] = Imath::half(curr_pixel.N.z);
            depth[idx] = Imath::half(curr_pixel.depth);
            
            px[idx] = Imath::half(curr_pixel.P.x);
            py[idx] = Imath::half(curr_pixel.P.y);
            pz[idx] = Imath::half(curr_pixel.P.z);

            facing_ratio[idx] = Imath::half(curr_pixel.facing_ratio);
            //object_id[idx] = Imath::half(curr_pixel.object_id);
            
            uint32_t hash = hash_name(std::to_string(curr_pixel.object_id));
            float hash_as_float = uint32_to_float32(hash);

            uint32_t mat_hash = hash_name(std::to_string(curr_pixel.mat_id));
            float mat_hash_as_float = uint32_to_float32(mat_hash);

            cryptoR[idx] = hash_as_float;
            cryptoG[idx] = curr_pixel.hit ? 1.0f : 0.0f;
            cryptoB[idx] = 0.0f;
            cryptoA[idx] = 0.0f;

            cryptoMatR[idx] = mat_hash_as_float;
            cryptoMatG[idx] = curr_pixel.hit ? 1.0f : 0.0f;
            cryptoMatB[idx] = 0.0f;
            cryptoMatA[idx] = 0.0f;

            manifest[to_hex8(hash)] = "/object_" + std::to_string(int(curr_pixel.object_id)); 
            mat_manifest[to_hex8(mat_hash)] = "/material_" + std::to_string(int(curr_pixel.mat_id));
            }

    buffer.insert("R", Imf::Slice(Imf::HALF, (char*)&rgbaPixels[0].r, sizeof(Imf::Rgba), sizeof(Imf::Rgba)*width));
    buffer.insert("G", Imf::Slice(Imf::HALF, (char*)&rgbaPixels[0].g, sizeof(Imf::Rgba), sizeof(Imf::Rgba)*width));
    buffer.insert("B", Imf::Slice(Imf::HALF, (char*)&rgbaPixels[0].b, sizeof(Imf::Rgba), sizeof(Imf::Rgba)*width));
    buffer.insert("A", Imf::Slice(Imf::HALF, (char*)&rgbaPixels[0].a, sizeof(Imf::Rgba), sizeof(Imf::Rgba)*width));

    buffer.insert("N.red", Imf::Slice(Imf::HALF, (char*)nx.data(), sizeof(Imath::half), sizeof(Imath::half)*width));
    buffer.insert("N.green", Imf::Slice(Imf::HALF, (char*)ny.data(), sizeof(Imath::half), sizeof(Imath::half)*width));
    buffer.insert("N.blue", Imf::Slice(Imf::HALF, (char*)nz.data(), sizeof(Imath::half), sizeof(Imath::half)*width));
    buffer.insert("depth.Z", Imf::Slice(Imf::HALF, (char*)depth.data(), sizeof(Imath::half), sizeof(Imath::half)*width));

    buffer.insert("P.x", Imf::Slice(Imf::HALF, (char*)px.data(), sizeof(Imath::half), sizeof(Imath::half)*width));
    buffer.insert("P.y", Imf::Slice(Imf::HALF, (char*)py.data(), sizeof(Imath::half), sizeof(Imath::half)*width));
    buffer.insert("P.z", Imf::Slice(Imf::HALF, (char*)pz.data(), sizeof(Imath::half), sizeof(Imath::half)*width));

    buffer.insert("facing_ratio.r", Imf::Slice(Imf::HALF, (char*)facing_ratio.data(), sizeof(Imath::half), sizeof(Imath::half)*width));
    //buffer.insert("object_id.r", Imf::Slice(Imf::HALF, (char*)object_id.data(), sizeof(Imath::half), sizeof(Imath::half)*width));

    buffer.insert("CryptoObject00.R", Imf::Slice(Imf::FLOAT, (char*)cryptoR.data(), sizeof(float), sizeof(float)*width));
    buffer.insert("CryptoObject00.G", Imf::Slice(Imf::FLOAT, (char*)cryptoG.data(), sizeof(float), sizeof(float)*width));
    buffer.insert("CryptoObject00.B", Imf::Slice(Imf::FLOAT, (char*)cryptoB.data(), sizeof(float), sizeof(float)*width));
    buffer.insert("CryptoObject00.A", Imf::Slice(Imf::FLOAT, (char*)cryptoA.data(), sizeof(float), sizeof(float)*width));

    buffer.insert("CryptoMaterial00.R", Imf::Slice(Imf::FLOAT, (char*)cryptoMatR.data(), sizeof(float), sizeof(float)*width));
    buffer.insert("CryptoMaterial00.G", Imf::Slice(Imf::FLOAT, (char*)cryptoMatG.data(), sizeof(float), sizeof(float)*width));
    buffer.insert("CryptoMaterial00.B", Imf::Slice(Imf::FLOAT, (char*)cryptoMatB.data(), sizeof(float), sizeof(float)*width));
    buffer.insert("CryptoMaterial00.A", Imf::Slice(Imf::FLOAT, (char*)cryptoMatA.data(), sizeof(float), sizeof(float)*width));
    
    nlohmann::json manifest_json;
    for (auto &p : manifest)
        manifest_json[p.second] = p.first;

    header.insert("cryptomatte/CryptoObject/manifest", Imf::StringAttribute(manifest_json.dump()));
    header.insert("cryptomatte/CryptoObject/hash", Imf::StringAttribute("MurmurHash3_32"));
    header.insert("cryptomatte/CryptoObject/conversion", Imf::StringAttribute("uint32_to_float32"));
    header.insert("cryptomatte/CryptoObject/name", Imf::StringAttribute("CryptoObject"));
    
    nlohmann::json mat_manifest_json;
    for (auto &m : mat_manifest)
        mat_manifest_json[m.second] = m.first;

    header.insert("cryptomatte/CryptoMaterial/manifest", Imf::StringAttribute(mat_manifest_json.dump()));
    header.insert("cryptomatte/CryptoMaterial/hash", Imf::StringAttribute("MurmurHash3_32"));
    header.insert("cryptomatte/CryptoMaterial/conversion", Imf::StringAttribute("uint32_to_float32"));
    header.insert("cryptomatte/CryptoMaterial/name", Imf::StringAttribute("CryptoMaterial"));

    Imf::OutputFile file(filename.c_str(), header);           
    file.setFrameBuffer(buffer);
    file.writePixels(height);
}
