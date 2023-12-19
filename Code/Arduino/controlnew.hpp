#include "control.hpp"
float steerRatio;
bool lineFollowingAlgorithm(float speed, LinePin linePins, MotorPins motorPins, bool lastTurnRight, bool colorDetected)
{
    // Assuming sensor values are read into variables sensor1, sensor2, sensor3, sensor4, sensor5
    // Assuming color sensor value is read into variable colorSensor
    // Assuming motor control functions are turnSharpLeft(speed, motorPins), turnSharpRight(speed, motorPins), turnBack(speed, motorPins), moveForward(speed, motorPins)
    // Assuming a boolean variable lastTurnRight to keep track of the last turn direction

    // Read color sensor value
    LineReading lineReading = readLine(linePins);

    if (linePins.L) steerRatio += -0.4; 
    //if (linePins.L && linePins.LL) steerRatio += -0.3;
    if (linePins.R) steerRatio += 0.4;
    //if (linePins.R && linePins.RR) steerRatio += 0.3;
    if (linePins.M) steerRatio = steerRatio/4
    motorControl(speed, speed *steerRatio, MotorPins MotorPins)

    
    if (colorDetected)
    {
        do
        {
            turn(motorPins);
            lineReading = readLine(linePins);
        } while (!lineReading.LL && !lineReading.L && lineReading.M && !lineReading.R && !lineReading.RR);
    }
    else
    {
        if (lineReading.LL && lineReading.L && !lineReading.M && lineReading.R && lineReading.RR)
        {
            // All sensors are on the line, junction detected
            if (lastTurnRight)
            {
                do
                {
                    turnRight(speed, motorPins);
                    lineReading = readLine(linePins);
                } while (!lineReading.LL && lineReading.M && !lineReading.RR);

                lastTurnRight = false;
            }
            else
            {
                do
                {
                    turnLeft(speed, motorPins);
                    lineReading = readLine(linePins);
                } while (!lineReading.LL && lineReading.M && !lineReading.RR);
                lastTurnRight = true;
            }
        }
        else if (lineReading.RR && lineReading.R && lineReading.M)
        {
            do
            {
                turnRight(speed, motorPins);
                lineReading = readLine(linePins);
            } while (!lineReading.LL && lineReading.M && !lineReading.RR);

            lastTurnRight = true;
        }
        else if (lineReading.LL && lineReading.L && lineReading.M)
        {
            do
            {
                turnLeft(speed, motorPins);
                lineReading = readLine(linePins);
            } while (!lineReading.LL && lineReading.M && !lineReading.RR);

            lastTurnRight = false;
        }
        else if (lineReading.M)
        {
            // Middle sensor detects the line
            moveForward(speed, motorPins);
        }
        else if (lineReading.L)
        {
            // Left sensor detects the line
            turnLeft(speed, motorPins);
        }
        else if (lineReading.R)
        {
            // Right sensor detects the line
            turnRight(speed, motorPins);
        }
        else if (!lineReading.LL && !lineReading.L && !lineReading.M && !lineReading.R && !lineReading.RR){
        
        }
        else
        {
            // None of the sensors detect the line
            // Continue in the last known direction
            if (lastTurnRight)
            {
                turnRight(speed, motorPins);
            }
            else
            {
                turnLeft(speed, motorPins);
            }
        }
    }
    return lastTurnRight;
}
