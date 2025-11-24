#pragma once

#include "Output.h"

Vector3 rand_bw() {
    float r = (float)(std::rand() % 10) / 10;
    if (r >= 0.5f) {
        r = 1;
    }
    else {
        r = 0;
    }
    return Vector3(r, r, r);
}

Vector2 kernel_3X3[] = {
    // Top left
    Vector2(-1, -1),
    // Top middle
    Vector2(0, -1),
    // Top right
    Vector2(1, -1),
    // Middle right
    Vector2(1, 0),
    // Bottom right
    Vector2(1, 1),
    // Middle bottom
    Vector2(0, 1),
    // Bottom left
    Vector2(-1, 1),
    // Middle left
    Vector2(-1, 0)
};

Image BoxBlur(Image& a, Vector2 canvSize) {
    std::unordered_map<Vector2, Vector3> data = a.GetImageData();

    Image b(a.GetFilePath().c_str(), a.GetResolution());

    Vector2 current_image_pixel(0, 0);

    for (int i = 0; i < canvSize.m_x * canvSize.m_y; i++) {

        Vector3 result(data[current_image_pixel]);
        int allowed_pixel_count = 0;
        for (size_t i = 0; i < sizeof(kernel_3X3) / sizeof(Vector2); i++)
        {
            Vector2 combo_pixel = kernel_3X3[i] + current_image_pixel;
            if (combo_pixel.m_x >= 0 || combo_pixel.m_y >= 0 || (combo_pixel.m_x >= 0 && combo_pixel.m_y >= 0)) {
                result = result + data[kernel_3X3[i] + current_image_pixel];
                allowed_pixel_count++;
            }

        }

        result = result / allowed_pixel_count;

        b.WritePixel(result);

        current_image_pixel.m_x++;
        if (current_image_pixel.m_x >= canvSize.m_x) {
            current_image_pixel.m_x = 0;
            current_image_pixel.m_y++;
        }
    }

    return b;
}