#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <fstream>
using namespace std;
using namespace sf;

// Function to check input, store characters and digits and to know about errors
void input(char commandmatrix[], char fullcommand[], char char_comm[], int& value, int& erralpha, int& errdig)
{
    char int_comm[100];
    int countchar = 0, countdig = 0, space = 0;
    int i;
    erralpha = 0, errdig = 0;
    for (i = 0; commandmatrix[i] != '\0'; i++)
    {
        fullcommand[i] = commandmatrix[i];
        if (commandmatrix[i] == ' ' || commandmatrix[i] == '"')
            space = 1;
        if (commandmatrix[i] >= '0' && commandmatrix[i] <= '9')
            space = 1;
        if (commandmatrix[i] >= 'a' && commandmatrix[i] <= 'z' && space == 0)
        {
            char_comm[countchar] = commandmatrix[i];
            countchar++;
        }
        if (commandmatrix[i] >= 'a' && commandmatrix[i] <= 'z' && space == 1)
            erralpha = -1;
        if (commandmatrix[i] >= '0' && commandmatrix[i] <= '9')
        {
            int_comm[countdig] = commandmatrix[i];
            countdig++;
        }
    }
    fullcommand[i] = '\0';
    char_comm[countchar] = '\0';
    int_comm[countdig] = '\0';
    if (countdig == 0)
        errdig = -2;
    value = 0;
    for (int i = 0; int_comm[i] != '\0'; i++)
        value = value * 10 + (int_comm[i] - '0');
}
// Function to make circle and store it 
CircleShape drawcircle(RenderWindow& window, int radius, float x, float y, float width, Color& mycolor) {
    CircleShape circle;
    Vector2f Position = Vector2f(x, y);
    circle.setPosition(Position - Vector2f(radius, radius));
    circle.setRadius(radius);
    circle.setFillColor(Color::Transparent);
    circle.setOutlineColor(mycolor);
    circle.setOutlineThickness(width);
    return circle;
}
// Function for circle and to check errors
void circlefunction(CircleShape circles_storage[], int& circleindex, int run[], int& commandindex, int errdig, int incomplete_error[], RenderWindow& window, int value, float x, float y, int width, Color& mycolor, bool repeat)
{
    if (repeat || errdig == 0) {
        circles_storage[circleindex] = CircleShape(drawcircle(window, value, x, y, width, mycolor));
        circleindex++;
    }
    else
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}

