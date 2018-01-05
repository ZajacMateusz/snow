CC = gcc

GTK_CFLAGS = -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include
#GTK_CFLAGS= -pthread -I/usr/include/gtk-3.0 -I/usr/lib64/gtk-3.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 
GLIB_CFLAGS = -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include 
CAIRO_CFLAGS = -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16
SOUP24_CFLAGS = -pthread -I/usr/include/libsoup-2.4 -I/usr/include/libxml2 -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include
GTK_LIBS = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0
WARN_CFLAGS = -I. -Wall -Wstrict-prototypes -Wnested-externs -Werror=missing-prototypes -Werror=implicit-function-declaration -Werror=pointer-arith -Werror=init-self -Werror=format=2 -Werror=missing-include-dirs -Werror=return-type 
GTHREAD_CFLAGS = -pthread -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include
_od= ../libs/osm-gps-map/src/libosmgpsmap_1_0_la-
_od1= $(_od)osm-gps-map-

#OSMGPSMAP_LIBS = $(_od)converter.o $(_od)osd-utils.o $(_od1)compat.o $(_od1)image.o $(_od1)layer.o $(_od1)osd.o $(_od1)point.o $(_od1)polygon.o $(_od1)source.o $(_od1)track.o $(_od1)widget.o
#$(_od)/converter.c  $(_od)/osd-utils.c  $(_od)/osm-gps-map-compat.c  $(_od)/osm-gps-map-image.c  $(_od)/osm-gps-map-layer.c  $(_od)/osm-gps-map-osd.c  $(_od)/osm-gps-map-point.c  $(_od)/osm-gps-map-polygon.c  $(_od)/osm-gps-map-source.c  $(_od)/osm-gps-map-track.c  $(_od)/osm-gps-map-widget.c

OSMGPSMAP_LIBS = ../libs/osm-gps-map/compile

OSMGPSMAP_CFLAGS = \
    $(GLIB_CFLAGS)          \
    $(GTK_CFLAGS)           \
    $(CAIRO_CFLAGS)         \
    $(SOUP24_CFLAGS)

mapviewer_CFLAGS = \
    -I../libs/osm_gps_map/src     \
    $(WARN_CFLAGS)          \
    $(OSMGPSMAP_CFLAGS)     \
    $(GTHREAD_CFLAGS)


#../libs/osm_gps_map/src/libosmgpsmap_1_0_la-converter.o 
#TEST= ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osd-utils.o ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osm-gps-map-compat.o ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osm-gps-map-image.o ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osm-gps-map-layer.o ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osm-gps-map-osd.o ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osm-gps-map-point.o ../libs/osm_gps_map/src/libosmgpsmap_1_0_la-osm-gps-map-polygon.o ../libs/osm_gps_map/src/

app: mapviewer.c src/def.h 
	$(CC) $(mapviewer_CFLAGS) $(GTK_LIBS) mapviewer.c -o  app 2> build.err 