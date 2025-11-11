#pragma once
#include <iostream>
#include "string"
#include "../Vector/Vector2.h"
#include "../Vector/Vector3.h"
#include <fstream>
#include <map>
#include <unordered_map>

class Image
{
private:
    std::string m_file_data;
    std::string m_output_file_name;
    std::unordered_map<Vector2, Vector3> m_mapped_image_data;
    Vector2 m_current_pixel_position;
    std::ofstream m_out;
    std::ifstream m_in;
    Vector2 m_resolution;
public:
    Image();
    Image(const char* output_file_name, Vector2 resolution);
    Image(const Image& image);
    ~Image();

    void Init();

    void WritePixel(Vector3 pixel);

    void SetPixel(Vector2 position, const Vector3& color);

    Vector3 GetPixel(Vector2 position);

    void Print();

    void Export();

    void Load(const char* image_path);

    int Size();

    std::string GetFilePath();

    static std::vector<float> image_to_float(Image & image);

    static Image Mix(Image& a, Image& b, float mix);

    Image operator+(Image& other);
    Image operator-(Image& other);
    Image operator*(Image& other);
    Image operator/(Image& other);

    Vector2 GetResolution();

    std::unordered_map<Vector2, Vector3> GetImageData();

};