// Function to gather information of circle by extracting it and comparing
int checkcolor(char command[], Color& mycolor)
{
    char color[100];
    int k = 0;

    for (int i = 0; command[i] != '\0'; i++)
        if (command[i] == ' ') {
            for (int j = i + 1; command[j] != '\0'; j++, k++)
            {
                color[k] = command[j];
            }
            break;
        }
    color[k] = '\0';
    if ((strcmp(color, "BROWN") == 0) || (strcmp(color, "brown") == 0) || (strcmp(color, "Brown") == 0)) {
        mycolor = Color{150,75,0};
        return 0;
    }
    else if ((strcmp(color, "RED") == 0) || (strcmp(color, "red") == 0) || (strcmp(color, "Red") == 0)) {
        mycolor = Color::Red;
        return 0;
    }
    else if ((strcmp(color, "GREEN") == 0) || (strcmp(color, "green") == 0) || (strcmp(color, "Green") == 0)) {
        mycolor = Color::Green;
        return 0;
    }
    else if ((strcmp(color, "BLUE") == 0) || (strcmp(color, "blue") == 0) || (strcmp(color, "Blue") == 0)) {
        mycolor = Color::Blue;
        return 0;
    }
    else if ((strcmp(color, "WHITE") == 0) || (strcmp(color, "white") == 0) || (strcmp(color, "White") == 0)) {
        mycolor = Color::White;
        return 0;
    }
    else if ((strcmp(color, "YELLOW") == 0) || (strcmp(color, "yellow") == 0) || (strcmp(color, "Yellow") == 0)) {
        mycolor = Color::Yellow;
        return 0;
    }
    else if ((strcmp(color, "CYAN") == 0) || (strcmp(color, "cyan") == 0) || (strcmp(color, "Cyan") == 0)) {
        mycolor = Color::Cyan;
        return 0;
    }
    else if ((strcmp(color, "MAGENTA") == 0) || (strcmp(color, "magenta") == 0) || (strcmp(color, "Magenta") == 0)) {
        mycolor = Color::Magenta;
        return 0;
    }
    else if ((strcmp(color, "TRANSPARENT") == 0) || (strcmp(color, "transparent") == 0) || (strcmp(color, "Transparent") == 0)) {
        mycolor = Color::Transparent;
        return 0;
    }
    else if ((strcmp(color, "GOLDEN") == 0) || (strcmp(color, "golden") == 0) || (strcmp(color, "Golden") == 0)) {
        mycolor = Color{255,233,147};
        return 0;
    }
    else if ((strcmp(color, "ORANGE") == 0) || (strcmp(color, "orange") == 0) || (strcmp(color, "Orange") == 0)){
        mycolor = Color{252,80,12};
        return 0;
    }
    else if ((strcmp(color, "PURPLE") == 0) || (strcmp(color, "purple") == 0) || (strcmp(color, "Purple") == 0)) {
        mycolor = Color{ 128,0,128 };
        return 0;
    }
    return -1;
}
// Main function of color & to check error
void colorfunction(char fullcommand[], int run[], int& commandindex, Color& mycolor, int colorerror, int incomplete_error[], int erralpha)
{
    colorerror = checkcolor(fullcommand, mycolor);
    if (colorerror == -1)
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}
// Function to chnage width
void widthfunction(int& width, int value, int run[], int& commandindex, int incomplete_error[], int errdig, bool repeat)
{
    if (repeat || errdig == 0)
        width = value;
    else
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}
//  Function to left rotate cursor
void functionleftrotate(ConvexShape& cursor, float& angle, int value, int run[], int& commandindex, int incomplete_error[], int errdig, bool repeat)
{
    if (repeat || errdig == 0)
    {
        angle -= value;
        cursor.setRotation(angle);
    }
    else
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}
//function to right rotate cursor
void functionrightrotate(ConvexShape& cursor, float& angle, int value, int run[], int& commandindex, int incomplete_error[], int errdig, bool repeat)
{
    if (repeat || errdig == 0)
    {
        angle += value;
        cursor.setRotation(angle);
    }
    else
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}
// Making line in forward direction and storing it 
RectangleShape moveforward(RenderWindow& window, int length, float& x, float& y, int width, float angle, Color& mycolor)
{
    RectangleShape line;
    line.rotate(angle);
    float radians = angle * 3.1415f / 180.0f;
    y = y - length * cos(radians);
    x = x + length * sin(radians);
    line.setPosition(x - width / 2, y);
    line.setSize(Vector2f(width, length));
    line.setFillColor(mycolor);
    return line;
}
// Main function of forward and to check errors
void forwardfunction(RectangleShape lines_storage[], int& linesindex, int run[], int& commandindex, RenderWindow& window, int value, float& x, float& y, int width, float angle, Color& mycolor, int errdig, int incomplete_error[], bool repeat)
{
    if (repeat || errdig == 0) {
        lines_storage[linesindex] = RectangleShape(moveforward(window, value, x, y, width, angle, mycolor));
        linesindex++;
    }
    else
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}
// Making line in backward direction and storing it 
RectangleShape movebackward(RenderWindow& window, int length, float& x, float& y, int width, float angle, Color& mycolor)
{
    RectangleShape line;
    float radians = angle * 3.1415f / 180.0f;
    line.setPosition(x - width / 2, y);
    y = y + length * cos(radians);
    x = x - length * sin(radians);
    line.setSize(Vector2f(width, length));
    line.setFillColor(mycolor);
    line.rotate(angle);
    return line;
}
// Main function of backward and to check errors
void backwardfunction(RectangleShape lines_storage[], int& linesindex, int run[], int& commandindex, RenderWindow& window, int value, float& x, float& y, int width, float angle, Color& mycolor, int errdig, int incomplete_error[], bool repeat)
{
    if (repeat || errdig == 0) {
        lines_storage[linesindex] = RectangleShape(movebackward(window, value, x, y, width, angle, mycolor));
        linesindex++;
    }
    else
        incomplete_error[commandindex] = 1;
    run[commandindex] = 1;
}
// Printing history and updating it to latest 5
void history(RenderWindow& window, int& commandindex, Text historytext, char commandmatrix[][100], int run[], int incomeplete_error[], int invalid[])
{
    int total_count1 = 0, total_count2 = 0, total_count3 = 0;

    for (int j = 0; j < commandindex; j++)
    {
        if (run[j] == 1 && incomeplete_error[j] == 0)
            total_count1++;
        else if (run[j] == 1 && incomeplete_error[j] == 1)
            total_count2++;
        else if (invalid[j] == 1)
            total_count3++;
    }

    int count1 = 0, count2 = 0, count3 = 0;
    float lining1 = 60.0f, lining2 = 350.0f, lining3 = 632.0f;

    for (int i = 0; i < commandindex; i++)
    {
        const auto& history = commandmatrix[i];

        if (run[i] == 1 && incomeplete_error[i] == 0)
        {
            if (count1 >= total_count1 - 5)
            {
                historytext.setString("(" + to_string(count1 + 1) + ") " + history);
                historytext.setPosition(1165, lining1);
                window.draw(historytext);
                lining1 += 45.0f;
            }
            count1++;
        }
        else if (run[i] == 1 && incomeplete_error[i] == 1)
        {
            if (count2 >= total_count2 - 5)
            {
                historytext.setString("(" + to_string(count2 + 1) + ") " + history);
                historytext.setPosition(1165, lining2);
                window.draw(historytext);
                lining2 += 45.0f;
            }
            count2++;
        }
        else if (invalid[i] == 1)
        {
            if (count3 >= total_count3 - 5)
            {
                historytext.setString("(" + to_string(count3 + 1) + ") " + history);
                historytext.setPosition(1165, lining3);
                window.draw(historytext);
                lining3 += 45.0f;
            }
            count3++;
        }
    }
}
// Drawing lines and format on sfml screen
void drawformat(Text& historytext, Text& historyheading, RenderWindow& window, VertexArray& Commandline, VertexArray& historyleftline, VertexArray& historytopline1, VertexArray& historytopline2, VertexArray& historytopline3, VertexArray& historytopline4, VertexArray& historytopline5, VertexArray& historytopline6)
{
    Commandline[0].position = Vector2f(0, 820);
    Commandline[1].position = Vector2f(1150, 820);
    historyleftline[0].position = Vector2f(1150, 7);
    historyleftline[1].position = Vector2f(1150, 900);
    historytopline1[0].position = Vector2f(1150, 7);
    historytopline1[1].position = Vector2f(1500, 7);
    historytopline2[0].position = Vector2f(1150, 50);
    historytopline2[1].position = Vector2f(1500, 50);
    historytopline3[0].position = Vector2f(1150, 295);
    historytopline3[1].position = Vector2f(1500, 295);
    historytopline4[0].position = Vector2f(1150, 340);
    historytopline4[1].position = Vector2f(1500, 340);
    historytopline5[0].position = Vector2f(1150, 580);
    historytopline5[1].position = Vector2f(1500, 580);
    historytopline6[0].position = Vector2f(1150, 620);
    historytopline6[1].position = Vector2f(1500, 620);
    historyheading.setString("Command History");
    historyheading.setPosition(1180, 10);
    window.draw(historyheading);
    historyheading.setString("Incomplete Commands");
    historyheading.setPosition(1175, 300);
    window.draw(historyheading);
    historyheading.setString("Invalid Commands");
    historyheading.setPosition(1180, 583);
    window.draw(historyheading);
    window.draw(historytopline1);
    window.draw(historytopline2);
    window.draw(historytopline3);
    window.draw(historytopline4);
    window.draw(historytopline5);
    window.draw(historytopline6);
    window.draw(historyleftline);
    window.draw(Commandline);
}
// Prinitng already stored circles 
void drawcircles_storage(RenderWindow& window, CircleShape circles_storage[], int& circleindex)
{

    for (int j = 0; j < circleindex; j++)
        window.draw(circles_storage[j]);
}
// Prinitng already stored lines
void drawlines_storage(RenderWindow& window, RectangleShape lines_storage[], int& linesindex)
{
    for (int i = 0; i < linesindex; i++)
        window.draw(lines_storage[i]);
}
// Drawing cursor 
void drawcursor(ConvexShape& cursor, Color& mycolor, Color& tempcolor, float& x, float& y, bool pen, int width)
{
    cursor.setPoint(0, Vector2f(0, -15 - width));
    cursor.setPoint(1, Vector2f(10 + width, 10 + width));
    cursor.setPoint(2, Vector2f(-10 - width, 10 + width));
    if (pen)
        cursor.setFillColor(mycolor);
    else
        cursor.setFillColor(tempcolor);
    cursor.setPosition(x, y);
}
// Function for repeat command
void repeatfunction(char fullcommand[], bool& repeat, RenderWindow& window, ConvexShape& cursor, int run[], RectangleShape lines_storage[], int& linesindex, CircleShape circles_storage[], int& circleindex, int commandindex, float& angle, int& width,
    float& x, float& y, Color& mycolor, Color& tempcolor, int incomplete_error[], int errdig, bool& pen, int erralpha, int& colorerror)
{
    repeat = true;
    run[commandindex] = 1;
    char repetition[100], charcommand[100], intcommand[100];
    int repetitiontimes = 0, funcvalue = 0;
    int l, countrep = 0, countalpha = 0, countint = 0;
    for (l = 0; fullcommand[l] != '[' && fullcommand[l] != '\0'; l++)
    {
        if (fullcommand[l] >= '0' && fullcommand[l] <= '9')
        {
            repetition[countrep] = fullcommand[l];
            countrep++;
        }
    }
    if (countrep == 0 || fullcommand[l] == '\0')
    {
        incomplete_error[commandindex] = 1;
    }
    else {
        for (int j = 0; j < countrep; j++) {
            repetitiontimes = repetitiontimes * 10 + (repetition[j] - '0');
            l++;
        }
        int p;
        for (int no = 1; no <= repetitiontimes; no++)
        {
            p = l;

            while (fullcommand[p] != ']' && fullcommand[p] != '\0')
            {
                int flag = 0;
                countalpha = 0;
                for (; fullcommand[p] != ' ' && fullcommand[p] != ']' && fullcommand[p]; p++)
                {
                    if (fullcommand[p] >= 48 && fullcommand[p] <= 57)
                    {
                        flag = 1;
                        break;
                    }
                    charcommand[countalpha] = fullcommand[p];
                    countalpha++;
                }
                charcommand[countalpha] = '\0';
                if (!flag)
                    p++;
                if ((strcmp(charcommand, "bk") == 0) || (strcmp(charcommand, "fd") == 0) || (strcmp(charcommand, "forward") == 0) || (strcmp(charcommand, "backward") == 0) || (strcmp(charcommand, "circle") == 0) || (strcmp(charcommand, "width") == 0) || (strcmp(charcommand, "WIDTH") == 0) || (strcmp(charcommand, "rt") == 0) || (strcmp(charcommand, "lt") == 0))
                {
                    countint = 0;
                    for (; fullcommand[p] != ' ' && fullcommand[p] != ']' && fullcommand[p]; p++)
                    {
                        int flag1 = 0;
                        if (fullcommand[p] >= 'a' && fullcommand[p] <= 'z')
                        {
                            flag = 1;
                            break;
                        }
                        if (fullcommand[p] >= 48 && fullcommand[p] <= 57)
                        {
                            intcommand[countint] = fullcommand[p];
                            countint++;
                        }
                    }
                    if (countint == 0)
                        incomplete_error[commandindex] = 1;
                    else {
                        funcvalue = 0;
                        for (int m = 0; m < countint; m++)
                            funcvalue = funcvalue * 10 + (intcommand[m] - '0');
                        if ((strcmp(charcommand, "fd") == 0) || (strcmp(charcommand, "forward") == 0))
                            forwardfunction(lines_storage, linesindex, run, commandindex, window, funcvalue, x, y, width, angle, mycolor, errdig, incomplete_error, repeat);
                        else if ((strcmp(charcommand, "bk") == 0) || (strcmp(charcommand, "backward") == 0))
                            backwardfunction(lines_storage, linesindex, run, commandindex, window, funcvalue, x, y, width, angle, mycolor, errdig, incomplete_error, repeat);
                        else if ((strcmp(charcommand, "circle") == 0))
                            circlefunction(circles_storage, circleindex, run, commandindex, errdig, incomplete_error, window, funcvalue, x, y, width, mycolor, repeat);
                        else if ((strcmp(charcommand, "width") == 0) || (strcmp(charcommand, "w") == 0) || (strcmp(charcommand, "WIDTH") == 0))
                            widthfunction(width, funcvalue, run, commandindex, incomplete_error, errdig, repeat);
                        else if (strcmp(charcommand, "rt") == 0)
                            functionrightrotate(cursor, angle, funcvalue, run, commandindex, incomplete_error, errdig, repeat);
                        else if (strcmp(charcommand, "lt") == 0)
                            functionleftrotate(cursor, angle, funcvalue, run, commandindex, incomplete_error, errdig, repeat);
                    }
                }
                else if ((strcmp(charcommand, "pu") == 0))
                {
                    if (pen)
                        tempcolor = mycolor;
                    pen = false;
                    mycolor = Color::Transparent;
                    run[commandindex] = 1;
                }
                else if ((strcmp(charcommand, "pd") == 0))
                {
                    pen = true;
                    mycolor = tempcolor;
                    run[commandindex] = 1;
                }
                else if (strcmp(charcommand, "color") == 0)
                {
                    char colorcommand[100];
                    strcpy_s(colorcommand, charcommand);
                    int colorindex = 5;
                    colorcommand[colorindex] = ' ';
                    colorindex++;
                    for (; fullcommand[p] != ' ' && fullcommand[p] != ']' && fullcommand[p] != '\0'; p++, colorindex++)
                    {
                        colorcommand[colorindex] = fullcommand[p];
                    }
                    colorcommand[colorindex] = '\0';
                    colorfunction(colorcommand, run, commandindex, mycolor, colorerror, incomplete_error, erralpha);
                }
            }
        }
    }
}
// Function to clear screen by initializing back to inital positions 
void clearscreen(float& x, float& y, int& width, int& linesindex, int& circleindex, int& commandindex, float& angle, bool& pen, ConvexShape& cursor, int run[], int invalid[], int incomplete_error[], char commandmatrix[][100], Color& mycolor)
{
    x = 600, y = 450, width = 1, linesindex = 0, circleindex = 0, commandindex = -1, angle = 0.0, pen = true, cursor.setRotation(angle), mycolor = Color::White;
    for (int i = 0; i < 100; i++)
        run[i] = { 0 }, incomplete_error[i] = { 0 }, invalid[i] = { 0 };
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            commandmatrix[i][j] = '\0';
}
// Function for pendown command
void pendownfunction(bool& pen, Color& mycolor, Color& tempcolor, int run[], int commandindex)
{
    pen = true;
    mycolor = tempcolor;
    run[commandindex] = 1;
}
// Function for penup function
void penupfunction(bool& pen, Color& mycolor, Color& tempcolor, int run[], int commandindex)
{
    if (pen)
        tempcolor = mycolor;
    pen = false;
    mycolor = Color::Transparent;
    run[commandindex] = 1;
}
// Function to save commands in a file (name given by user)
void saveFunction(char commandmatrix[][100], int run[], char fullcommand[], int commandindex, int invalid[], int incomplete_error[])
{
    run[commandindex] = 1;
    char filename[100];
    int indexfile = 0, j = 0;
    while (fullcommand[j] != '"')
        j++;
    j++;
    if (fullcommand[j] == '"')
        j++;
    for (int i = j; fullcommand[i] != '"' && fullcommand[i] != '\0'; i++, indexfile++)
    {
        filename[indexfile] = fullcommand[i];
    }
    filename[indexfile] = '\0';
    ofstream fileout(filename);
    if (!fileout)
    {
        invalid[commandindex] = 1;
        return;
    }
    else
    {
        fileout << commandindex << endl;
        for (int l = 0; l < commandindex; l++) {
            fileout << commandmatrix[l] << endl;
        }
        fileout.close();
    }
}
// Function to load commands from a file (name given by user)
void loadfunction(RenderWindow& window, ConvexShape& cursor, float& x, float& y, float& angle, int& width, char commandmatrix[][100], char fullcommand[], char char_comm[], int& commandindex, int& value, int& erralpha, int& errdig, int run[], int incomplete_error[], int invalid[], RectangleShape lines_storage[], int& linesindex, CircleShape circles_storage[], int& circleindex, bool& repeat, bool& pen, Color& mycolor, Color& tempcolor, int& colorerror, int& commandcolumns)
{
    int storedcommandindex;
    char filename[100];
    int indexfile = 0, j = 0;

    while (fullcommand[j] != '"')
        j++;
    j++;
    if (fullcommand[j] == '"')
        j++;
    for (int i = j; fullcommand[i] != '"' && fullcommand[i] != '\0'; i++, indexfile++)
    {
        filename[indexfile] = fullcommand[i];
    }
    filename[indexfile] = '\0';
    ifstream filein(filename);
    if (!filein)
    {
        invalid[commandindex] = 1;
        return;
    }
    else
    {
        x = 600, y = 450, angle = 0.0, pen = true, cursor.setRotation(angle), mycolor = Color::White, width = 1;
        filein >> storedcommandindex;
        int totalindex = commandindex + storedcommandindex;
        for (; commandindex <= totalindex;) {
            filein.getline(commandmatrix[commandindex], 100);
            input(commandmatrix[commandindex], fullcommand, char_comm, value, erralpha, errdig);
            if (strcmp(char_comm, "repeat") == 0)
            {
                repeatfunction(fullcommand, repeat, window, cursor, run, lines_storage, linesindex, circles_storage, circleindex, commandindex, angle, width, x, y, mycolor, tempcolor, incomplete_error, errdig, pen, erralpha, colorerror);
            }
            else if (((strcmp(char_comm, "fd") == 0) || (strcmp(char_comm, "forward") == 0)) && erralpha == 0) {
                forwardfunction(lines_storage, linesindex, run, commandindex, window, value, x, y, width, angle, mycolor, errdig, incomplete_error, repeat);
            }
            else if ((strcmp(char_comm, "save") == 0))
            {
                saveFunction(commandmatrix, run, fullcommand, commandindex, invalid, incomplete_error);
            }
            else if (((strcmp(char_comm, "bk") == 0) || (strcmp(char_comm, "backward") == 0)) && erralpha == 0) {
                backwardfunction(lines_storage, linesindex, run, commandindex, window, value, x, y, width, angle, mycolor, errdig, incomplete_error, repeat);
            }
            else if ((strcmp(char_comm, "color") == 0) && errdig == -2) {
                colorfunction(fullcommand, run, commandindex, mycolor, colorerror, incomplete_error, erralpha);
            }
            else if ((strcmp(char_comm, "circle") == 0) && erralpha == 0)
            {
                circlefunction(circles_storage, circleindex, run, commandindex, errdig, incomplete_error, window, value, x, y, width, mycolor, repeat);
            }
            else if ((strcmp(char_comm, "pu") == 0) || (strcmp(fullcommand, "pen up") == 0) && errdig == -2)
            {
                penupfunction(pen, mycolor, tempcolor, run, commandindex);
            }
            else if ((strcmp(char_comm, "pd") == 0) || (strcmp(fullcommand, "pen down") == 0) && errdig == -2)
            {
                pendownfunction(pen, mycolor, tempcolor, run, commandindex);
            }
            else if (((strcmp(char_comm, "width") == 0) || (strcmp(char_comm, "w") == 0) || (strcmp(char_comm, "WIDTH") == 0)) && erralpha == 0)
            {
                widthfunction(width, value, run, commandindex, incomplete_error, errdig, repeat);
            }
            else if ((strcmp(char_comm, "rt")) == 0 && erralpha == 0)
            {
                functionrightrotate(cursor, angle, value, run, commandindex, incomplete_error, errdig, repeat);
            }
            else if ((strcmp(char_comm, "lt")) == 0 && erralpha == 0)
            {
                functionleftrotate(cursor, angle, value, run, commandindex, incomplete_error, errdig, repeat);
            }
            else if ((strcmp(char_comm, "cs") == 0) || (strcmp(fullcommand, "clear screen") == 0))
            {
                clearscreen(x, y, width, linesindex, circleindex, commandindex, angle, pen, cursor, run, invalid, incomplete_error, commandmatrix, mycolor);
            }
            else if ((strcmp(char_comm, "\0") != 0))
                invalid[commandindex] = 1;
            commandindex++, commandcolumns = 0, repeat = false;
        }
        commandindex--;
        filein.close();
    }
}

