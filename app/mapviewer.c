/*
 * mapviewer.c
 * Copyright (C) Mateusz Zając 2017 <zajac382@gmail.com>
 */

 /* ******************* libraries *************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "osm-gps-map.h"

#include "src/def.h"

/* ******************* nmea  **************************** */

static int 
nmea_parse( nmea *position, char data[] ){    
    char buff[10];
    int data_number= 0;
    int i, j;
    for(i= 0; i< strlen(data); ++i){
        j= 0;
        while(data[i]!=',' && i< strlen(data)){
            buff[j++]= data[i++]; 
        }; 

        switch(data_number){
            case 0:
                if(strcmp(buff, "$GPGLL")!= 0)
                    return 0;                   
                break;
            case 1:{
                char a= buff[4];
                buff[4]= buff[2];
                buff[2]= a;
                a= buff[3];
                buff[3]= buff[4];
                buff[4]= a;
                position->lat = atof(buff);
                break;
            }
            case 2:
                position->ns = buff[0];
                break;
            case 3:{
                char a= buff[5];
                buff[5]= buff[3];
                buff[3]= a;
                a= buff[4];
                buff[4]= buff[5];
                buff[5]= a;
                position->lon = atof(buff);
                break;
            }
            case 4:
                position->ew = buff[0];
                break;
            case 5:{
                char temp_buff[11]= "00:00:00:00";
                temp_buff[0]= buff[0];
                temp_buff[1]= buff[1];
                temp_buff[3]= buff[2];
                temp_buff[4]= buff[3];
                temp_buff[6]= buff[4];
                temp_buff[7]= buff[5];
                strcpy(position->time, temp_buff);
                break;
            }
            
        }
        ++data_number;
    }
    return 0;
}

/* ******************* Function  ******************* */

static GtkWidget *
create_main_window(GtkBuilder * builder;){
    
    GtkWidget * window;
    GError * error = NULL;
    
    /* Tworzy obiekt buildera */
    builder = gtk_builder_new();
    /* Wczytuje zawartość interfejsu i sprawdza ewentualne błędy */
    if( !gtk_builder_add_from_file( builder, UI_FILE, & error ) )
    {
        g_warning( "Nie można wczytać plilu buildera: %s", error->message );
        g_error_free( error );
    }
    
    /* Łączy sygnały zawarte w pliku interfejsu z odpowiednimi funkcjami */
    gtk_builder_connect_signals( builder, NULL );
    
    /* Pobiera obiekt z nazwą "window1" */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "main_window" ) );  
    
    return window;
}

static void 
on_gps_status_change(GtkWidget *widget){
    
    GtkImage *image= (GtkImage*)gtk_builder_get_object(builder, "img_gps_status");
    GdkPixbuf * image_src;    
     if(!GPS_ICON_STATUS){        
        image_src = gdk_pixbuf_new_from_file (GPS_ICON_ON_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
        GPS_ICON_ON;
    }
    else{
        image_src = gdk_pixbuf_new_from_file (GPS_ICON_OFF_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
        GPS_ICON_OFF;
    } 
}

static void 
on_snow_sensor_status_change(GtkWidget *widget){
    
    GtkImage *image= (GtkImage*)gtk_builder_get_object(builder, "img_snow_sensor_status");
    GdkPixbuf * image_src;    
     if(!SNOW_SENSOR_ICON_STATUS){        
        image_src = gdk_pixbuf_new_from_file (SNOW_SENSOR_ICON_ON_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
        SNOW_SENSOR_ICON_ON;
    }
    else{
        image_src = gdk_pixbuf_new_from_file (SNOW_SENSOR_ICON_OFF_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
        SNOW_SENSOR_ICON_OFF;
    } 
}

static void
on_gps_data_in(char data[]){
   
    nmea_parse( device->position, uart_data);
}

static void
on_set_information(){

    char text[11];
    sprintf(text, "%f", device->position->lat);
    GtkLabel *label = (GtkLabel *)gtk_builder_get_object(builder, "lb_lat_coordinates");
    gtk_label_set_text (label, text );
    sprintf(text, "%f", device->position->lon);
    label = (GtkLabel *)gtk_builder_get_object(builder, "lb_lon_coordinates");
    gtk_label_set_text (label, text );
    sprintf(text, "%c", device->position->ns);
    label = (GtkLabel *)gtk_builder_get_object(builder, "lb_lat_coordinates_ns");
    gtk_label_set_text (label, text );
    sprintf(text, "%c", device->position->ew);
    label = (GtkLabel *)gtk_builder_get_object(builder, "lb_lon_coordinates_ew");
    gtk_label_set_text (label, text );    
    sprintf(text, "%f", device->snow_depth);
    char tab[5]= "";
    for(int i= 0; i< 4; ++i)
        tab[i]= text[i];
    label = (GtkLabel *)gtk_builder_get_object(builder, "lb_snow_depth");
    gtk_label_set_text (label, tab ); 
}

/* ************  UI button function  ******************* */

static void 
ui_map_set_center(GtkWidget *widget){
    
    osm_gps_map_set_center_and_zoom ( map, device->position->lat, device->position->lon, 20);  
 }    

static void 
ui_on_view_menu(GtkWidget *widget){
    
    if(!VIEW_MENU_STATUS){
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, VIEW_MENU_SRC)));  
        VIEW_MENU_ON;
    }
    else{
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, VIEW_MENU_SRC)));  
        VIEW_MENU_OFF;
    } 
}

