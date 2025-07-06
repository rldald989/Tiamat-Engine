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

void BoxBlur(Image& a, Image& b, Vector2 canvSize) {
    std::unordered_map<Vector2, Vector3> data = a.GetImageData();

    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < data.size(); i++) {

        Vector3 result = data[current_export_pixel];
        if ((current_export_pixel.m_x - 1 >= 0 && current_export_pixel.m_y - 1 >= 0) &&
            (current_export_pixel.m_x + 1 < canvSize.m_x && current_export_pixel.m_y + 1 < canvSize.m_y))
        {
            // Not near edges
            result = Vector3::average
            (
                //top left
                data[current_export_pixel + Vector2(-1, -1)],
                //top middle
                data[current_export_pixel + Vector2(0, -1)],
                //top right
                data[current_export_pixel + Vector2(1, -1)],
                //middle right
                data[current_export_pixel + Vector2(1, 0)],
                //bottom right
                data[current_export_pixel + Vector2(1, 1)],
                //middle bottom
                data[current_export_pixel + Vector2(0, 1)],
                //bottom left
                data[current_export_pixel + Vector2(-1, 1)],
                //middle left
                data[current_export_pixel + Vector2(-1, 0)],
                //self
                data[current_export_pixel]
            );
        }
        else if (current_export_pixel.m_x - 1 <= 0 && current_export_pixel.m_y - 1 <= 0) {
            //Top left corner
            result = Vector3::average
            (
                //middle right
                data[current_export_pixel + Vector2(1, 0)], //keep
                //bottom right
                data[current_export_pixel + Vector2(1, 1)], //keep
                //middle bottom
                data[current_export_pixel + Vector2(0, 1)], //keep
                //self
                data[current_export_pixel]
            );
        }
        else if ((current_export_pixel.m_x - 1 <= 0 && current_export_pixel.m_y - 1 >= 0) && (current_export_pixel.m_x + 1 < canvSize.m_x && current_export_pixel.m_y + 1 < canvSize.m_y))
        {
            //Left edge
            result = Vector3::average
            (
                //top middle
                data[current_export_pixel + Vector2(0, -1)], //keep
                //top right
                data[current_export_pixel + Vector2(1, -1)], //keep
                //middle right
                data[current_export_pixel + Vector2(1, 0)], //keep
                //bottom right
                data[current_export_pixel + Vector2(1, 1)], //keep
                //middle bottom
                data[current_export_pixel + Vector2(0, 1)], //keep
                //self
                data[current_export_pixel]
            );
        }
        else if ((current_export_pixel.m_x - 1 >= 0 && current_export_pixel.m_y - 1 <= 0) && (current_export_pixel.m_x + 1 < canvSize.m_x && current_export_pixel.m_y + 1 < canvSize.m_y))
        {
            //Top edge
            result = Vector3::average
            (
                //middle right
                data[current_export_pixel + Vector2(1, 0)],
                //bottom right
                data[current_export_pixel + Vector2(1, 1)],
                //middle bottom
                data[current_export_pixel + Vector2(0, 1)],
                //bottom left
                data[current_export_pixel + Vector2(-1, 1)],
                //middle left
                data[current_export_pixel + Vector2(-1, 0)],
                //self
                data[current_export_pixel]
            );
        }
        else if ((current_export_pixel.m_x - 1 >= 0) && (current_export_pixel.m_x + 1 < canvSize.m_x && current_export_pixel.m_y + 1 <= canvSize.m_y))
        {
            //Bottom edge
            result = Vector3::average
            (
                //top left
                data[current_export_pixel + Vector2(-1, -1)],
                //top middle
                data[current_export_pixel + Vector2(0, -1)],
                //top right
                data[current_export_pixel + Vector2(1, -1)],
                //middle right
                data[current_export_pixel + Vector2(1, 0)],
                //middle left
                data[current_export_pixel + Vector2(-1, 0)],
                //self
                data[current_export_pixel]
            );
        }
        else if ((current_export_pixel.m_y - 1 >= 0) && (current_export_pixel.m_x + 1 <= canvSize.m_x && current_export_pixel.m_y + 1 < canvSize.m_y))
        {
            //Right Edge
            result = Vector3::average
            (
                //top left
                data[current_export_pixel + Vector2(-1, -1)],
                //top middle
                data[current_export_pixel + Vector2(0, -1)],
                //middle bottom
                data[current_export_pixel + Vector2(0, 1)],
                //bottom left
                data[current_export_pixel + Vector2(-1, 1)],
                //middle left
                data[current_export_pixel + Vector2(-1, 0)],
                //self
                data[current_export_pixel]
            );
        }

        b.WritePixel(result);

        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= canvSize.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }
}
