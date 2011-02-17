#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "renderer.h"

#include <iostream>
#include <sstream>
//#include <mapnik/graphics.hpp>
//#include <mapnik/image_util.hpp>
//#include <mapnik/value.hpp>
//#include <unicode/unistr.h>

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

void draw_ellipse_grid(agg::grid_rasterizer& ras,
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

/*
void png2grid(int step, mapnik::image_32 im) {
    mapnik::image_data_32 image = im.data();
    std::ostringstream s("");
    for (unsigned y = 0; y < image.height(); y=y+step)
    {
        unsigned int* row = image.getRow(y);
        for (unsigned x = 0; x < image.width(); x=x+step)
        {
            unsigned value = row[x] & 0xff;
            s << value;
        }
        s << "\n";
    }
    std::clog << "grid: " << s.str() << "\n";
}


void int2grid(int step, mapnik::image_32 im) {
    mapnik::image_data_32 image = im.data();
    std::ostringstream s("");
    for (unsigned y = 0; y < image.height(); y=y+step)
    {
        unsigned int* row = image.getRow(y);
        for (unsigned x = 0; x < image.width(); x=x+step)
        {
            s << "'" << row[x] << "'";
            //s << row[x];
        }
        s << "\n";
    }
    std::clog << "grid: " << s.str() << "\n";
}

*/
void buf2grid(int step, agg::grid_rendering_buffer& buf) {
    std::ostringstream s("");
    //unsigned int length = 256 / step;
    //unsigned int len = length * (length + 3) + 1;

    //UnicodeString::UnicodeString str(len, 0, len);
    s << "{ \"grid\":\n[\n";
    //int32_t index = 0;
    //str.setCharAt(index++, (UChar)'[');
    for (unsigned y = 0; y < buf.height(); y=y+step)
    {
        agg::grid_value2* row = buf.row(y);
        s << "\"";
        for (unsigned x = 0; x < buf.width(); x=x+step)
        {
            //s << "'" << (int)row[x] << "'";
            /*
            int val = (int)row[x];
            if (val == 0)
              s << " ";
            else 
              s << val;
            */
            //s << (int)row[x*4];
            s << row[x];
            //str.setCharAt(index++, (UChar)'a');
        }
        s << "\",\n";
    }
    s << "]\n}";
    //std::string buffer;
    //mapnik::to_utf8(str,buffer);
    std::clog << s.str() << "\n";
}

int main()
{

/*
    mapnik::image_32 im(width,height);
    agg::rendering_buffer rbuf(im.raw_data(),width,height, width * 4);

    agg::renderer<agg::span_rgba32> ren(rbuf);
    
    agg::rasterizer ras;
    ras.gamma(0.0);
    ras.filling_rule(agg::fill_even_odd);
    ren.clear(agg::rgba8(0, 255, 255));

    ras.move_to_d(50,50);
    ras.line_to_d(50,100);
    ras.line_to_d(100,100);
    ras.line_to_d(100,50);
    ras.render(ren, agg::rgba8(2,125,0,255));

    draw_ellipse(ras, 120,120,20,70);
    ras.render(ren, agg::rgba8(4,0,125,255));

    ras.move_to_d(200,200);
    ras.line_to_d(200,300);
    ras.line_to_d(300,300);
    ras.line_to_d(300,200);
    ras.render(ren, agg::rgba8(255,0,0,255));

    png2grid(4,im);
    //int2grid(4,im);
    mapnik::save_to_file<mapnik::image_data_32>(im.data(),"demo.png","png");
    system("open demo.png");

*/
    // grid
    
    //mapnik::image_32 im2(width,height);
    //std::clog << "size int: " << sizeof(unsigned int) << "\n";
    
    //agg::rendering_buffer rbuf2(im2.raw_data(),width,height, width);
    //agg::rendering_buffer rbuf2(im2.raw_data(),width,height, width*4);

    //unsigned char* buf = new unsigned char[width * height];
    //std::clog << sizeof(unsigned char) << "\n";
    //agg::rendering_buffer rbuf2(buf, width, height, width);


    unsigned int* buf = new unsigned int[width * height];
    //std::clog << sizeof(unsigned char) << "\n";
    agg::grid_rendering_buffer rbuf2(buf, width, height, width);

    agg::grid_renderer<agg::span_grid> ren_grid(rbuf2);
    agg::grid_rasterizer ras_grid;

    ras_grid.gamma(0.0);
    //ras_grid.filling_rule(agg::fill_even_odd);

    ren_grid.clear(0);

    ras_grid.move_to_d(50,50);
    ras_grid.line_to_d(50,100);
    ras_grid.line_to_d(100,100);
    ras_grid.line_to_d(100,50);
    ras_grid.render(ren_grid, 1);

    draw_ellipse_grid(ras_grid, 120,120,20,70);
    ras_grid.render(ren_grid, 2);

    ras_grid.move_to_d(200,200);
    ras_grid.line_to_d(200,300);
    ras_grid.line_to_d(300,300);
    ras_grid.line_to_d(300,200);
    ras_grid.render(ren_grid, 3);

    //png2grid(4,im);
    //int2grid(4,im2);
    buf2grid(4,rbuf2);
    delete buf;
    //mapnik::save_to_file<mapnik::image_data_32>(buf,"demo2.png","png");
    //system("open demo2.png");



    return 0;
}

