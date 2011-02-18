#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "grid.h"
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

void draw_ellipse(agg::grid_rasterizer& ras,
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


void draw_line(agg::grid_rasterizer& ras,
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


void buf2grid(int step, agg::grid_rendering_buffer& buf) {
    std::ostringstream s("");
    s << "{ \"grid\":\n[\n";
    for (unsigned y = 0; y < buf.height(); y=y+step)
    {
        agg::grid_value* row = buf.row(y);
        s << "\"";
        for (unsigned x = 0; x < buf.width(); x=x+step)
        {
            //s << "'" << (int)row[x] << "'";
            
            agg::grid_value val = (agg::grid_value)row[x];
            if (val == 0)
              s << " ";
            else 
              s << val;
            
            //s << (int)row[x*4];
            //s << row[x];
        }
        s << "\",\n";
    }
    s << "]\n}";
    std::clog << s.str() << "\n";
}

int main()
{

    agg::grid_value* buf = new agg::grid_value[width * height];
    agg::grid_rendering_buffer rbuf2(buf, width, height, width);

    agg::grid_renderer<agg::span_grid> ren_grid(rbuf2);
    agg::grid_rasterizer ras_grid;
    
    std::clog << "size char: " << sizeof(unsigned char) << "\n";
    std::clog << "size int: " << sizeof(unsigned int) << "\n";

    //ras_grid.gamma(0.0);
    //ras_grid.filling_rule(agg::fill_even_odd);

    ren_grid.clear(' ');

    draw_line(ras_grid, 120,120,20,70,10);
    ras_grid.render(ren_grid, 'a');

    ras_grid.move_to_d(50,50);
    ras_grid.line_to_d(50,100);
    ras_grid.line_to_d(100,100);
    ras_grid.line_to_d(100,50);
    ras_grid.render(ren_grid, 'b');

    draw_ellipse(ras_grid, 120,120,20,70);
    ras_grid.render(ren_grid, 'c');

    ras_grid.move_to_d(200,200);
    ras_grid.line_to_d(200,300);
    ras_grid.line_to_d(300,300);
    ras_grid.line_to_d(300,200);
    ras_grid.render(ren_grid, 'd');

    buf2grid(4,rbuf2);
    delete buf;
    return 0;
}

