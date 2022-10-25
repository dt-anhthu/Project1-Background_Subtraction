# include <stdio.h>
#include <stdlib.h>
# define STB_IMAGE_IMPLEMENTATION
# include "./headers/stb_image.h"
# define STB_IMAGE_WRITE_IMPLEMENTATION
# include "./headers/stb_image_write.h"

unsigned char *background_subtraction(unsigned char * image_bg , int width_bg , int height_bg , int channel_bg, unsigned char * image_fg , int width_fg , int height_fg , int channel_fg, unsigned char * image_wf , int width_wf , int height_wf , int channel_wf)
{
     for (int i=0; i<height_fg;i++)
    {
        for(int j=0; j<width_fg; j++)
        {
            for(int k=0; k<channel_fg; k++)
            {
                if(abs(image_fg[i*width_fg*channel_fg+j*channel_fg+k] - image_bg[i*width_bg*channel_bg+j*channel_bg+k])>85
                   || abs(image_fg[i*width_fg*channel_fg+j*channel_fg+k] - image_fg[i*width_fg*channel_fg+j*channel_fg+k-1])<75)
                {
                    image_bg[i*width_bg*channel_bg+j*channel_bg+k]=0;
                    image_bg[i*width_bg*channel_bg+j*channel_bg+k-1]=0;
                }
                else
                    image_bg[i*width_bg*channel_bg+j*channel_bg+k]=255;

            }
        }
    }

    for (int i=0; i<height_fg;i++)
    {
        for(int j=0; j<width_fg; j++)
        {
            for(int k=0; k<channel_fg; k++)
            {
                if(image_bg[i*width_bg*channel_bg+j*channel_bg+2]==255)
                    image_bg[i*width_bg*channel_bg+j*channel_bg+k]=255;

                if(image_bg[i*width_bg*channel_bg+j*channel_bg+k]<10)
                    image_wf[i*width_wf*channel_wf+j*channel_wf+k] = image_fg[i*width_fg*channel_fg+j*channel_fg+k];
            }
        }
    }
}

int main ()
{
    // declare variables
    int width_bg , height_bg , channel_bg ;
    char path_img_bg [] = "./images/background.png";

    int width_fg , height_fg , channel_fg ;
    char path_img_fg [] = "./images/foreground.png";

    int width_wf , height_wf , channel_wf ;
    char path_img_wf [] = "./images/weather_forecast.png";
    char save_path_wf [] = "./images/weather_forecast-New.png";

    // read image data
    unsigned char *image_bg = stbi_load ( path_img_bg, &width_bg , &height_bg , &channel_bg , 0) ;
    if (image_bg == NULL)
    {
        printf ("\nError in loading the background image \n") ;
        exit (1) ;
    }
    printf ("width_bg = %d height_bg = %d channel_bg = %d\n", width_bg , height_bg , channel_bg ) ;

    unsigned char *image_fg = stbi_load ( path_img_fg, &width_fg , &height_fg , &channel_fg , 0) ;
    if (image_fg == NULL)
    {
        printf ("\nError in loading the foreground image \n") ;
        exit (1) ;
    }
    printf ("width_fg = %d height_fg = %d channel_fg = %d\n", width_fg , height_fg , channel_fg ) ;

    unsigned char *image_wf = stbi_load ( path_img_wf, &width_wf , &height_wf , &channel_wf , 0) ;
    if (image_wf == NULL)
    {
        printf ("\nError in loading the weather forecast image \n") ;
        exit (1) ;
    }
    printf ("width_wf = %d height_wf = %d channel_wf = %d\n", width_wf , height_wf , channel_wf ) ;


    //  background subtraction
    background_subtraction(image_bg, width_bg, height_bg, channel_bg, image_fg, width_fg, height_fg, channel_fg, image_wf, width_wf, height_wf, channel_wf);

    // save image
    stbi_write_png ( save_path_wf , width_wf, height_wf, channel_wf , image_wf , width_wf * channel_wf ) ;
    printf ("New image saved to %s\n", save_path_wf ) ;
}
