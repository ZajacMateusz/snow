

/* ******************* nmea file **************************** */

char uart_data[] = "$GPGLL,4973.7831,N,01990.6901,W,225444,A";

 /* ******************* structs ***************************** */

typedef struct _nmea{
    char time[11];      /**< Time - hh:mm:ss:ss */
    float  lat;        /**< Latitude in NDEG - [degree][min].[sec/60] */
    char    ns;         /**< [N]orth or [S]outh */
    float  lon;        /**< Longitude in NDEG - [degree][min].[sec/60] */
    char    ew;         /**< [E]ast or [W]est */
    float speed;
    float alt;
    char date[100];
}nmea;

typedef struct device_data{
     nmea *position;
     float snow_depth;
}device_data;

/* ******************* variables **************************** */

GtkBuilder * builder;
GtkWidget * main_window;
GtkWidget *map_w; 

OsmGpsMap *map;
OsmGpsMapLayer *osd; 

int demo_is_on= 0;
device_data *device;             
static gint timer = 0;

short ui_visible_item= 0;

enum visible_flags{
    view_menu= 0x01,
    coordinates_box= 0x02,
    snow_depth_box= 0x04,
    gps_icon= 0x08,
    snow_sensor_icon= 0x10,
    gps_more_information_box= 0x20
};

/* ******************* GUI interface ******************* */

#define UI_FILE                         "src/view.ui"
#define VIEW_MENU_SRC                   "box_view_menu"
#define COORDINATES_BOX_SRC             "bt_coordinates"
#define SNOW_DEPTH_BOX_SRC              "bt_snow_depth"
#define GPS_MORE_INFORMATION_BOX_SRC    "bt_gps_more_information"

/* ******************* icon sources ******************* */

#define GPS_ICON_ON_SRC                 "img/gps_icon_ok.png"
#define GPS_ICON_OFF_SRC                "img/gps_icon_no.png"
#define SNOW_SENSOR_ICON_ON_SRC         "img/snow_sensor_icon_ok.png"
#define SNOW_SENSOR_ICON_OFF_SRC        "img/snow_sensor_icon_no.png"
#define DEVICE_MAP_MARKER_SRC           "img/device_marker.png"

/* ******************* macros **************************** */

#define VIEW_MENU_STATUS                (ui_visible_item & view_menu)
#define VIEW_MENU_ON                    (ui_visible_item|= view_menu)
#define VIEW_MENU_OFF                   (ui_visible_item&= ~view_menu)

#define COORDINATES_BOX_STATUS          (ui_visible_item & coordinates_box)
#define COORDINATES_BOX_ON              (ui_visible_item|= coordinates_box)
#define COORDINATES_BOX_OFF             (ui_visible_item&= ~coordinates_box)

#define SNOW_DEPTH_BOX_STATUS           (ui_visible_item & snow_depth_box)
#define SNOW_DEPTH_BOX_ON               (ui_visible_item|= snow_depth_box)
#define SNOW_DEPTH_BOX_OFF              (ui_visible_item&= ~snow_depth_box)

#define GPS_ICON_STATUS                 (ui_visible_item & gps_icon)
#define GPS_ICON_ON                     (ui_visible_item|= gps_icon)
#define GPS_ICON_OFF                    (ui_visible_item&= ~gps_icon)

#define SNOW_SENSOR_ICON_STATUS         (ui_visible_item & snow_sensor_icon)
#define SNOW_SENSOR_ICON_ON             (ui_visible_item|= snow_sensor_icon)
#define SNOW_SENSOR_ICON_OFF            (ui_visible_item&= ~snow_sensor_icon)

#define GPS_MORE_INFORMATION_BOX_STATUS (ui_visible_item & gps_more_information_box)
#define GPS_MORE_INFORMATION_BOX_ON     (ui_visible_item|= gps_more_information_box)
#define GPS_MORE_INFORMATION_BOX_OFF    (ui_visible_item&= ~gps_more_information_box)




