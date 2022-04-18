#pragma once

namespace TIPS 
{

enum class ImageFormat
{
    mono8,   // unsigned char luminance
    mono16,  // unsigned short luminance
    mono32,  // float luminance

    monoA8,  // unsigned char luminance with alpha
    monoA16, // unsigned short luminance with alpha
    monoA32, // float luminance with alpha

    RGB8,    // unsigned char RGB
    RGB16,   // unsigned short RGB
    RGB32,   // float RGB

    RGBA8,   // unsigned char RGBA
    RGBA16,  // unsigned short RGBA
    RGBA32,  // float RGBA

    UNDEFINED = -1

};


inline int channelPerPixel(const ImageFormat& format)
{
    switch (format) 
    {
        case ImageFormat::mono8:
        case ImageFormat::mono16:
        case ImageFormat::mono32: return 1;
        case ImageFormat::monoA8:
        case ImageFormat::monoA16:
        case ImageFormat::monoA32: return 2;
        case ImageFormat::RGB8:
        case ImageFormat::RGB16:
        case ImageFormat::RGB32: return 3;
        case ImageFormat::RGBA8:
        case ImageFormat::RGBA16:
        case ImageFormat::RGBA32: return 4;
        default: return 0;
    }
}

inline int bytePerPixel(const ImageFormat& format)
{
    switch (format)
    {
        case ImageFormat::mono8: return 1;
        case ImageFormat::mono16: return 2;
        case ImageFormat::mono32: return 4;
        case ImageFormat::monoA8: return 2;
        case ImageFormat::monoA16: return 4;
        case ImageFormat::monoA32: return 8;
        case ImageFormat::RGB8: return 3;
        case ImageFormat::RGB16: return 6;
        case ImageFormat::RGB32: return 12;
        case ImageFormat::RGBA8: return 4;
        case ImageFormat::RGBA16: return 8;
        case ImageFormat::RGBA32: return 16;
        default: return 0;
    }
}

}  // end of namespace TIPS