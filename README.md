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

1. The direction in which you want the ROD to move
    * MsgGen.W_FORWARD
    * MsgGen.W_BACKWARD
    * MsgGen.W_LEFT
    * MsgGen.W_RIGHT
    * MsgGen.W_STOP
2. The speed at which you want the ROD to move
    * A **double** between 0.0 and 1.0
    * This parameter **may be omitted** if you pass *MsgGen.W_STOP* as the direction argument.

**Example**
```java
MsgGen.wheels(MsgGen.W_FORWARD, 1.0);
MsgGen.wheels(MsgGen.W_STOP);
```

```
<sidenote>
I have explicitly chosen to store all the aforementioned values (W_IN, D_LEFT, etc.) as final static integers instead of enums. 
These are far more memory-friendly than enums on Android platforms.
</sidenote>
```