int main()
{
    RenderWindow window(VideoMode(1500, 900), "Project - Drawing Tablet");
    Color mycolor = Color::White, tempcolor = Color::White;
    VertexArray line(Lines, 2);
    float  x = 600, y = 450, angle = 0.0;
    const int commandlistmax = 100;
    char fullcommand[100] = { 0 }, command[100] = { 0 }, char_comm[100] = { 0 }, commandmatrix[100][commandlistmax] = { 0 };
    int width = 1, erralpha = 0, errdig = 0, value = 1, colorerror = 0, commandindex = 0, commandcolumns = 0, run[100] = { 0 }, incomplete_error[100] = { 0 }, invalid[100] = { 0 };
    bool pen = true, repeat = false;
    RectangleShape lines_storage[100];
    int linesindex = 0;
    CircleShape circles_storage[100];
    int circleindex = 0;
    VertexArray Commandline(Lines, 2), historyleftline(Lines, 2), historytopline1(Lines, 2), historytopline2(Lines, 2), historytopline3(Lines, 2), historytopline4(Lines, 2), historytopline5(Lines, 2), historytopline6(Lines, 2);
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font" << endl;
        return -1;
    }
    Text commandtext;                                                   // Text of commands taken from user
    commandtext.setFont(font);
    commandtext.setCharacterSize(30);
    commandtext.setFillColor(Color::White);
    commandtext.setPosition(20, 840);
    Text historyheading;                                                // Text of heading of history
    historyheading.setFont(font);
    historyheading.setCharacterSize(30);
    historyheading.setFillColor(Color::White);
    Text historytext;                                                   // Text of history
    historytext.setFont(font);
    historytext.setCharacterSize(25);
    historytext.setFillColor(Color::White);
    ConvexShape cursor(3);
    while (window.isOpen())
    {
        drawcursor(cursor, mycolor, tempcolor, x, y, pen, width);           // Drawing cursor
        window.clear();
        drawlines_storage(window, lines_storage, linesindex);               // Drawing stored lines
        drawcircles_storage(window, circles_storage, circleindex);          // Drawing stored circles

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128 && event.text.unicode != 13)
                {
                    commandmatrix[commandindex][commandcolumns++] = static_cast<char>(event.text.unicode);
                    commandtext.setString("Enter Command: " + string(commandmatrix[commandindex]));                      // Taking input and storing in 2d array

                    commandmatrix[commandindex][commandcolumns] = '\0';
                }
                else if (event.text.unicode == 13)
                {
                    window.display();
                    input(commandmatrix[commandindex], fullcommand, char_comm, value, erralpha, errdig);                // Extracting from array (row of 2d array) and comparing with all commands
                    if (strcmp(char_comm, "repeat") == 0)
                    {
                        repeatfunction(fullcommand, repeat, window, cursor, run, lines_storage, linesindex, circles_storage, circleindex, commandindex, angle, width, x, y, mycolor, tempcolor, incomplete_error, errdig, pen, erralpha, colorerror);
                    }
                    else if (strcmp(char_comm, "load") == 0)
                    {
                        loadfunction(window, cursor, x, y, angle, width, commandmatrix, fullcommand, char_comm, commandindex, value, erralpha, errdig, run, incomplete_error, invalid, lines_storage, linesindex, circles_storage, circleindex, repeat, pen, mycolor, tempcolor, colorerror, commandcolumns);
                    }
                    else if (((strcmp(char_comm, "fd") == 0) || (strcmp(char_comm, "forward") == 0)) && erralpha == 0) {
                        forwardfunction(lines_storage, linesindex, run, commandindex, window, value, x, y, width, angle, mycolor, errdig, incomplete_error, repeat);
                    }
                    else if ((strcmp(char_comm, "save") == 0))
                    {
                        saveFunction(commandmatrix, run, fullcommand, commandindex, invalid, incomplete_error);
                    }
                    else if (((strcmp(char_comm, "bk") == 0) || (strcmp(char_comm, "backward") == 0)) && erralpha == 0) {
                        backwardfunction(lines_storage, linesindex, run, commandindex, window, value, x, y, width, angle, mycolor, errdig, incomplete_error, repeat);
                    }
                    else if ((strcmp(char_comm, "color") == 0) && errdig == -2) {
                        colorfunction(fullcommand, run, commandindex, mycolor, colorerror, incomplete_error, erralpha);
                    }
                    else if ((strcmp(char_comm, "circle") == 0) && erralpha == 0)
                    {
                        circlefunction(circles_storage, circleindex, run, commandindex, errdig, incomplete_error, window, value, x, y, width, mycolor, repeat);
                    }
                    else if ((strcmp(char_comm, "pu") == 0) || (strcmp(fullcommand, "pen up") == 0) && errdig == -2)
                    {
                        penupfunction(pen, mycolor, tempcolor, run, commandindex);
                    }
                    else if ((strcmp(char_comm, "pd") == 0) || (strcmp(fullcommand, "pen down") == 0) && errdig == -2)
                    {
                        pendownfunction(pen, mycolor, tempcolor, run, commandindex);
                    }
                    else if (((strcmp(char_comm, "width") == 0)|| (strcmp(char_comm, "w") == 0) || (strcmp(char_comm, "WIDTH") == 0)) && erralpha == 0)
                    {
                        widthfunction(width, value, run, commandindex, incomplete_error, errdig, repeat);
                    }
                    else if ((strcmp(char_comm, "rt")) == 0 && erralpha == 0)
                    {
                        functionrightrotate(cursor, angle, value, run, commandindex, incomplete_error, errdig, repeat);
                    }
                    else if ((strcmp(char_comm, "lt")) == 0 && erralpha == 0)
                    {
                        functionleftrotate(cursor, angle, value, run, commandindex, incomplete_error, errdig, repeat);
                    }
                    else if ((strcmp(char_comm, "cs") == 0) || (strcmp(fullcommand, "clear screen") == 0))
                    {
                        clearscreen(x, y, width, linesindex, circleindex, commandindex, angle, pen, cursor, run, invalid, incomplete_error, commandmatrix, mycolor);
                    }
                    else
                        invalid[commandindex] = 1;
                    commandindex++, commandcolumns = 0, repeat = false;
                }
            }
        }
        // Prinitng history, format and displaying all on screen
        history(window, commandindex, historytext, commandmatrix, run, incomplete_error, invalid);
        drawformat(historytext, historyheading, window, Commandline, historyleftline, historytopline1, historytopline2, historytopline3, historytopline4, historytopline5, historytopline6);
        window.draw(cursor);
        window.draw(commandtext);
        window.display();
    }
    return 0;
}
