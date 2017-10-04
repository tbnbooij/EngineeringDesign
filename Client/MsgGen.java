class MsgGen {
    public static String generateMessage(String body, int code, int speed) {
        return "#" + body + "@" + code + "@" + speed + "!";
    }

    // Door message codes
    public static int LEFT_DOOR_IN = 1;
    public static int RIGHT_DOOR_IN = 2;
    public static int LEFT_DOOR_OUT = 3;
    public static int RIGHT_DOOR_OUT = 4;
    public static int BOTH_DOORS_IN = 5;
    public static int BOTH_DOORS_OUT = 6;
    public static int BOTH_DOORS_STOP = 7;

    // Slope message codes
    public static int SLOPE_STOP = 0;
    public static int SLOPE_UP = 1;
    public static int SLOPE_DOWN = 2;

    // Wheels message codes
    public static int DIR_STOP = 0;
    public static int DIR_FORWARD = 1;
    public static int DIR_TURN = 2;

    // Body codes
    public static String DOOR_BODY = "d";
    public static String SLOPE_BODY = "s";
    public static String WHEELS_BODY = "w";
}
