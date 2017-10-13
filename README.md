# EngineeringDesign
## Client API

In order to create ROD-friendly messages without the hassle of maintaining the somewhat arbitrary preprocessor values, I have written a very simple Java API.

### How it works
The Java class **MsgGen** handles all the hassle of building messages for the ROD. It does this with only three functions.
The robot has three main sets of actuators (**D**oors, **S**lope and **W**heels). Each type of actuator has its own function.

#### Doors
In order to control the doors, you can use the **.doors()** method.
This method expects two parameters: 
1. The door(s) you want to control
    * MsgGen.D_LEFT
    * MsgGen.D_RIGHT
    * MsgGen.D_BOTH
2. The direction in which you want to move this/these door(s)
    * MsgGen.D_IN
    * MsgGen.D_OUT
    * MsgGen.D_STOP

**Example**
```java
MsgGen.doors(MsgGen.D_LEFT, MsgGen.D_IN);
```
This line of code will generate a String message that tells the rod to move the left door to move inwards. The rest of the commands should be self-explanatory.

#### Slope
The **.slope()** method is very similar to the method for the doors. The main difference is that because the ROD only has one slope servo, the function only has one argument.

1. The direction in which you want the slope to move
    * MsgGen.S_UP
    * MsgGen.S_DOWN
    * MsgGen.S_STOP

**Example**
```java
MsgGen.slope(MsgGen.S_UP);
```

#### Wheels
Controlling the wheels in C++ is hard enough as-is, which is why I have tried to simplify their control as much as possible.
The **.wheels()** method generates messages for changing the wheel motion. It expects 2 parameters:

1. The vertical velocity (double from 0.0 to 1.0)
2. The horizontal velocity (double from 0.0 to 1.0)

**Example**
```java
MsgGen.wheels(0.5, 0.6);
```

#### LED
The internal LED can be turned on with the message created by the **.led()** method.

**Example**
```java
MsgGen.led();
```

#### Gimbal
The camera gimbal can be controlled with the **.gimbal()** method which has one argument: the desired state of the gimbal. The gimbal has 5 states:

1. MsgGen.G_STOP
2. MsgGen.G_LEFT
3. MsgGen.G_RIGHT
4. MsgGen.G_UP
5. MsgGen.G_DOWN

**Example**
```java
MsgGen.gimbal(MsgGen.G_LEFT);
```





