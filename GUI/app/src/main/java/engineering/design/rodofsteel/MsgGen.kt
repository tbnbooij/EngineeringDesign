package engineering.design.rodofsteel

/**
 * Created by s166315 on 15-10-2017.
 */
import java.lang.Math.round

internal object MsgGen {
    // Door message codes
    private val LEFT_DOOR_IN = 1
    private val RIGHT_DOOR_IN = 2
    private val LEFT_DOOR_OUT = 3
    private val RIGHT_DOOR_OUT = 4
    private val LEFT_DOOR_STOP = 5
    private val RIGHT_DOOR_STOP = 6
    private val BOTH_DOORS_IN = 7
    private val BOTH_DOORS_OUT = 8
    private val BOTH_DOORS_STOP = 9

    // Slope message codes
    private val SLOPE_STOP = 0
    private val SLOPE_UP = 1
    private val SLOPE_DOWN = 2

    // Body codes
    private val DOOR_BODY = "d"
    private val SLOPE_BODY = "s"
    private val WHEELS_BODY = "w"
    private val LED_BODY = "l"
    private val GIMBAL_BODY = "g"

    // "API" codes
    // Doors
    val D_LEFT = 0
    val D_RIGHT = 1
    val D_BOTH = 2

    val D_IN = 3
    val D_OUT = 4
    val D_STOP = 5

    // Slope
    val S_UP = 0
    val S_DOWN = 1
    val S_STOP = 2

    // Gimbal
    val G_STOP = 0
    val G_LEFT = 2
    val G_RIGHT = 3
    val G_UP = 4
    val G_DOWN = 5


    private fun createMsg(body: String, code: Int, speed: Int): String {
        return "#$body@$code@$speed!"
    }

    // "API" Functions
    fun door(side: Int, direction: Int): String {
        var instruction = -1

        when (side) {
            D_LEFT -> when (direction) {
                D_IN -> instruction = LEFT_DOOR_IN
                D_OUT -> instruction = LEFT_DOOR_OUT
                D_STOP -> instruction = LEFT_DOOR_STOP
            }
            D_RIGHT -> when (direction) {
                D_IN -> instruction = RIGHT_DOOR_IN
                D_OUT -> instruction = RIGHT_DOOR_OUT
                D_STOP -> instruction = RIGHT_DOOR_STOP
            }
            D_BOTH -> when (direction) {
                D_IN -> instruction = BOTH_DOORS_IN
                D_OUT -> instruction = BOTH_DOORS_OUT
                D_STOP -> instruction = BOTH_DOORS_STOP
            }
        }
        return createMsg(DOOR_BODY, instruction, 0)
    }

    fun slope(direction: Int): String {
        var instruction = -1

        when (direction) {
            S_UP -> instruction = SLOPE_UP
            S_DOWN -> instruction = SLOPE_DOWN
            S_STOP -> instruction = SLOPE_STOP
        }
        return createMsg(SLOPE_BODY, instruction, 0)
    }

    fun wheels(verticalSpeed: Double, horizontalSpeed: Double): String {
        return createMsg(WHEELS_BODY, 50 + round(50.0 * verticalSpeed).toInt(), 50 + round(50.0 * horizontalSpeed).toInt())
    }

    fun led(): String {
        return createMsg(LED_BODY, 0, 0)
    }

    fun gimbal(state: Int): String {
        return createMsg(GIMBAL_BODY, state, 0)
    }
}