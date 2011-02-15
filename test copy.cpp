#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "renderer.h"

#include <iostream>
#include <mapnik/graphics.hpp>
#include <mapnik/image_util.hpp>

// icu
#include <unicode/unistr.h>

enum
{
    width  = 256,
    height = 256
};


double random(double min, double max)
{
    int r = (rand() << 15) | rand();
    return ((r & 0xFFFFFFF) / double(0xFFFFFFF + 1)) * (max - min) + min;
}


void draw_ellipse(agg::rasterizer& ras,
                  double x,  double y,
                  double rx, double ry)
{
    int i;
    ras.move_to_d(x + rx, y);

    // Here we have a fixed number of approximation steps, namely 360
    // while in reality it's supposed to be smarter.
    for(i = 1; i < 360; i++)
    {
        double a = double(i) * 3.1415926 / 180.0;
        ras.line_to_d(x + cos(a) * rx, y + sin(a) * ry);
    }
}


void draw_line(agg::rasterizer& ras,
               double x1, double y1, 
               double x2, double y2,
               double width)
{

    double dx = x2 - x1;
    double dy = y2 - y1;
    double d = sqrt(dx*dx + dy*dy);
    
    dx = width * (y2 - y1) / d;
    dy = width * (x2 - x1) / d;

    ras.move_to_d(x1 - dx,  y1 + dy);
    ras.line_to_d(x2 - dx,  y2 + dy);
    ras.line_to_d(x2 + dx,  y2 - dy);
    ras.line_to_d(x1 + dx,  y1 - dy);
}


int main()
{
    // Allocate the framebuffer
    //unsigned char* buf = new unsigned char[width * height * 3];

    // Create the rendering buffer 
    //agg::rendering_buffer rbuf(buf, width, height, width * 3);

    mapnik::image_32 im(width,height);
    //im.set_background(mapnik::color("white"));
    agg::rendering_buffer rbuf(im.raw_data(),width,height, width*4);

    // Create the renderer and the rasterizer
    agg::renderer<agg::span_rgba32> ren(rbuf);
    agg::rasterizer ras;

    // Setup the rasterizer
    ras.gamma(0.0);
    ras.filling_rule(agg::fill_even_odd);

    ren.clear(agg::rgba8(0, 0, 0));

    ras.move_to_d(50,50);
    ras.line_to_d(50,100);
    ras.line_to_d(100,100);
    ras.line_to_d(100,50);
    ras.render(ren, agg::rgba8(2,125,0,255));


    ras.move_to_d(200,200);
    ras.line_to_d(200,300);
    ras.line_to_d(300,300);
    ras.line_to_d(300,200);
    ras.render(ren, agg::rgba8(3,0,0,255));


/*
    int i;

    // Draw random polygons
    for(i = 0; i < 5; i++)
    {
        int n = rand() % 6 + 3;

        // Make the polygon. One can call move_to() more than once. 
        // In this case the rasterizer behaves like Win32 API PolyPolygon().
        ras.move_to_d(random(-30, rbuf.width() + 30), 
                      random(-30, rbuf.height() + 30));

        int j;
        for(j = 1; j < n; j++)
        {
            ras.line_to_d(random(-30, rbuf.width() + 30), 
                          random(-30, rbuf.height() + 30));
        }

        // Render
        ras.render(ren, agg::rgba8(rand() & 0xFF, 
                                   rand() & 0xFF, 
                                   rand() & 0xFF, 
                                   rand() & 0xFF));
    }

    // Draw random ellipses
    for(i = 0; i < 50; i++)
    {
        draw_ellipse(ras, 
                     random(-30, rbuf.width()  + 30), 
                     random(-30, rbuf.height() + 30),
                     random(3, 50), 
                     random(3, 50));
        ras.render(ren, agg::rgba8(rand() & 0x7F, 
                                   rand() & 0x7F, 
                                   rand() & 0x7F,
                                  (rand() & 0x7F) + 100));
    }

    // Draw random straight lines
    for(i = 0; i < 20; i++)
    {
        draw_line(ras, 
                  random(-30, rbuf.width()  + 30), 
                  random(-30, rbuf.height() + 30),
                  random(-30, rbuf.width()  + 30), 
                  random(-30, rbuf.height() + 30),
                  random(0.1, 10));

        ras.render(ren, agg::rgba8(rand() & 0x7F, 
                                   rand() & 0x7F, 
                                   rand() & 0x7F));
    }
*/
    int step = 4;

    UChar codepoint = 31; // Last ASCII control char.
    unsigned int length = 256 / step;

    // The exact string length:
    //   +3: length + two quotes and a comma
    //   +1: we don't need the last comma, but we need [ and ]
    unsigned int len = length * (length + 3) + 1;

    UnicodeString::UnicodeString str(len, 0, len);

    mapnik::image_data_32 image = im.data();
    int32_t index = 0;
    //s << '[';
    std::ostringstream s("");
    mapnik::image_data_32 image2(width,height);
    for (unsigned y = 0; y < image.height(); y=y+step)
    {
        unsigned int* row = image.getRow(y);
        unsigned int* row_to = image2.getRow(y);
        for (unsigned x = 0; x < image.width(); x=x+step)
        {
            unsigned value = row[x] & 0xff;
            row_to[x] = row[x];
            s << value;
            str.setCharAt(index++, (UChar)'1');
            std::clog << "value: " << index << "\n";
            //std::clog << "value: " << value << "\n";
        }
        s << "\n";
    }
    
    //std::string str2((const char*)str.getBuffer());
    std::clog << "data: " << s.str() << "\n";
    mapnik::save_to_file<mapnik::image_data_32>(im.data(),"demo.png","png");
    // Write a .ppm file
    /*
    FILE* fd = fopen("agg_test.ppm", "wb");
    fprintf(fd, "P6\n%d %d\n255\n", rbuf.width(), rbuf.height());
    fwrite(buf, 1, rbuf.width() * rbuf.height() * 3, fd);
    fclose(fd);
    */

    //delete [] buf;
    return 0;
}