static void 
ui_on_view_coordinates(GtkWidget *widget){
    
    if(!COORDINATES_BOX_STATUS){
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, COORDINATES_BOX_SRC)));  
        COORDINATES_BOX_ON;
    }
    else{
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, COORDINATES_BOX_SRC)));  
        COORDINATES_BOX_OFF;
    } 
}

static void 
ui_on_view_snow_depth(GtkWidget *widget){
    
    if(!SNOW_DEPTH_BOX_STATUS){
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, SNOW_DEPTH_BOX_SRC)));  
        SNOW_DEPTH_BOX_ON;
    }
    else{
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, SNOW_DEPTH_BOX_SRC)));  
        SNOW_DEPTH_BOX_OFF;
    } 
}

static void 
ui_on_view_gps_more_information(GtkWidget *widget){
  if(!GPS_MORE_INFORMATION_BOX_STATUS){
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, GPS_MORE_INFORMATION_BOX_SRC)));  
        GPS_MORE_INFORMATION_BOX_ON;
    }
    else{
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, GPS_MORE_INFORMATION_BOX_SRC)));  
        GPS_MORE_INFORMATION_BOX_OFF;
    }  
}

static void 
ui_on_status_change(GtkWidget *widget){
    
    on_gps_status_change(widget);
    on_snow_sensor_status_change(widget);
}

static void
ui_on_demo(GtkWidget *widget){
   
    if(!demo_is_on){
        demo_is_on= 1;
        //StartTimer();
    }
    else
        demo_is_on= 0;
}

static void
ui_show_menu_item(){

    GtkImage *image= (GtkImage*)gtk_builder_get_object(builder, "img_gps_status");
    GdkPixbuf * image_src;    
    if(GPS_ICON_STATUS){        
        image_src = gdk_pixbuf_new_from_file (GPS_ICON_ON_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
    }
    else {
        image_src = gdk_pixbuf_new_from_file (GPS_ICON_OFF_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
    }

    image= (GtkImage*)gtk_builder_get_object(builder, "img_snow_sensor_status");   
    if(SNOW_SENSOR_ICON_STATUS){        
        image_src = gdk_pixbuf_new_from_file (SNOW_SENSOR_ICON_ON_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
    }
    else{
        image_src = gdk_pixbuf_new_from_file (SNOW_SENSOR_ICON_OFF_SRC, NULL);
        gtk_image_set_from_pixbuf(image, image_src);
    } 

    if(VIEW_MENU_STATUS)
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, VIEW_MENU_SRC)));    
    else
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, VIEW_MENU_SRC)));
    if(SNOW_DEPTH_BOX_STATUS)
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, SNOW_DEPTH_BOX_SRC)));    
    else
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, SNOW_DEPTH_BOX_SRC)));  
    if(COORDINATES_BOX_STATUS)
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, COORDINATES_BOX_SRC)));    
    else
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, COORDINATES_BOX_SRC))); 
    if(GPS_MORE_INFORMATION_BOX_STATUS)
        gtk_widget_show (GTK_WIDGET(gtk_builder_get_object(builder, GPS_MORE_INFORMATION_BOX_SRC)));    
    else
        gtk_widget_hide (GTK_WIDGET(gtk_builder_get_object(builder, GPS_MORE_INFORMATION_BOX_SRC))); 
}

