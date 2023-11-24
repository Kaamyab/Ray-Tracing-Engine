#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"

#include "color.h"
#include "hittable.h"
#include "output.h"

#include <iostream>
#include <fstream>
#include <chrono>

class camera {
public:
    double aspect_ratio = 16.0 /9.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    int MaxDepth = 10;

    camera() {
        // Inputs
        std::cout << "Enter width: ";
        std::cin >> image_width;
        calc_height(image_width, aspect_ratio);

        std::cout << "Enter Maximum Samples: ";
        std::cin >> samples_per_pixel;

        // default constructor
    }

    // an overload for the constructor
    camera(double aspect_ratio, int image_width, int samples_per_pixel, int maxDepth)
        : aspect_ratio(aspect_ratio), image_width(image_width), samples_per_pixel(samples_per_pixel), MaxDepth(maxDepth) {
            // Set the image_height When the default image_width is changed
            calc_height(image_width, aspect_ratio);
        }

    // Render function logic here
    void render(const hittable& world) 
    {
        initialize();

        // Dynamic memory allocation for the image
        unsigned int*** image_data = new unsigned int**[image_height];
        for (int j =0; j < image_height; ++j)
        {
            image_data[j] = new unsigned int*[image_width];
            for (int i=0; i < image_width; ++i)
            {
                image_data[j][i] = new unsigned int[3];
            }
        }

        // Start the time tracking
        auto start = std::chrono::high_resolution_clock::now();

        // Render
        for (int j = 0; j < image_height; ++j)
        {
            output::print_progressbar(static_cast<int>((static_cast<double>(j) / image_height) * 100), "Rendering The Image:");
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample)
                {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, MaxDepth, world);
                }
                calc_color(&image_data[j][i][0], pixel_color, samples_per_pixel);
            }
        }

        // Stop the time tracking
        auto stop = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        // finish the rendering progressbar
        output::print_progressbar(100, "Rendering The Image:");

        // output the duration
        std::cout << "\nTime taken by function: " << duration.count() << " miliseconds";

        // Write rendered data to a ppm file
        output::write_ppm("output.ppm", image_data, image_height, image_width);

        // Deallocate memory for the 3rd dimension
        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                delete[] image_data[j][i];
            }
            // Deallocate memory for the 2nd dimension
            delete[] image_data[j];
        }

        // Deallocate memory for the 1st dimension
        delete[] image_data;

        std::clog << "\nDone.\n";


    }

private:
    int image_height = (static_cast<int>(image_width / aspect_ratio) < 1) ? 1 : static_cast<int>(image_width / aspect_ratio);
    point3 camera_center;
    point3 pixel_location;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize() {

        camera_center = point3(0, 0, 0);

        // Camera Setup
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Calculate Vectors for Viewport Edges
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate The Horizontal and Vertical Vectors from pixel to pixel
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;


        // Calculate The Viewport's top-left pixel
        auto ViewportUpperLeft = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel_location = ViewportUpperLeft + 0.5 * (pixel_delta_u + pixel_delta_v);

    }

    void calc_height(int width, double aspect_ratio)
    {
        image_height = (static_cast<int>(width / aspect_ratio) < 1) ? 1 : static_cast<int>(width / aspect_ratio);
    };

    ray get_ray(int i, int j) const {
        // Get a randomly sampled camera ray for the pixel at location i,j.

        auto pixel_center = pixel_location + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        hit_record rec;

        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color(0, 0, 0);

        if (world.hit(r, interval(0.001, infinity), rec)) {
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray(rec.p, direction), depth-1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif