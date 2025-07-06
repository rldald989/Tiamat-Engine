#include "Output.h"

Image::Image() : m_resolution(0, 0), m_output_file_name(""), m_current_pixel_position(0, 0)
{
}

Image::Image(const char *output_file_name, Vector2 resolution) : m_resolution(resolution), m_output_file_name(output_file_name), m_current_pixel_position(0, 0)
{
   
}

Image::Image(const Image& image) : m_out(image.m_output_file_name), m_resolution(image.m_resolution), m_output_file_name(image.m_output_file_name), m_current_pixel_position(0, 0)
{
}
Image::~Image()
{
}

// Makes sure the ppm file has the correct formatting at the beginning of the file
void Image::Init()
{
    m_out.open(m_output_file_name);
    m_file_data += "P3\n" + std::to_string((int)m_resolution.m_x) + " " + std::to_string((int)m_resolution.m_y) + "\n255\n";
}

// Adds a pixel to the map and gives it a position based on the order you write the pixels in (is stored in an un-rdered map)
void Image::WritePixel(Vector3 pixel)
{
    m_mapped_image_data[m_current_pixel_position] = pixel;
    m_current_pixel_position.m_x++;
    if (m_current_pixel_position.m_x >= m_resolution.m_x) {
        m_current_pixel_position.m_x = 0;
        m_current_pixel_position.m_y++;
    }
}

// Allows you to change the color of a pixel using it's position to grab it from the un-ordered map
void Image::SetPixel(Vector2 position, const Vector3& color)
{
    m_mapped_image_data[position] = color;
}

// Allows you to get the color of a pixel using it's position to grab it from the un-ordered map
Vector3 Image::GetPixel(Vector2 position)
{
    return m_mapped_image_data[position];
}

// Allows you to print the pixel data in order by using the position to order it correctly
void Image::Print()
{
    Vector2 current_print_pixel(0, 0);
    for (int i = 0; i < m_mapped_image_data.size(); i++) {
        std::cout << "Position: " << Vector2::to_string(current_print_pixel) << ", Value: " << Vector3::to_string_i(m_mapped_image_data[current_print_pixel]) << std::endl;
        current_print_pixel.m_x++;
        if (current_print_pixel.m_x >= m_resolution.m_x) {
            current_print_pixel.m_x = 0;
            current_print_pixel.m_y++;
        }
    }
}

// Same principle as the print except this is what actually exports to the .ppm file
void Image::Export()
{
    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < m_mapped_image_data.size(); i++) {
        m_file_data += Vector3::to_string_i(m_mapped_image_data[current_export_pixel] * 255) + "\n";
        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= m_resolution.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }
    m_out << m_file_data;
    m_out.close();
}

// Loads in an image using the WritePixel function to add the pixel, though the loader skips over non-important
// aspects within the file and searches for the size of the image to ensure proper loading
void Image::Load(const char *image_path)
{
    m_current_pixel_position = Vector2(0, 0);
    std::string temp_image_data;
    m_in.open(image_path);
    int counter = 0;
    int rgbCounter = 0;
    Vector3 tempColor(0, 0, 0);
    while(m_in >> temp_image_data){
        counter++;
        if(counter == 2){
            m_resolution.m_x = atoi(temp_image_data.c_str());
        }

        if(counter == 3){
            m_resolution.m_y = atoi(temp_image_data.c_str());
            Init();
        }

        

        if(counter >= 5){

            if(rgbCounter == 0){
                tempColor.x = std::atoi(temp_image_data.c_str());
            }
            else if(rgbCounter == 1){
                tempColor.y = std::atoi(temp_image_data.c_str());
            }
            else if(rgbCounter == 2){
                tempColor.z = std::atoi(temp_image_data.c_str());
                WritePixel(tempColor / 255);
                m_file_data += Vector3::to_string_i(tempColor) + "\n";
                
            }
            rgbCounter++;


        }

        if(rgbCounter >= 3){
            rgbCounter = 0;
        }
        
    }
    counter = 0;
}

std::vector<float> Image::image_to_float(Image& image)
{
    std::vector<float> data;
    data.reserve(image.m_mapped_image_data.size() * 3);

    Vector2 current_print_pixel(image.m_resolution);
    for (int i = image.m_resolution.m_x * image.m_resolution.m_y; i > 0; i--)
    {
        data.push_back(image.m_mapped_image_data[current_print_pixel].x);
        data.push_back(image.m_mapped_image_data[current_print_pixel].y);
        data.push_back(image.m_mapped_image_data[current_print_pixel].z);
        
        current_print_pixel.m_x--;
        if (current_print_pixel.m_x <= 0) {
            current_print_pixel.m_x = image.m_resolution.m_x;
            current_print_pixel.m_y--;
        }
    }

    return data;
}

Image Image::Mix(Image& a, Image& b, float mix)
{
    Image result_image("mix_result.ppm", a.m_resolution);
    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < a.m_mapped_image_data.size(); i++) {

        Vector3 result = a.m_mapped_image_data[current_export_pixel];

        result = Vector3::mix(a.m_mapped_image_data[current_export_pixel], b.m_mapped_image_data[current_export_pixel], mix);

        result_image.WritePixel(result);

        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= a.m_resolution.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }

    return result_image;
}

Image Image::operator+(Image& other)
{
    Image result_image("mix_result.ppm", m_resolution);
    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < m_mapped_image_data.size(); i++) {

        Vector3 result = m_mapped_image_data[current_export_pixel];

        result = (m_mapped_image_data[current_export_pixel] + other.m_mapped_image_data[current_export_pixel]);

        result_image.WritePixel(result);

        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= m_resolution.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }

    return result_image;
}

Image Image::operator-(Image& other)
{
    Image result_image("mix_result.ppm", m_resolution);
    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < m_mapped_image_data.size(); i++) {

        Vector3 result = m_mapped_image_data[current_export_pixel];

        result = (m_mapped_image_data[current_export_pixel] - other.m_mapped_image_data[current_export_pixel]);

        result_image.WritePixel(result);

        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= m_resolution.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }

    return result_image;
}

Image Image::operator*(Image& other)
{
    Image result_image("mix_result.ppm", m_resolution);
    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < m_mapped_image_data.size(); i++) {

        Vector3 result = m_mapped_image_data[current_export_pixel];

        result = (m_mapped_image_data[current_export_pixel] * other.m_mapped_image_data[current_export_pixel]);

        result_image.WritePixel(result);

        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= m_resolution.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }

    return result_image;
}

Image Image::operator/(Image& other)
{
    Image result_image("mix_result.ppm", m_resolution);
    Vector2 current_export_pixel(0, 0);
    for (int i = 0; i < m_mapped_image_data.size(); i++) {

        Vector3 result = m_mapped_image_data[current_export_pixel];

        result = (m_mapped_image_data[current_export_pixel] / other.m_mapped_image_data[current_export_pixel]);

        result_image.WritePixel(result);

        current_export_pixel.m_x++;
        if (current_export_pixel.m_x >= m_resolution.m_x) {
            current_export_pixel.m_x = 0;
            current_export_pixel.m_y++;
        }
    }

    return result_image;
}

// Simply gets the resolution of the image, whether set manually or loaded in
Vector2 Image::GetResolution()
{
    return m_resolution;
}

// This is used to get the pixel information, mainly useful for filters
std::unordered_map<Vector2, Vector3> Image::GetImageData()
{
    return m_mapped_image_data;
}