static void
ui_init(){

    VIEW_MENU_OFF;
    SNOW_DEPTH_BOX_ON;
    COORDINATES_BOX_ON;    
    GPS_MORE_INFORMATION_BOX_OFF;
    ui_show_menu_item();
}

/* ************** main *************************** */

int 
main( int argc, char * argv[] ){    

    device = malloc(sizeof(device_data));       
    device->position = malloc(sizeof(nmea));    
     // temporary:
        device->snow_depth= 0.55;  
        on_gps_data_in(uart_data);


    gtk_init( & argc, & argv );
    main_window = create_main_window(builder);
    gtk_window_fullscreen(GTK_WINDOW(main_window));

    OsmGpsMapSource_t source = OSM_GPS_MAP_SOURCE_GOOGLE_SATELLITE;

    if ( !osm_gps_map_source_is_valid(source) )
        return 1;    
    
    map_w = g_object_new (OSM_TYPE_GPS_MAP,
                     "map-source", source,
                     "tile-cache", "/tmp/",
                      NULL);
    osd = g_object_new (OSM_TYPE_GPS_MAP_OSD,
                        "show-scale",FALSE,
                        "show-coordinates",FALSE,
                        "show-crosshair",FALSE,
                        "show-dpad",FALSE,
                        "show-zoom",TRUE,
                        "show-gps-in-dpad",TRUE,
                        "show-gps-in-zoom",FALSE,
                        "dpad-radius", 30,
                        NULL);

    gtk_box_pack_start (
                GTK_BOX(gtk_builder_get_object(builder, "box_map")),
                GTK_WIDGET(map_w), TRUE, TRUE, 0);   

    map = OSM_GPS_MAP(map_w);

    osm_gps_map_set_center_and_zoom ( map, device->position->lat, device->position->lon, 20);
    osm_gps_map_layer_add(OSM_GPS_MAP(map), osd);
    
    gtk_widget_show_all (main_window);
    ui_init();

    /* ****************** signal connect *********************** */

    g_signal_connect(gtk_builder_get_object(builder, "bt_set_center"), "clicked", G_CALLBACK(ui_map_set_center), (gpointer) "center map");
    g_signal_connect(gtk_builder_get_object(builder, "bt_show_snow_depth"), "clicked", G_CALLBACK(ui_on_view_snow_depth), (gpointer) "show snow depth box");
    g_signal_connect(gtk_builder_get_object(builder, "bt_show_coordinates"), "clicked", G_CALLBACK(ui_on_view_coordinates), (gpointer) "show coordinates box");
    g_signal_connect(gtk_builder_get_object(builder, "bt_show_gps_more_information"), "clicked", G_CALLBACK(ui_on_view_gps_more_information), (gpointer) "show coordinates box");
    g_signal_connect(gtk_builder_get_object(builder, "bt_view_menu"), "clicked", G_CALLBACK(ui_on_view_menu), (gpointer) "show view menu");
    g_signal_connect(gtk_builder_get_object(builder, "bt_demo"), "clicked", G_CALLBACK(ui_on_demo), (gpointer) "start demo");
    // temporary:
        g_signal_connect(gtk_builder_get_object(builder, "button3"), "clicked", G_CALLBACK(ui_on_status_change), (gpointer) " test button status gps and sensor");

    
    GdkPixbuf * image;
    image = gdk_pixbuf_new_from_file (DEVICE_MAP_MARKER_SRC, NULL);
    if(image!= NULL)
        osm_gps_map_image_add(map, device->position->lat, device->position->lon, image);

    on_set_information();

    g_object_unref(G_OBJECT(osd));
    gtk_main();
    return 0;
}
